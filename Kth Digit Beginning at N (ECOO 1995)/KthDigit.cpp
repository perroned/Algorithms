// Written by Dan Perrone (https://github.com/perroned)
#include <fstream>
#include <iostream>
#include <sstream>
using std::endl;
using std::ostringstream;
using std::string;

// create a stringstream object, insert integer
// cast ostream to ostringstream, retrieve output
std::string intToString(int num) {
  //return static_cast<ostringstream*>(&(ostringstream() << num))->str();
  return static_cast<ostringstream*>(&(ostringstream() << num))->str();
}

// loop from n up until k digits have been assembled
// retrieve k'th digit from sum
char getDigit(int n, int k) {
  string sum = "";
  for (int current = n; sum.length() < k; current++) {
    sum += intToString(current);
  }
  return sum[k - 1];
}

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

  for (unsigned int test = 0; test < TEST_CASES; test++) {
    int n = 0, k = 0;
    infile >> n >> k;
    std::cout << getDigit(n, k) << endl;
  }
  std::getchar();
  return 0;
}
