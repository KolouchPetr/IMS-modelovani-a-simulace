#ifndef GRID_HPP
#define GRID_HPP

#include "ward.hpp"
#include <vector>

class Grid {
public:
  Grid(int rows, int cols);
  ~Grid();
  void printGrid();
  std::vector<std::vector<Ward>> initGrid();
  std::vector<Ward> getNeighbors(int row, int col);
  void simulateStep();
  std::vector<double> getNeighbourAreas(int row, int col,
                                        std::vector<std::vector<Ward>> grid);
  std::vector<int> getNeighbourEnemies(int row, int col,
                                       std::vector<std::vector<Ward>> grid);

  std::vector<STATE>
  getNeighboursStates(int row, int col,
                      std::vector<std::vector<Ward>> gridCopy);
  STATE mapState(int population);

private:
  int rows;
  int cols;
  std::vector<std::vector<Ward>> grid;
};

#endif
