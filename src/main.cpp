#include "../headers/Preprocessor.h"
#include <iostream>

int main() {
  Preprocessor preprocessor;
  std::cout << "Type something: ";
  std::string userInput;
  std::getline(std::cin, userInput);

  // Apply preprocessing steps
  std::vector<std::string> tokens = preprocessor.tokenize(userInput);
  std::string lowercaseText = preprocessor.toLowerCase(userInput);
  std::string noPunctuationText = preprocessor.removePunctuation(lowercaseText);
  std::vector<std::string> noStopwordsTokens = preprocessor.removeStopwords(tokens);
  std::vector<std::string> stemmedTokens = preprocessor.stem(noStopwordsTokens);
  std::vector<std::string> lemmatizedTokens = preprocessor.lemmatize(stemmedTokens);

  // Print processed text (you may want to concatenate the lemmatizedTokens into a single string)
  std::cout << "Processed text: " << noPunctuationText << std::endl;

  return 0;
}