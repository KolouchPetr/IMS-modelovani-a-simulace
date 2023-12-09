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
    std::cout << "Ward ID " << ward.second.getID() << " named " << ward.second.getName() << " has "
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
  //int count = 0;
  //double sum = 0;

  for (auto &ward : wardMap) {
    double mortalityRate = ward.second.getMortalityRate();
    mortalityRate += (exp(0.4 * step))/44;
    if(mortalityRate > 1){
        mortalityRate = 1;
    }
    //count++;
    //sum += mortalityRate;
    //std::cout << "Day: " << step << " mord rate: " << mortalityRate << std::endl;
    ward.second.setMoralityRate(mortalityRate);
  }
  //std::cout << "Avg: " << sum/count << std::endl;

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

void Grid::exportState(int step) {
  std::ofstream file("../output/states" + std::to_string(step) + ".csv");

  if (!file.is_open()) {
    std::cerr << "Error: file not open" << std::endl;
    exit(1);
  }
  for (auto &ward : wardMap) {
    file << ward.second.getID() << "," << ward.second.getName() << ","
         << ward.second.getState() << ","
         << ward.second.getPopulationPerSquareMeter() << std::endl;
  }
  file.close();
}

void Grid::simulateStep(int step, std::bitset<3> transitionRules) {
  std::unordered_map<int, Ward> wardMapCopy = wardMap;

  if (transitionRules[1]) {
    this->updateMortalities(step);
  }

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
      ward.second.secondTransitionRule(density);
    }
    if (transitionRules[2]) {
      ward.second.thirdTransitionRule(neighboursStates);
    }
  }
}
