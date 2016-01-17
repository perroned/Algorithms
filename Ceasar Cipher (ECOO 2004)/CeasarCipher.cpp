// Written by Dan Perrone (https://github.com/perroned)
#include <fstream>
#include <iostream>
#include <map>
#include <string>
using std::cout;
using std::string;

int main(int argc, char *argv[]) {
  // should only receive 1 user specified arg, file with full absolute path
  if (argc != 2) {
    std::cerr << "must provide a data file argument";
    return -1;
  }

  std::ifstream infile(argv[1]);

  if (!infile) {
    std::cerr << "failed to open file";
    return -1;
  }

  const int TEST_CASES = 5;
  const unsigned char SHIFT = 'E';

  for (unsigned int test = 0; test < TEST_CASES; test++) {
    string line = "", input = "";

    while(std::getline(infile, line)) {
      if (line.find("***") == 0) {
        break;
      }
      input += line + "\n";
    }

    // find the letter that occurs the most
    char most = '\0';
    std::map<char, int> alphabet;
    for (char c: input) {
      if (isalpha(c)) {
        alphabet[c]++;
        if (alphabet[c] > alphabet[most]) {
          most = c;
        }
      }
    }

    // determine how much to shift each letter by
    int shiftAmount = most - SHIFT;
    for (char c: input) {
      if (isalpha(c)) {
        // wrap around from A to Z
        if (c - shiftAmount < 'A') {
          int offset = c - 'A';
          c -= offset;
          // count back from end of alphabet
          c += 26 - (shiftAmount - offset);
        } else {
          // can just shift without worrying about wrapping
          c -= shiftAmount;
        }
      }
      cout << c;
    }
    cout << std::endl;
  }

  std::getchar();
  return 0;
}
