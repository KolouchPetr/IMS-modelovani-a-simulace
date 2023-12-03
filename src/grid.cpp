#include "grid.hpp"
#include <iostream>

Grid::Grid(int rows, int cols) : rows(rows), cols(cols) { grid = initGrid(); }
Grid::~Grid() {}

std::vector<std::vector<Ward>> Grid::initGrid() {
  std::vector<std::vector<Ward>> grid;
  for (int i = 0; i < this->rows; i++) {
    std::vector<Ward> row;
    for (int j = 0; j < this->cols; j++) {
      Ward ward(NONE, 0, 0, 0, 0);
      row.push_back(ward);
    }
    grid.push_back(row);
  }
  return grid;
}

void Grid::printGrid() {
  for (int i = 0; i < rows; i++) {
    std::cout << "|";
    for (int j = 0; j < cols; j++) {
      std::cout << grid[i][j].getState() << "|";
    }
    std::cout << std::endl;
  }
}

std::vector<Ward> Grid::getNeighbors(int row, int col) {
  std::vector<Ward> neighbors;
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = col - 1; j <= col + 1; j++) {
      if (i >= 0 && i < rows && j >= 0 && j < cols) {
        neighbors.push_back(grid[i][j]);
      }
    }
  }
  return neighbors;
}

std::vector<double> Grid::getNeighbourAreas(int row, int col) {
  std::vector<double> neighbourAreas;
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = col - 1; j <= col + 1; j++) {
      if (i >= 0 && i < rows && j >= 0 && j < cols) {
        neighbourAreas.push_back(grid[i][j].getArea());
      }
    }
  }
  return neighbourAreas;
}

std::vector<int> Grid::getNeighbourEnemies(int row, int col) {
  std::vector<int> neighbourEnemies;
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = col - 1; j <= col + 1; j++) {
      if (i >= 0 && i < rows && j >= 0 && j < cols) {
        neighbourEnemies.push_back(grid[i][j].getEnemiesPerSquareMeter());
      }
    }
  }
  return neighbourEnemies;
}

void Grid::simulateStep() {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->cols; j++) {
      double density = grid[i][j].getPopulationPerSquareMeter();
      std::vector<double> neighbourAreas = getNeighbourAreas(i, j);
      std::vector<int> neighbourEnemies = getNeighbourEnemies(i, j);
      grid[i][j].updateState(density, neighbourAreas, neighbourEnemies);
    }
  }
}
