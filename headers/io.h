#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <string>
#include <vector>

class Preprocessor {
public:
    Preprocessor(); // Constructor to initialize any necessary resources

    // Tokenize the input text into words or subwords
    std::vector<std::string> tokenize(const std::string& text);

    // Convert all characters to lowercase
    std::string toLowerCase(const std::string& text);

    // Remove punctuation and special characters
    std::string removePunctuation(const std::string& text);

    // Remove common stopwords
    std::vector<std::string> removeStopwords(const std::vector<std::string>& tokens);

    // Apply stemming to reduce words to their root form
    std::vector<std::string> stem(const std::vector<std::string>& tokens);

    // Apply lemmatization to reduce words to their base or root form
    std::vector<std::string> lemmatize(const std::vector<std::string>& tokens);

    // Convert words to vectors using pre-trained embeddings
    std::vector<std::vector<float>> wordEmbeddings(const std::vector<std::string>& tokens);

    // Pad sequences to the same length
    std::vector<std::vector<float>> padSequences(const std::vector<std::vector<float>>& sequences, int length);

    // Process the entire text using the enabled preprocessing steps
    std::vector<std::vector<float>> preprocess(const std::string& text);

private:
    // Private methods for additional functionality, such as initializing resources
};

#endif // PREPROCESSOR_H

