#include "../h/config.h"

#include <iostream>

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

    const std::string text = newText(config::TEXT_MODE);

    int chr;
    int index = 0;
    bool err = false;

    system("cls");
    print_logo();

    showText(&text, &index, err);

    while (index != config::TEXT_LENGTH) {

        chr = _getch();

        switch (chr) {
            case SpecialChar::ESC:
                goto exit;

            case SpecialChar::BACKSPACE:
                if (!err)
                    index--;

                err = false;
                break;

            default:
                // Don't allow user to override incorrect char
                if (err) continue;

                bool correct = (chr == text[index]);
                index += correct;
                err = !correct;
                break;
        }

        showText(&text, &index, err);
    }

    exit:
        const std::string msg = "You win!";
        std::stringstream msg_output;
        const size_t padding_width = (config::TERM_COLS - msg.length()) / 2;

        for (int i = 0; i < padding_width; i++)
            msg_output << ' ';

        msg_output << msg;
        std::cout << '\n' << msg_output.str() << std::endl;

    do {chr = _getch();} while (chr != SpecialChar::ESC);

    system("cls");

    return 0;
}
