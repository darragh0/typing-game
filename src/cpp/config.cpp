#include "../h/config.h"

#include <iostream>
#include <fstream>
#include <unordered_map>


const uint8_t config::LOGO_ROWS = 6;
const uint8_t config::LOGO_COLS = 44;

const char* config::LOGO =
    u8"    __   _ __  __        __                 "
    u8"   / /__(_) /_/ /___  __/ /___  ______  ___ "
    u8"  / //_/ / __/ __/ / / / __/ / / / __ \\/ _ \\"
    u8" / ,< / / /_/ /_/ /_/ / /_/ /_/ / /_/ /  __/"
    u8"/_/|_/_/\\__/\\__/\\__, /\\__/\\__, / .___/\\___/ "
    u8"               /____/    /____/_/           ";

int config::TERM_ROWS = 0;
int config::TERM_COLS = 0;
TextAlign config::TEXT_ALIGN = TextAlign::LEFT;
TextMode config::TEXT_MODE = TextMode::WORDS;
int config::TEXT_LENGTH = 0;


void config::parse_settings_toml() {

    std::fstream file("config/settings.toml");
    std::string line;
    const char partition = '=';

    std::cout << "Settings:\n";

    while (std::getline(file, line)) {
        size_t symbol_partition = line.find(partition);
        const std::string name = line.substr(0, symbol_partition - 1);
        const std::string value = line.substr(
            symbol_partition + 3,
            line.length() - 1 - symbol_partition - 3
        );

        std::cout << "'" << name << "', " << "'" << value << "'" << std::endl;

        if (name == "text-align") {
            if (value == "left")
                TEXT_ALIGN = TextAlign::LEFT;
            if (value == "center")
                TEXT_ALIGN = TextAlign::CENTER;
            else if (value == "right")
                TEXT_ALIGN = TextAlign::RIGHT;
            else
                throw SettingsParsingException("Missing or invalid value for setting 'text-align': '" + value + "'");
        }

        else if (name == "text-mode") {
            if (value == "words")
                TEXT_MODE = TextMode::WORDS;
            else
                throw SettingsParsingException("Missing or invalid value for setting 'text-mode': '" + value + "'");
        }

    }
}


config::SettingsParsingException::SettingsParsingException(std::string msg)
    : msg(std::move(msg)) {}


const char* config::SettingsParsingException::what() const noexcept {
    return this->msg.c_str();
}
