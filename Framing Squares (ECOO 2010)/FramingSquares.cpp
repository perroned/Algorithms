// Written by Dan Perrone (https://github.com/perroned)
#include <fstream>
#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

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
    int frameWithMat = 0, framing = 0, height = 0, horizontal = 0, matting = 0, vertical = 0, width = 0;

    // input of individual dimensions
    infile >> vertical >> horizontal >> matting >> framing;
    // calculate portrait dimensions
    height = vertical + (matting * 2) + (framing * 2);
    width = horizontal + (matting * 2) + (framing * 2);
    frameWithMat = framing + matting;
    // create picture filled with frame characters
    vector<vector<char>> picture(height, vector<char> (width, '#'));

    // insert matting and painting
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        if (y >= framing && y < (height - framing) && x >= framing && x < (width - framing)) {
          picture[y][x] = '+';
        }
        if (y >= (frameWithMat) && y < (height - frameWithMat) &&
          x >= (frameWithMat) && x < (width - frameWithMat)) {
          picture[y][x] = '.';
        }
      }
    }

    // display portrait
    for (auto& y : picture) {
      for (auto& x : y) {
        cout << x;
      }
      cout << endl;
    }
    cout << endl;
  }
  std::getchar();
  return 0;
}
