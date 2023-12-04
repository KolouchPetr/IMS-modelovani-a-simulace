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
double Ward::getArea() { return this->area; }
int Ward::getEnemiesPerSquareMeter() { return this->enemiesPerSquareMeter; }

void Ward::printInfo() {
  std::cout << "Population per square meter: " << this->populationPerSquareMeter
            << "\t";
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
  int e1t = neighbourAreas[maxEnemyIndex] * maxEnemyCount;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, maxEnemyCount);
  int r = dis(gen);

  double v1t_plus_1 = density - e1t * r;

  // Pesticides effect
  v1t_plus_1 *= (1 - mortalityRate);

  // Immigration effect
  int positiveStatesSum = 0;
  int positiveStatesCount = 0;
  for (STATE state : neighbourStates) {
    if (state > NONE) {
      positiveStatesSum += state;
      positiveStatesCount++;
    }
  }

  int averageState = (positiveStatesCount > 0)
                         ? (positiveStatesSum / positiveStatesCount)
                         : this->state;
  STATE newState =
      static_cast<STATE>(std::max(static_cast<int>(this->state), averageState));

  this->setState(newState);
}
