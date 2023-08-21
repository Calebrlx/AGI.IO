#include "../headers/Preprocessor.h"
#include <iostream>

int main() {
  Preprocessor io;
  std::string processed_text = io.promptInput();
  std::cout << "Processed text: " << processed_text << std::endl;
  return 0;
}