#include "grid.hpp"
#include "ward.hpp"
#include <iostream>
#include <math.h>

Grid::Grid(std::vector<Ward> wards) { wardMap = initGrid(wards); }
Grid::~Grid() {}

std::unordered_map<int, Ward> Grid::initGrid(std::vector<Ward> wards) {
  std::unordered_map<int, Ward> wardMap;
  for (auto &ward : wards) {
    wardMap.insert({ward.getID(), ward});
  }
  return wardMap;
}

STATE Grid::mapState(int population) {
  if (population <= thresholds[0]) {
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

void Grid::printInfo() {
  for (auto &ward : wardMap) {
    std::cout << "Ward " << ward.second.getName() << " has "
              << ward.second.getPopulationPerSquareMeter()
              << " PHB per square meter and is in state "
              << ward.second.getState() << std::endl;
  }
}

std::vector<Ward> Grid::getNeighbors(Ward ward) {
  std::vector<Ward> neighbours;
  for (int neighbourID : ward.getNeighbourIDs()) {
    neighbours.push_back(wardMap[neighbourID]);
  }
  return neighbours;
}

std::vector<double>
Grid::getNeighbourAreas(Ward ward, std::unordered_map<int, Ward> wardMapCopy) {
  std::vector<double> neighbourAreas;
  for (int neighbourID : ward.getNeighbourIDs()) {
    neighbourAreas.push_back(wardMapCopy[neighbourID].getArea());
  }
  return neighbourAreas;
}

std::vector<int>
Grid::getNeighbourEnemies(Ward ward,
                          std::unordered_map<int, Ward> wardMapCopy) {
  std::vector<int> neighbourEnemies;
  for (int neighbourID : ward.getNeighbourIDs()) {
    neighbourEnemies.push_back(
        wardMapCopy[neighbourID].getEnemiesPerSquareMeter());
  }
  return neighbourEnemies;
}

void Grid::updateMortalities(int step) {
  for (auto &ward : wardMap) {
    double mortalityRate = ward.second.getMortalityRate();
    mortalityRate += exp(0.1 * step);
    ward.second.setMoralityRate(mortalityRate);
  }
}

std::vector<STATE>
Grid::getNeighboursStates(Ward ward,
                          std::unordered_map<int, Ward> wardMapCopy) {
  std::vector<STATE> neighbourStates;
  for (int neighbourID : ward.getNeighbourIDs()) {
    neighbourStates.push_back(wardMapCopy[neighbourID].getState());
  }
  return neighbourStates;
}

void Grid::simulateStep(int step, std::bitset<3> transitionRules) {
  std::unordered_map<int, Ward> wardMapCopy = wardMap;

  for (auto &ward : wardMap) {
    double density = ward.second.getPopulationPerSquareMeter();
    std::vector<double> neighbourAreas =
        getNeighbourAreas(ward.second, wardMapCopy);
    std::vector<int> neighbourEnemies =
        getNeighbourEnemies(ward.second, wardMapCopy);
    std::vector<STATE> neighboursStates =
        getNeighboursStates(ward.second, wardMapCopy);

    if (transitionRules[0]) {
      ward.second.firstTransitionRule(density, neighbourAreas,
                                      neighbourEnemies);
    }
    if (transitionRules[1]) {
      this->updateMortalities(step);
      ward.second.secondTransitionRule(density);
    }
    if (transitionRules[2]) {
      ward.second.thirdTransitionRule(neighboursStates);
    }
  }
}
