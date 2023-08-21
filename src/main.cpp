#include "../headers/io.h"
#include <iostream>

int main() {
  IO io;
  std::string processed_text = io.promptInput();
  std::cout << "Processed text: " << processed_text << std::endl;
  return 0;
}