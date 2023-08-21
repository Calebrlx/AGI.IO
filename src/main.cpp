#include "../headers/io.h"
#include <iostream>

int main() {
  IO io; // Create an instance of the IO class
  std::string processed_text = io.getUserInputAndPreprocess(); // Call the function through the instance
  std::cout << "Processed text: " << processed_text << std::endl;
  return 0;
}