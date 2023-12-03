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
  void simulate();

private:
  int rows;
  int cols;
  std::vector<std::vector<Ward>> grid;
};

#endif
