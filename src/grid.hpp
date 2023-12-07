#ifndef GRID_HPP
#define GRID_HPP

#include "ward.hpp"
#include <bitset>
#include <unordered_map>
#include <vector>

class Grid {
public:
  Grid(std::vector<Ward> wards);
  ~Grid();
  std::unordered_map<int, Ward> initGrid(std::vector<Ward> wards);
  std::vector<Ward> getNeighbors(Ward ward);
  void simulateStep(int step, std::bitset<3> transitionRules);
  std::vector<double>
  getNeighbourAreas(Ward ward, std::unordered_map<int, Ward> wardMapCopy);
  std::vector<int>
  getNeighbourEnemies(Ward ward, std::unordered_map<int, Ward> wardMapCopy);
  void updateMortalities(int step);

  std::vector<STATE>
  getNeighboursStates(Ward ward, std::unordered_map<int, Ward> wardMapCopy);
  STATE mapState(int population);
  void printInfo();

private:
  std::unordered_map<int, Ward> wardMap;
};

#endif
