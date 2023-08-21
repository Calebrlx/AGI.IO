#ifndef IO_H
#define IO_H

#include <string>

// Function to get user input and return the preprocessed text
std::string getUserInputAndPreprocess();

class IO {
public:
    IO();
    ~IO();
    std::string promptInput();
};

#endif // IO_H
