#include "ward.hpp"
#include <algorithm>
#include <iostream>

Ward::Ward(STATE state, double area, int enemiesPerSquareMeter,
           double mortalityRate, int populationPerSquareMeter)
    : state(state), area(area), enemiesPerSquareMeter(enemiesPerSquareMeter),
      mortalityRate(mortalityRate),
      populationPerSquareMeter(populationPerSquareMeter) {}

Ward::~Ward() {}

void Ward::setState(STATE state) { this->state = state; }
STATE Ward::getState() { return this->state; }
void Ward::updateState(double density, const std::vector<double> neighbourAreas,
                       const std::vector<int> neighbourEnemies) {

  int maxEnemyCount =
      *std::max_element(neighbourEnemies.begin(), neighbourEnemies.end());
  int e1_t = static_cast<int>(this->area * this->enemiesPerSquareMeter);
  double v1_t_1 =
      density * -e1_t *
      ((rand() % maxEnemyCount) / static_cast<double>(maxEnemyCount));

  if (v1_t_1 < 0) {
    this->setState(NONE);
  } else if (v1_t_1 < thresholds[1]) {
    this->setState(NORMAL);
  } else if (v1_t_1 < thresholds[2]) {
    this->setState(LIGHT);
  } else if (v1_t_1 < thresholds[3]) {
    this->setState(MEDUIM);
  } else if (v1_t_1 < thresholds[4]) {
    this->setState(HIGH);
  } else {
    this->setState(VERY_HIGH);
  }
}

double Ward::getMortalityRate() { return this->mortalityRate; }
int Ward::getPopulationPerSquareMeter() {
  return this->populationPerSquareMeter;
}
double Ward::getArea() { return this->area; }
int Ward::getEnemiesPerSquareMeter() { return this->enemiesPerSquareMeter; }
