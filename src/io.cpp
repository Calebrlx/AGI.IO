#include "io.h"
#include <iostream>

IO::IO() {
    // Constructor implementation (if needed)
}

IO::~IO() {
    // Destructor implementation (if needed)
}

std::string IO::promptInput() {
    std::cout << "Type something: ";
    std::string userInput;
    std::getline(std::cin, userInput);
    return userInput;
}
