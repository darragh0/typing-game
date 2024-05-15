#include "../h/config.h"

#include <iostream>
#include <fstream>

#include <conio.h>
#include <windows.h>


int main() {

    config::parse_settings_toml();

    // Set console code page to UTF-8 so console known how to interpret string data
    SetConsoleOutputCP(CP_UTF8);

    // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(
        GetStdHandle(STD_OUTPUT_HANDLE),
        &csbi
    );

    config::TERM_COLS = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    config::TERM_ROWS = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    std::ifstream file("snippets/cpp/test.txt");
    std::string text;
    getline(file, text);

    int chr;
    int index = 0;
    bool err = false;

    system("cls");
    print_logo();

    while (index != 27) {

        showText(&text, &index, err);
        chr = _getch();

        switch (chr) {
            case SpecialChar::ESC:
                goto exit;

            case SpecialChar::BACKSPACE:
                if (!err)
                    index--;

                err = false;
                continue;

            default:
                break;
        }

        // Don't allow user to override incorrect char
        if (err) continue;

        bool correct = (chr == text[index]);
        index += correct;
        err = !correct;
    }

    exit:
        refresh_then_print("         You win!          ");

    do {chr = _getch();} while (chr != SpecialChar::ESC);

    system("cls");

    return 0;
}
