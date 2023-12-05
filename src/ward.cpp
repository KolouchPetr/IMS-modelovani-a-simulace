#include "ward.hpp"
#include <algorithm>
#include <iostream>
#include <random>

Ward::Ward(STATE state, double area, int enemiesPerSquareMeter,
           double mortalityRate, int populationPerSquareMeter)
    : state(state), area(area), enemiesPerSquareMeter(enemiesPerSquareMeter),
      mortalityRate(mortalityRate),
      populationPerSquareMeter(populationPerSquareMeter) {}

Ward::~Ward() {}

void Ward::setState(STATE state) { this->state = state; }
STATE Ward::getState() { return this->state; }
double Ward::getMortalityRate() { return this->mortalityRate; }
int Ward::getPopulationPerSquareMeter() {
  return this->populationPerSquareMeter;
}
void Ward::setPopulationPerSquareMeter(int populationPerSquareMeter) {
  this->populationPerSquareMeter = populationPerSquareMeter;
}
double Ward::getArea() { return this->area; }
int Ward::getEnemiesPerSquareMeter() { return this->enemiesPerSquareMeter; }
void Ward::printInfo() {
  std::cout << "Population per square meter: " << this->populationPerSquareMeter
            << "\t";
}
void Ward::setMoralityRate(double mortalityRate) {
  this->mortalityRate = mortalityRate;
}
void Ward::updateState(double density,
                       const std::vector<double> &neighbourAreas,
                       const std::vector<int> &neighbourEnemies,
                       double mortalityRate,
                       const std::vector<STATE> &neighbourStates) {
  auto maxEnemyIter =
      std::max_element(neighbourEnemies.begin(), neighbourEnemies.end());
  int maxEnemyCount =
      (maxEnemyIter != neighbourEnemies.end()) ? *maxEnemyIter : 0;
  int maxEnemyIndex = std::distance(neighbourEnemies.begin(), maxEnemyIter);
  int e1t = (neighbourAreas[maxEnemyIndex] * maxEnemyCount) / this->area;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, maxEnemyCount);
  int r = dis(gen);

  double v1t_plus_1 = density - e1t * r;

  // Pesticides effect
  // v1t_plus_1 *= (1 - this->mortalityRate);

  if (v1t_plus_1 <= 0) {
    this->setState(NONE);
  } else if (v1t_plus_1 < thresholds[1]) {
    this->setState(NORMAL);
  } else if (v1t_plus_1 < thresholds[2]) {
    this->setState(LIGHT);
  } else if (v1t_plus_1 < thresholds[3]) {
    this->setState(MEDIUM);
  } else if (v1t_plus_1 < thresholds[4]) {
    this->setState(HIGH);
  } else {
    this->setState(VERY_HIGH);
  }
}
