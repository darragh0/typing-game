#pragma once

#include <cstdint>
#include <exception>
#include <string>

#include "util.h"


namespace config {
    extern const char* LOGO;
    extern const uint8_t LOGO_ROWS;
    extern const uint8_t LOGO_COLS;

    extern TextAlign TEXT_ALIGN;
    extern TextMode TEXT_MODE;
    extern int TEXT_LENGTH;
    extern int TERM_ROWS;
    extern int TERM_COLS;

    extern void parse_settings_toml();

    class SettingsParsingException : public std::exception {
        private:
            const std::string msg;

        public:
            explicit SettingsParsingException(std::string msg);
            [[nodiscard]] const char* what() const noexcept override;
    };
}
