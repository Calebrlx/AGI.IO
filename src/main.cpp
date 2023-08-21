#include "io.h"
#include <iostream>

int main() {
    IO io; // Creating an instance of the IO class
    std::string userInput = io.promptInput(); // Calling the promptInput method
    std::cout << "You typed: " << userInput << std::endl; // Printing the user input

    // Additional code can go here to process the user input or continue the program's functionality

    return 0; // Return statement to indicate successful execution
}
