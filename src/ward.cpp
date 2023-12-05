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
void Ward::setStateWithDensity(double density) {
  setPopulationPerSquareMeter(density);
  if (density <= 0) {
    this->state = NONE;
  } else if (density < thresholds[1]) {
    this->state = NORMAL;
  } else if (density < thresholds[2]) {
    this->state = LIGHT;
  } else if (density < thresholds[3]) {
    this->state = MEDIUM;
  } else if (density < thresholds[4]) {
    this->state = HIGH;
  } else {
    this->state = VERY_HIGH;
  }
}
void Ward::firstTransitionRule(double density,
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

  setStateWithDensity(v1t_plus_1);
}

void Ward::secondTransitionRule(double density,
                                const std::vector<double> &neighbourAreas,
                                const std::vector<int> &neighbourEnemies,
                                double mortalityRate,
                                const std::vector<STATE> &neighbourStates) {
  double v1t_plus_1 = density * (1 - this->mortalityRate);
  setStateWithDensity(v1t_plus_1);
}

void Ward::thirdTransitionRule(double density,
                               const std::vector<double> &neighbourAreas,
                               const std::vector<int> &neighbourEnemies,
                               double mortalityRate,
                               const std::vector<STATE> &neighbourStates) {
  int positiveStatesSum = 0;
  int positiveStatesCount = 0;
  for (STATE state : neighbourStates) {
    if (state > NONE) {
      positiveStatesSum += state;
      positiveStatesCount++;
    }
  }
  int averageState = (positiveStatesCount > 0)
                         ? positiveStatesSum / positiveStatesCount
                         : this->state;
  int deviation = abs(averageState - this->state);
  setState(static_cast<STATE>(deviation));
}
