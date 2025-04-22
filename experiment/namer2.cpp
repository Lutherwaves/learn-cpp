#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#if defined(_WIN32)
#include <conio.h>
#elif defined(__unix__)
#include <termios.h>
#include <unistd.h>
#endif

// Platform-specific input setup/cleanup
void init_input(bool enable) {
    #if defined(__unix__)
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
    #endif
}

int get_key() {
    #if defined(_WIN32)
    return _getch();
    #elif defined(__unix__)
    return getchar();
    #endif
}

int main() {
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int guess = std::rand() % 100;

    std::cout << "Hello, " << name << "! I'm guessing your age.\n";
    std::cout << "Initial guess: " << guess << "\n";
    std::cout << "Use arrow keys (↑/↓) to adjust, Enter to confirm.\n";

    #if defined(__unix__)
    init_input(true);
    #endif

    while(true) {
        int ch = get_key();
        
        #if defined(_WIN32)
        if (ch == 13) break; // Enter
        if (ch == 224) { // Arrow keys
            int arrow = get_key();
            if (arrow == 72) guess++;      // Up
            else if (arrow == 80) guess--; // Down
        }
        #elif defined(__unix__)
        if (ch == '\n' || ch == '\r') break; // Enter
        if (ch == 27 && get_key() == '[') {  // Escape sequence
            char arrow = get_key();
            if (arrow == 'A') guess++;      // Up
            else if (arrow == 'B') guess--; // Down
        }
        #endif

        std::cout << "\rCurrent guess: " << guess << "     " << std::flush;
    }

    #if defined(__unix__)
    init_input(false);
    #endif

    std::cout << "\nFinal age confirmed: " << guess << "!\n";
    return 0;
}
