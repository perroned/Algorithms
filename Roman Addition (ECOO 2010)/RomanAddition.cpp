// Written by Dan Perrone (https://github.com/perroned)
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
using std::cout;
using std::string;

// conversation table of Roman numerals to decimal representation
const std::vector<std::pair <int, string>> lookup{
  { 1000, "M" },
  { 900, "CM" },
  { 500, "D" },
  { 400, "CD" },
  { 100, "C" },
  { 90, "XC" },
  { 50, "L" },
  { 40, "XL" },
  { 10, "X" },
  { 9, "IX" },
  { 5, "V" },
  { 4, "IV" },
  { 1, "I" } };

// break the number down and build the Roman representation
// look up the largest Roman representation, and subtract
// its value from the decimal until it reaches 0
string decimalToRoman(int decimal, string roman = "") {
  if (decimal > 0) {
    for (auto& p : lookup) {
      if (decimal >= p.first) {
        decimal -= p.first;
        roman += p.second;
        return decimalToRoman(decimal, roman);
      }
    }
  }
  return roman;
}

// cycle character by character through the Roman string.
// look up the character's largest representation and store it.
// add them
int romanToDecimal(string input) {
  std::vector<int> values;
  for (char c : input) {
    for (auto& p : lookup) {
      if (p.second.length() == 1 && c == p.second[0]) {
        values.push_back(p.first);
      }
    }
  }

  unsigned int total = 0;
  for (unsigned int i = 0; i < values.size(); i++) {
    // if the current number is smallest than the next, substract it
    // otherwise add its value to the sum
    if ((i + 1 < values.size()) && (values[i + 1] > values[i])) {
      total -= values[i];
    } else {
      total += values[i];
    }
  }
  return total;
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
    string roman1, roman2;
    infile >> roman1 >> roman2;
    unsigned int decimal1 = romanToDecimal(roman1);
    unsigned int decimal2 = romanToDecimal(roman2);
    unsigned int decimalAnswer = decimal1 + decimal2;

    cout << roman1 << " + " << roman2 << " = " << decimalToRoman(decimalAnswer) << std::endl;
  }

  std::getchar();
  return 0;
}
