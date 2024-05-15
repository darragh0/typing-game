#include "../h/util.h"
#include "../h/config.h"

#include <unordered_map>
#include <iostream>
#include <string_view>
#include <fstream>
#include <sstream>
#include <random>


std::string ansi_code_str(AnsiCode code) {

    static std::unordered_map<AnsiCode, std::string> cache = {};

    if (cache.count(code))
        return cache[code];

    std::string ret;

    switch (code) {
        case AnsiCode::UNDERLINE:
            ret = "\033[4m";
            break;

        case AnsiCode::RESET:
            ret = "\033[0;0m";
            break;

        case AnsiCode::GOTO_TOP:
            ret = "\033[" + std::to_string(0) + "A";
            break;

        case AnsiCode::HIDE_CURSOR:
            ret = "\033[?25l";
            break;

        default:
            ret = "\033[" + std::to_string(code) + "m";
            break;
    }

    return (cache[code] = ret);

}


void print_logo() {

    for (int i = 0; i < config::LOGO_ROWS; i++) {
        int padding_width = (config::TERM_COLS - config::LOGO_COLS) / 2;

        const std::string_view str {
                config::LOGO + config::LOGO_COLS*i,
                config::LOGO_COLS
        };

        for (int j = 0; j < padding_width; j++)
            std::cout << ' ';

        std::cout << str << std::endl;
    }

    std::cout << "\n\n" << std::endl;

}


void refresh_then_print(const std::string& string) {

    uint8_t padding_width;

    switch (config::TEXT_ALIGN) {
        case TextAlign::LEFT:
            padding_width = 0;
            break;

        case TextAlign::CENTER:
            padding_width = (config::TERM_COLS - config::TEXT_LENGTH - 1) / 2;
            break;

        case TextAlign::RIGHT:
            padding_width = (config::TERM_COLS - config::TEXT_LENGTH - 1);
            break;
    }


    for (int i = 0; i < padding_width; i++)
        std::cout << ' ';

    std::cout << ansi_code_str(AnsiCode::GOTO_TOP)
              << ansi_code_str(AnsiCode::HIDE_CURSOR)
              << string
              << std::endl;
}


void refresh_then_print(const std::stringstream& stream) {
    refresh_then_print(stream.str());
}


void showText(const std::string* text, const int* index, bool err) {
    std::stringstream out;

    for (int i = 0; i < *index; i++)
        out << ansi_code_str(AnsiCode::GREEN)
            << (*text)[i]
            << ansi_code_str(AnsiCode::RESET);

    if (err)
        out << ansi_code_str(AnsiCode::RED);

    out << ansi_code_str(AnsiCode::UNDERLINE)
        << (*text)[*index]
        << ansi_code_str(AnsiCode::RESET);

    for (int i = *index + 1; i < text->length(); i++)
        out << (*text)[i];

    refresh_then_print(out);
}


std::string newText(TextMode mode) {

    std::stringstream text;

    switch (mode) {
        case TextMode::WORDS:
            std::random_device seeder;
            std::mt19937 engine(seeder());
            std::uniform_int_distribution<int> generator(1, 370105);

            int random_numbers[5] = {};

            for (int& random_number : random_numbers)
                random_number = generator(engine);

            std::ifstream file("text/words.txt");
            std::string line;

            int line_number = 0;
            int count = 1;

            while (count < 5) {
                std::getline(file, line);
                line_number++;

                for (int& random_number : random_numbers) {
                    if (random_number == line_number) {
                        count++;
                        text << line << (count == 5 ? "" : " ");
                    }
                }
            }

    }

    const std::string words = text.str();
    config::TEXT_LENGTH = words.length();
    return words;

}
