#include <iostream>
#include <string>
#include <cstdlib> // for rand and srand
#include <ctime>   // for time

int main() {
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    std::srand(std::time(nullptr)); // seed random number generator
    int guess = std::rand() % 100; // random number between 0 and 99

    std::cout << "Hello, " << name << "! I will try to guess your age.\n";
    std::cout << "My guess is: " << guess << "\n";

    std::string input;
    while (true) {
        std::cout << "Is your age UP, DOWN, or OK? (type 'up', 'down', or press Enter for OK): ";
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "Exiting program with code 0. Goodbye!\n";
            return 0;
        } else if (input == "up") {
            guess++;
            std::cout << "My new guess is: " << guess << "\n";
        } else if (input == "down") {
            guess--;
            std::cout << "My new guess is: " << guess << "\n";
        } else {
            std::cout << "Invalid input. Please type 'up', 'down', or press Enter.\n";
        }
    }
}
