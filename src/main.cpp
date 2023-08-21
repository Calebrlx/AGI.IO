#include "../headers/Preprocessor.h"
#include <iostream>
#include <string>

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

  // Print tokenized text
  std::cout << "Tokenized text: ";
  for (const std::string& token : tokens) {
    std::cout << token << " ";
  }
  std::cout << std::endl;

  // Print processed text (concatenate the lemmatizedTokens into a single string)
  std::string processedText = "";
  for (const std::string& token : lemmatizedTokens) {
    processedText += token + " ";
  }
  std::cout << "Processed text: " << processedText << std::endl;

  return 0;
}