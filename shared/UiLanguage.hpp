#pragma once

enum class UiLanguage : int { Chinese, English, French };

template<typename Char>
const Char* localized(UiLanguage language, const Char* chinese, const Char* english, const Char* french) {
    switch (language) {
        case UiLanguage::English: return english;
        case UiLanguage::French: return french;
        default: return chinese;
    }
}
