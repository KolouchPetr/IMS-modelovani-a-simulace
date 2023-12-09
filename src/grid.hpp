#ifndef GRID_HPP
#define GRID_HPP

#include "ward.hpp"
#include <bitset>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

/**
 * @brief The Grid class
 * @details The Grid class is a container for the wards. It is responsible for
 * the simulation of the steps and the export of the data.
 */

class Grid {
public:
  /**
   * @brief Construct a new Grid object
   *
   * @param wards The wards that will be used in the simulation
   */
  Grid(std::vector<Ward> wards);
  ~Grid();
  /**
   * @brief initialize the grid with the given wards
   *
   * @param wards The wards that will be used in the simulation
   * @return std::unordered_map<int, Ward> The initialized grid as a map with id
   * as key and ward as value
   */
  std::unordered_map<int, Ward> initGrid(std::vector<Ward> wards);
  /**
   * @brief Get the Neighbors object
   *
   * @param ward The ward for which the neighbors will be returned
   * @return std::vector<Ward> The neighbors of the given ward
   */
  std::vector<Ward> getNeighbors(Ward ward);
  /**
   * @brief simulate the given number of steps
   *
   * @param steps The number of steps that will be simulated
   * @param transitionRules The transition rules that will be used in the
   * simulation
   */
  void simulateStep(int step, std::bitset<3> transitionRules);
  /**
   * @brief get areas of the neighbors of the given ward
   *
   * @param ward The ward for which the neighbors will be returned
   * @param wardMapCopy The map of the wards
   * @return std::vector<double> The areas of the neighbors of the given ward
   */
  std::vector<double>
  getNeighbourAreas(Ward ward, std::unordered_map<int, Ward> wardMapCopy);
  /**
   * @brief get enemies per square meter of the neighbors of the given ward
   *
   * @param ward The ward for which the neighbors will be returned
   * @param wardMapCopy The map of the wards
   * @return std::vector<int> The enemies per square meter of the neighbors of
   * the given ward
   */
  std::vector<int>
  getNeighbourEnemies(Ward ward, std::unordered_map<int, Ward> wardMapCopy);
  /**
   * @brief update the mortalities of the wards
   * @details The mortalities are updated based on the efficiency of pesticides
   *
   * @param step The current step
   */
  void updateMortalities(int step);
  /**
   * @brief get states of the neighbors of the given ward
   *
   * @param ward The ward for which the neighbors will be returned
   * @param wardMapCopy The map of the wards
   * @return std::vector<STATE> The states of the neighbors of the given ward
   */
  std::vector<STATE>
  getNeighboursStates(Ward ward, std::unordered_map<int, Ward> wardMapCopy);
  /**
   * @brief converts the given population to a state
   *
   * @param population The population that will be converted
   * @return STATE The state that corresponds to the given population
   */
  STATE mapState(int population);
  /**
   * @brief print the information about the grid
   *
   */
  void printInfo();
  /**
   * @brief export the state of the grid to a file
   *
   * @param step The current step
   */
  void exportState(int step);

private:
  std::unordered_map<int, Ward> wardMap;
};

#endif
