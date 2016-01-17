// Written by Dan Perrone (https://github.com/perroned)
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

// set found to true if the character has previously been marked
// as a character passed over. Otherwise the function will print
// the character and mark the character as passed over
void markCharacter(char& character, bool& found) {
  if (character == '@') {
    found = true;
  } else {
    cout << character;
    character = '@';
  }
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
      int height, width;
      infile >> height >> width;
      vector<string> grid;
      infile.ignore();
      for (int i = 0; i < height; i++) {
        string line;
        getline(infile, line);
        grid.push_back(line);
      }
      
      int distance = 1, startX = 0, startY = 0, x, y;
      bool found = false;
      // locate center
      for (y = 0; !found && y < height; y++) {
        for (x = 0; !found && x < width; x++) {
          if (grid[y][x] == '@') {
            startY = y;
            startX = x;
            found = true;
            break;
          }
        }
      }

      // keep printing until a marked character is processed
      for (x = startX, y = startY, found = false; !found;) {
        // print a vertical column ascending
        // distance is the amount of character to ascend over
        // check we don't get lower below zero
        // exit if a character has been marked
        for (int i = 1; (i <= distance) && ((y - i) >= 0) && !found; i++) {
          markCharacter(grid[y - i][x], found);
        }

        // move the position the amount of characters just printed
        // bounds checking
        y = std::max(y - distance, 0);

        // left
        for (int i = 1; (i <= distance) && ((x - i) >= 0) && !found; i++) {
          markCharacter(grid[y][x - i], found);
        }
        x = std::max(x - distance, 0);

        // went half way around the spiral, increase the amount of
        // characters that need to be printed to loop around corners
        distance++;

        // down
        for (int i = 1; (i <= distance) && ((y + i) < height) && !found; i++) {
          markCharacter(grid[y + i][x], found);
        }
        y = std::min(y + distance, height - 1);

        // right
        for (int i = 1; (i <= distance) && ((x + i) < width) && !found; i++) {
          markCharacter(grid[y][x + i], found);
        }
        x = std::min(x + distance, width - 1);
        distance++;

        // escape if the amount of characters getting printed exceeds
        // the vertical or horizontal size of the grid
        if ((distance > width) || (distance > height)) {
          found = true;
        }
      }
      cout << endl;
    }
  
  std::getchar();
  return 0;
}

