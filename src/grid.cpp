#include "grid.hpp"
#include "ward.hpp"
#include <iostream>
#include <random>

Grid::Grid(int rows, int cols) : rows(rows), cols(cols) { grid = initGrid(); }
Grid::~Grid() {}

std::vector<std::vector<Ward>> Grid::initGrid() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrPopulation(0, 500);
  std::uniform_int_distribution<> distrEnemies(0, 10);
  std::uniform_real_distribution<> distrArea(0.0, 10.0);
  std::uniform_real_distribution<> distrMortality(0.0, 1.0);
  std::vector<std::vector<Ward>> grid;
  for (int i = 0; i < this->rows; i++) {
    std::vector<Ward> row;
    for (int j = 0; j < this->cols; j++) {
      int population = distrPopulation(gen);
      STATE state = mapState(population);
      Ward ward(state, distrArea(gen), distrEnemies(gen), distrMortality(gen),
                population);
      row.push_back(ward);
    }
    grid.push_back(row);
  }
  return grid;
}

STATE Grid::mapState(int population) {
  if (population < thresholds[0]) {
    return NONE;
  } else if (population <= thresholds[1]) {
    return NORMAL;
  } else if (population <= thresholds[2]) {
    return LIGHT;
  } else if (population <= thresholds[3]) {
    return MEDIUM;
  } else if (population <= thresholds[4]) {
    return HIGH;
  } else {
    return VERY_HIGH;
  }
}

void Grid::printGrid() {
  for (int i = 0; i < rows; i++) {
    std::cout << "|";
    for (int j = 0; j < cols; j++) {
      std::cout << grid[i][j].getState() << "|";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
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

std::vector<double>
Grid::getNeighbourAreas(int row, int col,
                        std::vector<std::vector<Ward>> gridCopy) {
  std::vector<double> neighbourAreas;
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = col - 1; j <= col + 1; j++) {
      if (i >= 0 && i < rows && j >= 0 && j < cols) {
        neighbourAreas.push_back(gridCopy[i][j].getArea());
      }
    }
  }
  return neighbourAreas;
}

std::vector<int>
Grid::getNeighbourEnemies(int row, int col,
                          std::vector<std::vector<Ward>> gridCopy) {
  std::vector<int> neighbourEnemies;
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = col - 1; j <= col + 1; j++) {
      if (i >= 0 && i < rows && j >= 0 && j < cols) {
        neighbourEnemies.push_back(gridCopy[i][j].getEnemiesPerSquareMeter());
      }
    }
  }
  return neighbourEnemies;
}

std::vector<STATE>
Grid::getNeighboursStates(int row, int col,
                          std::vector<std::vector<Ward>> gridCopy) {
  std::vector<STATE> neighbourStates;
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = col - 1; j <= col + 1; j++) {
      if (i >= 0 && i < rows && j >= 0 && j < cols) {
        neighbourStates.push_back(gridCopy[i][j].getState());
      }
    }
  }
  return neighbourStates;
}

void Grid::simulateStep() {
  std::vector<std::vector<Ward>> gridCopy = grid;

  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->cols; j++) {
      double density = gridCopy[i][j].getPopulationPerSquareMeter();
      std::vector<double> neighbourAreas = getNeighbourAreas(i, j, gridCopy);
      std::vector<int> neighbourEnemies = getNeighbourEnemies(i, j, gridCopy);
      std::vector<STATE> neighboursStates = getNeighboursStates(i, j, gridCopy);
      double mortalityRate = gridCopy[i][j].getMortalityRate();
      grid[i][j].updateState(density, neighbourAreas, neighbourEnemies,
                             mortalityRate, neighboursStates);

      grid[i][j].printInfo();
      std::cout << std::endl;
    }
  }
}
