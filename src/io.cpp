#include "../headers/io.h"
#include <iostream>
#include <fst/fstlib.h>
#include <string>
#include <sstream>
#include <cctype>

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

  // Create TextPreprocessor object
  TextPreprocessor preprocessor;

  // Preprocess the user input
  return preprocessor.preprocess(userInput);
}

class TextPreprocessor {
public:
  // Constructor
  TextPreprocessor() {
    // Initialize FST
    initFST();
  }

  // Function to preprocess a given text
  std::string preprocess(const std::string& input_text) {
    std::string result;
    fst::StdVectorFst output;

    // Start from the initial state
    int current_state = fst_.Start();

    // Iterate through the input text
    for (char c : input_text) {
      if (std::isalnum(c) || c == ' ') {
        // Follow the transition for the current character
        fst::ArcIterator<fst::StdVectorFst> aiter(fst_, current_state);
        for (; !aiter.Done(); aiter.Next()) {
          const fst::StdArc &arc = aiter.Value();
          if (arc.ilabel == std::tolower(c)) {
            result.push_back(arc.olabel);
            current_state = arc.nextstate;
            break;
          }
        }
      }
    }

    return result;
  }

private:
  // FST for preprocessing
  fst::StdVectorFst fst_;

  // Initialize the FST
  void initFST() {
    int start = fst_.AddState();
    fst_.SetStart(start);

    // Add transitions for lowercase characters and space
    int current_state = start;
    for (char c = 'a'; c <= 'z'; c++) {
      int next_state = fst_.AddState();
      fst_.AddArc(current_state, fst::StdArc(c, c, 0, next_state));
      current_state = next_state;
    }
    for (char c = 'A'; c <= 'Z'; c++) {
      int next_state = fst_.AddState();
      fst_.AddArc(current_state, fst::StdArc(c, std::tolower(c), 0, next_state));
      current_state = next_state;
    }
    // Add transition for space (tokenization)
    int space_state = fst_.AddState();
    fst_.AddArc(current_state, fst::StdArc(' ', ' ', 0, space_state));
    fst_.SetFinal(space_state, 0);
  }
};