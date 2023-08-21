#include "../headers/io.h"
#include <iostream>

int main() {
  std::string processed_text = getUserInputAndPreprocess();
  std::cout << "Processed text: " << processed_text << std::endl;
  return 0;
}