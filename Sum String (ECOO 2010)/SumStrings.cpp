// Written by Dan Perrone (https://github.com/perroned)
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

//
void doCount(const vector<unsigned int>& grid, unsigned int sum, unsigned int& totalSumCount) {
  // loop through every element in the data
  // both rows and columns are treated the same
  for (unsigned int index = 0; index < grid.size(); index++) {
    unsigned int currentColumnSum = 0, i = index;
    // start counting the sum from the current index
    while (currentColumnSum < sum && i < grid.size()) {
      // add each element to the sum
      currentColumnSum += grid[i];
      i++;
    }
    // check if the sum has been reached
    if (currentColumnSum == sum) {
      totalSumCount++;
    }
  }
}

// cycke through each column and count the substrings
int getColSums(const vector<vector<unsigned int>>& grid, unsigned int sum) {
  unsigned int totalColumnSumCount = 0;

  for (unsigned int x = 0; x < grid[0].size(); x++) {
    vector<unsigned int> column;
    // cycle through each row, and grab the x'th element of the column
    for (auto& y: grid) {
      column.push_back(y[x]);
    }
    doCount(column, sum, totalColumnSumCount);
  }
  return totalColumnSumCount;
}

// cycle through all the rows of the grid
int getRowSums(const vector<vector<unsigned int>>& grid, unsigned int sum) {
  unsigned int totalRowSumCount = 0;

  // loop through each row in the grid and perform the count
  for (auto& row: grid) {
    doCount(row, sum, totalRowSumCount);
  }
  return totalRowSumCount;
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
    // fetch grid size and sum
    unsigned int height, width, sum;
    infile >> height >> width >> sum;
    infile.ignore();
    vector<vector<unsigned int>> grid;

    // populate the grid with file data
    for (unsigned int y = 0; y < height; y++) {
      grid.push_back({});
      for (unsigned int x = 0; x < width; x++) {
        grid[y].push_back(infile.get() - '0');
      }
      infile.ignore();
    }

    // retrieve the count
    unsigned int count = getRowSums(grid, sum) + getColSums(grid, sum);
    cout << "There are " << count << " strings of " << sum << endl;
  }
  std::getchar();
  return 0;
}
