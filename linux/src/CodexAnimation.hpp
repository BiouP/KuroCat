#pragma once

#include <array>
#include "CatRenderer.hpp"
#include "CodexActivity.hpp"

namespace CodexAnimation {

inline double ease(double a, double b, double time) {
    const double t = std::clamp((time - a) / (b - a), 0.0, 1.0);
    return t * t * (3.0 - 2.0 * t);
}

inline double pulse(double a, double b, double c, double d, double t) {
    return ease(a, b, t) * (1.0 - ease(c, d, t));
}

inline Pt blend(Pt from, Pt to, double amount) {
    return {static_cast<float>(from.x + (to.x - from.x) * amount),
            static_cast<float>(from.y + (to.y - from.y) * amount)};
}

inline void applyPose(CatPhysics& cat, CodexFrame frame, const SkinSpec& skin) {
    const bool working = frame.phase == CodexPhase::Working;
    const double t = std::fmod(frame.elapsed, 4.85);
    const double ready = working ? ease(0.12, 0.62, frame.elapsed) : 0;
    const double thinking = ready * pulse(2.03, 2.45, 2.82, 3.23, t);
    const double focus = ready * (1.0 - 0.88 * thinking);
    const double stretch = working ? 0 : pulse(0.04, 0.60, 0.81, 1.47, frame.elapsed);
    const double recovery = working ? 0 : pulse(0.96, 1.17, 1.28, 1.67, frame.elapsed);

    cat.headOffsetY.value += 8 * focus - 6 * thinking + 13.5 * stretch - 7.5 * recovery;
    cat.headTilt.value += -0.034 * focus + 0.19 * thinking - 0.095 * stretch;
    cat.headYaw.value += 0.11 * focus * std::sin(5 * t) + 0.46 * thinking - 0.22 * stretch;
    cat.headPitch.value += 0.46 * focus - 0.48 * thinking;
    cat.eyeGaze.x.value += 0.62 * thinking;
    cat.eyeGaze.y.value += 0.43 * focus - 0.68 * thinking;
    cat.bodySquash.value *= 1.0 - 0.055 * focus - 0.14 * stretch + 0.045 * recovery;
    cat.earTwitch.value += 0.28 * focus * std::sin(9.3 * t) + 0.42 * thinking;
    cat.earFold.value += 0.21 * stretch;
    cat.tailTip.y.value -= 11 * stretch;
    cat.sleepiness *= 1.0 - std::max(ready, stretch);
    cat.yawnAmount *= 1.0 - ready;

    Pt left = blend(cat.leftPaw.point(), {155, 249}, ready);
    Pt right = blend(cat.rightPaw.point(), {223, 248}, ready);
    left.y -= 4 * thinking;
    right.y -= 11 * thinking;
    const bool douni = skin.renderStyle == SkinRenderStyle::Douni;
    if (douni) {
        cat.douniMouseBlend.value *= 1.0 - std::max(ready, stretch);
        cat.douniLoafBlend.value = std::max(cat.douniLoafBlend.value * (1.0 - ready), stretch);
    }

    using Key = PhysicalKey;
    struct Tap { double at; Key key; };
    constexpr std::array<Tap, 19> taps{{
        {0.72, Key::H}, {0.87, Key::F}, {1.03, Key::J}, {1.18, Key::D}, {1.39, Key::U},
        {1.54, Key::R}, {1.71, Key::K}, {1.88, Key::F}, {2.03, Key::J},
        {3.14, Key::J}, {3.31, Key::F}, {3.44, Key::H}, {3.57, Key::D}, {3.74, Key::U},
        {3.90, Key::R}, {4.09, Key::K}, {4.29, Key::F}, {4.47, Key::J}, {4.73, Key::Enter}
    }};
    for (const Tap& tap : taps) {
        if (!working) break;
        const double delta = t - tap.at;
        const double impact = pulse(-0.11, 0.003, 0.032, 0.15, delta);
        if (impact > 0) {
            if (douni) {
                const bool useLeft = prefersViewerLeftPaw(tap.key);
                (useLeft ? cat.douniLeftRaise : cat.douniRightRaise).value = -impact;
                const Pt target = KeyboardLayout::v2KeyCellCenter(tap.key);
                auto& paw = useLeft ? cat.douniLeftKeyTarget : cat.douniRightKeyTarget;
                paw.x.value = target.x;
                paw.y.value = target.y;
            } else {
                const Pt target = KeyboardLayout::canvasPointForKey(tap.key);
                Pt& paw = target.x < CatPhysics::SeatAnchor.x ? left : right;
                paw = blend(paw, target, impact);
                paw.y -= 10.5 * pulse(-0.16, -0.085, -0.060, 0.003, delta);
            }
        }
        if (delta >= 0 && delta < 0.24) {
            auto& glow = cat.keyGlow[visualKeyOf(tap.key)];
            glow = std::max(glow, static_cast<float>(1.0 - ease(0.045, 0.24, delta)));
        }
    }
    left = blend(left, {141, 277}, stretch);
    right = blend(right, {257, 275}, stretch);
    cat.leftPaw.x.value = left.x;
    cat.leftPaw.y.value = left.y;
    cat.rightPaw.x.value = right.x;
    cat.rightPaw.y.value = right.y;
    if (std::max(ready, stretch) > 0.3) cat.leftPawOnMouse = false;
    cat.petHeadIntensity = std::max(cat.petHeadIntensity, static_cast<float>(0.97 * stretch));
}

inline void drawStatus(cairo_t* cr, CodexFrame frame, const CatSettings& settings, const SkinSpec& skin) {
    const bool working = frame.phase == CodexPhase::Working;
    const double t = frame.elapsed;
    const double alpha = working ? ease(0.10, 0.45, t) : pulse(0, 0.28, 1.01, CodexFrame::FinishDuration, t);
    if (alpha <= 0.01) return;
    constexpr double pi = 3.141592653589793;
    const double width = working ? 60 : 32;
    const double x = skin.renderStyle == SkinRenderStyle::Douni ? 101 : 271;
    const double y = 82 + 1.4 * std::sin(t * 3.4);
    cairo_save(cr);
    cairo_translate(cr, settings.flipHorizontal ? CatPhysics::CanvasWidth - x : x, y);
    const double scale = 0.86 + 0.14 * alpha;
    cairo_scale(cr, scale, scale);
    cairo_move_to(cr, -width * 0.33, 8);
    cairo_line_to(cr, -width * 0.37 - 3, 16);
    cairo_line_to(cr, -width * 0.10, 8);
    cairo_close_path(cr);
    cairo_set_source_rgba(cr, working ? 0.5 : 0.56, working ? 0.42 : 0.72, working ? 0.75 : 0.27, alpha);
    cairo_fill(cr);
    cairo_new_sub_path(cr);
    cairo_arc(cr, width / 2 - 9, -4, 9, -pi / 2, 0);
    cairo_arc(cr, width / 2 - 9, 4, 9, 0, pi / 2);
    cairo_arc(cr, -width / 2 + 9, 4, 9, pi / 2, pi);
    cairo_arc(cr, -width / 2 + 9, -4, 9, pi, 3 * pi / 2);
    cairo_close_path(cr);
    cairo_set_source_rgba(cr, 0.11, working ? 0.10 : 0.18, working ? 0.20 : 0.11, alpha);
    cairo_fill_preserve(cr);
    cairo_set_source_rgba(cr, working ? 0.58 : 0.63, working ? 0.51 : 0.79, working ? 0.84 : 0.30, alpha);
    cairo_set_line_width(cr, 1.3);
    cairo_stroke(cr);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
    if (working) {
        cairo_set_source_rgba(cr, 0.79, 0.72, 1, alpha);
        cairo_set_line_width(cr, 1.6);
        cairo_move_to(cr, -20, -3.5);
        cairo_line_to(cr, -16, 0);
        cairo_line_to(cr, -20, 3.5);
        cairo_move_to(cr, -13, 4);
        cairo_line_to(cr, -8, 4);
        cairo_stroke(cr);
        for (int i = 0; i < 3; ++i) {
            const double glow = (1.0 + std::sin(t * 7.8 - i * 1.45)) / 2.0;
            cairo_set_source_rgba(cr, 0.84, 0.77, 1, alpha * (0.34 + 0.66 * glow));
            cairo_arc(cr, 3 + i * 8, -2 * glow, 1.4 + glow * 0.8, 0, 2 * pi);
            cairo_fill(cr);
        }
    } else {
        cairo_set_source_rgba(cr, 0.79, 0.95, 0.43, alpha);
        cairo_set_line_width(cr, 2.5);
        cairo_move_to(cr, -6, 0);
        cairo_line_to(cr, -2, 4);
        cairo_line_to(cr, 6.5, -4.5);
        cairo_stroke(cr);
    }
    cairo_restore(cr);
}

}
