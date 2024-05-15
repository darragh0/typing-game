#pragma once

#include <string>
#include <sstream>


enum TextAlign {
    LEFT = 0,
    CENTER = 1,
    RIGHT = 2
};


enum AnsiCode {
    RESET,
    GOTO_TOP,
    HIDE_CURSOR,
    UNDERLINE,
    RED = 91,
    GREEN = 92
};


enum SpecialChar {
    BACKSPACE = 8,
    ESC = 27
};


const std::string ansi_code_str(AnsiCode code);
void print_logo();
void refresh_then_print(const std::string& stream);
void refresh_then_print(const std::stringstream& stream);
void showText(const std::string* text, const int* index, bool err);
