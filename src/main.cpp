#include "grid.hpp"
#include "parser.hpp"
#include <bitset>
#include <getopt.h>
#include <iostream>

/**
 * @brief parse the arguments
 *
 * @param argc The number of arguments
 * @param argv The arguments
 * @param steps The number of steps that will be simulated
 * @param transitionRules The transition rules that will be used in the
 * simulation
 */
void parseArgs(int argc, char *argv[], int &steps,
               std::bitset<3> &transitionRules) {
  int opt;
  while ((opt = getopt(argc, argv, "s:123")) != -1) {
    switch (opt) {
    case 's':
      steps = atoi(optarg);
      break;
    case '1':
      transitionRules.set(0);
      break;
    case '2':
      transitionRules.set(1);
      break;
    case '3':
      transitionRules.set(2);
      break;
    default:
      std::cout << "Usage: " << argv[0] << "-s <steps> [-1] [-2] [-3]"
                << std::endl;
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
  std::bitset<3> transitionRules;
  std::cin.peek();
  if (!std::cin.eof()) {
    std::vector<Ward> wards = Parser::parseRowsFromFile(std::cin);
    Grid grid = Grid(wards);
    // grid.printInfo();
    grid.exportState(0);
    // std::cout << "---------------------" << std::endl;
    parseArgs(argc, argv, steps, transitionRules);
    for (int i = 0; i < steps; i++) {
      grid.simulateStep(i, transitionRules);
      // grid.printInfo();
      grid.exportState(i + 1);
      // std::cout << "---------------------" << std::endl;
    }
  } else {
    std::cerr << "No input provided" << std::endl;
    exit(EXIT_FAILURE);
  }

  return 0;
}
