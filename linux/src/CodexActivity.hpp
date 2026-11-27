#pragma once

#include <cstring>
#include <string>
#include <string_view>
#include <unordered_map>
#include <glib-unix.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>

enum class CodexPhase { Idle, Working, Finishing };

struct CodexFrame {
    CodexPhase phase = CodexPhase::Idle;
    double elapsed = 0;

    static constexpr double FinishDuration = 1.75;
};

// Each Codex turn has its own entry, so one chat finishing cannot stop another's animation.
class CodexActivity {
public:
    CodexActivity() = default;
    CodexActivity(const CodexActivity&) = delete;
    CodexActivity& operator=(const CodexActivity&) = delete;
    ~CodexActivity() { stop(); }

    bool listen() {
        if (fd_ != -1) return true;
        const std::string path = std::string(g_get_user_runtime_dir()) + "/kurocat-codex.sock";
        sockaddr_un address{};
        if (path.size() >= sizeof(address.sun_path)) return false;
        address.sun_family = AF_UNIX;
        std::memcpy(address.sun_path, path.c_str(), path.size() + 1);

        struct stat previous{};
        if (lstat(path.c_str(), &previous) == 0 &&
            (!S_ISSOCK(previous.st_mode) || previous.st_uid != getuid() || unlink(path.c_str()) != 0)) {
            return false;
        }
        fd_ = socket(AF_UNIX, SOCK_DGRAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
        if (fd_ == -1) return false;
        if (bind(fd_, reinterpret_cast<sockaddr*>(&address), sizeof(address)) != 0) {
            close(fd_);
            fd_ = -1;
            return false;
        }
        path_ = path;
        if (chmod(path_.c_str(), S_IRUSR | S_IWUSR) != 0) {
            stop();
            return false;
        }
        watch_ = g_unix_fd_add(fd_, G_IO_IN, +[](gint fd, GIOCondition, gpointer data) -> gboolean {
            auto& activity = *static_cast<CodexActivity*>(data);
            char buffer[256];
            for (int i = 0; i < 32; ++i) {
                const ssize_t size = recv(fd, buffer, sizeof(buffer), MSG_TRUNC);
                if (size < 0) break;
                if (size > 0 && size < static_cast<ssize_t>(sizeof(buffer))) {
                    activity.receive(std::string_view(buffer, size), now());
                }
            }
            return G_SOURCE_CONTINUE;
        }, this);
        return true;
    }

    void stop() {
        if (watch_) g_source_remove(watch_);
        if (fd_ != -1) close(fd_);
        if (!path_.empty()) unlink(path_.c_str());
        watch_ = 0;
        fd_ = -1;
        path_.clear();
        turns_.clear();
        finishedAt_ = previewAt_ = -1;
    }

    void preview() {
        if (!turns_.empty()) return;
        finishedAt_ = -1;
        previewAt_ = now();
    }

    CodexFrame frame() {
        const double time = now();
        // An abrupt Codex exit can prevent all of its end hooks from running.
        for (auto turn = turns_.begin(); turn != turns_.end();) {
            if (time - turn->second > 6 * 60 * 60) turn = turns_.erase(turn);
            else ++turn;
        }
        if (!turns_.empty()) return {CodexPhase::Working, time - startedAt_};
        if (time - finishedAt_ < CodexFrame::FinishDuration && finishedAt_ >= 0) {
            return {CodexPhase::Finishing, time - finishedAt_};
        }
        if (previewAt_ >= 0) {
            constexpr double workDuration = 4.85;
            const double elapsed = time - previewAt_;
            if (elapsed < workDuration) return {CodexPhase::Working, elapsed};
            if (elapsed < workDuration + CodexFrame::FinishDuration) return {CodexPhase::Finishing, elapsed - workDuration};
            previewAt_ = -1;
        }
        return {};
    }

private:
    static double now() { return g_get_monotonic_time() / 1e6; }

    void receive(std::string_view message, double time) {
        const auto separator = message.find(' ');
        if (separator == message.npos) return;
        const auto event = message.substr(0, separator);
        const auto id = message.substr(separator + 1);
        if (id.empty() || id.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_:.") != id.npos) return;
        if (event == "start") {
            if (id.find(':') == id.npos) return;
            if (turns_.empty()) startedAt_ = time;
            turns_[std::string(id)] = time;
            previewAt_ = finishedAt_ = -1;
        } else if (event == "stop" || event == "interrupt") {
            if (turns_.erase(std::string(id)) && turns_.empty() && event == "stop") finishedAt_ = time;
        } else if (event == "close") {
            for (auto turn = turns_.begin(); turn != turns_.end();) {
                if (turn->first.compare(0, id.size(), id) == 0 && turn->first.size() > id.size()
                    && turn->first[id.size()] == ':') turn = turns_.erase(turn);
                else ++turn;
            }
        }
    }

    int fd_ = -1;
    guint watch_ = 0;
    std::string path_;
    std::unordered_map<std::string, double> turns_;
    double startedAt_ = 0;
    double finishedAt_ = -1;
    double previewAt_ = -1;
};
