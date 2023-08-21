#ifndef IO_H
#define IO_H
#include <string>
#include <fst/fstlib.h>

class TextPreprocessor {
public:
  TextPreprocessor();
  std::string preprocess(const std::string& input_text);

private:
  fst::StdVectorFst fst_;
  void initFST();
};

class IO {
public:
    IO();
    ~IO();
    std::string getUserInputAndPreprocess();
    std::string promptInput();
};

#endif // IO_H
