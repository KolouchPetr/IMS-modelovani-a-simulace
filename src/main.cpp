#include "grid.hpp"
#include <getopt.h>
#include <iostream>

// TODO add steps, initial conditions such as population, mortality, etc.
Grid parseArgs(int argc, char *argv[]) {
  int opt;
  int rows = 0;
  int cols = 0;
  while ((opt = getopt(argc, argv, "r:c:")) != -1) {
    switch (opt) {
    case 'r':
      rows = atoi(optarg);
      break;
    case 'c':
      cols = atoi(optarg);
      break;
    default:
      std::cout << "Usage: " << argv[0] << " -r <rows> -c <cols>" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  if (rows == 0 || cols == 0) {
    std::cout << "Usage: " << argv[0] << " -r <rows> -c <cols>" << std::endl;
    exit(EXIT_FAILURE);
  }
  Grid grid(rows, cols);
  return grid;
}

int main(int argc, char *argv[]) {
  Grid grid = parseArgs(argc, argv);
  return 0;
}
