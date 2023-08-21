#ifndef IO_H
#define IO_H
#include <string>

class IO {
public:
    IO();
    ~IO();
    std::string getUserInputAndPreprocess();
    std::string promptInput();
};

#endif // IO_H
