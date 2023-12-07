#include "grid.hpp"
#include "parser.hpp"
#include <getopt.h>
#include <iostream>

void parseArgs(int argc, char *argv[], int &steps) {
  int opt;
  while ((opt = getopt(argc, argv, "s:")) != -1) {
    switch (opt) {
    case 's':
      steps = atoi(optarg);
      break;
    default:
      std::cout << "Usage: " << argv[0] << "-s <steps>" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  if (steps == 0) {
    std::cerr << "No steps provided" << std::endl;
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]) {
  int steps = 0;
  std::cin.peek();
  if (!std::cin.eof()) {
    std::vector<Ward> wards = Parser::parseRowsFromFile(std::cin);
    Grid grid = Grid(wards);
    grid.printInfo();
    parseArgs(argc, argv, steps);
    // for (int i = 0; i < steps; i++) {
    //  grid.simulateStep(i);
    // }
  } else {
    std::cerr << "No input provided" << std::endl;
    exit(EXIT_FAILURE);
  }

  return 0;
}
