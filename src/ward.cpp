#include "ward.hpp"
#include <algorithm>
#include <iostream>
#include <random>

Ward::Ward()
    : id(0), area(0.0), enemiesPerSquareMeter(0), mortalityRate(0.0),
      populationPerSquareMeter(0) {
  setStateWithDensity(0.0);
}
Ward::Ward(int id, std::string name, double area, int enemiesPerSquareMeter,
           double mortalityRate, int populationPerSquareMeter,
           std::vector<int> neighbourIDs)
    : id(id), name(name), area(area),
      enemiesPerSquareMeter(enemiesPerSquareMeter),
      mortalityRate(mortalityRate),
      populationPerSquareMeter(populationPerSquareMeter),
      neighbourIDs(neighbourIDs) {
  setStateWithDensity(populationPerSquareMeter);
}
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
  std::cout << "ID: " << this->id << std::endl;
  std::cout << "Name: " << this->name << std::endl;
  std::cout << "Area: " << this->area << std::endl;
  std::cout << "Enemies per square meter: " << this->enemiesPerSquareMeter
            << std::endl;
  std::cout << "Mortality rate: " << this->mortalityRate << std::endl;
  std::cout << "Population per square meter: " << this->populationPerSquareMeter
            << std::endl;
  std::cout << "Neighbour IDs: ";
  for (int neighbourID : this->neighbourIDs) {
    std::cout << neighbourID << " ";
  }
  std::cout << std::endl;
  std::cout << "State: " << this->state << std::endl;
}
void Ward::setMoralityRate(double mortalityRate) {
  this->mortalityRate = mortalityRate;
}
void Ward::setStateWithDensity(double density) {
  if (density < 0) {
    density = 0;
  }
  setPopulationPerSquareMeter(density);
  if (density <= thresholds[0]) {
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
// killed by natural enemies
void Ward::firstTransitionRule(double density,
                               const std::vector<double> &neighbourAreas,
                               const std::vector<int> &neighbourEnemies) {
  auto maxEnemyIter =
      std::max_element(neighbourEnemies.begin(), neighbourEnemies.end());
  int maxEnemyCount =
      (maxEnemyIter != neighbourEnemies.end()) ? *maxEnemyIter : 0;
  int maxEnemyIndex = std::distance(neighbourEnemies.begin(), maxEnemyIter);
  /*std::cout << this->getID()
            << " maxEnemy: " << neighbourAreas[maxEnemyIndex]
            << " maxEnemyCount: " << maxEnemyCount
            << " Area: " << this->area << std::endl; */
  int e1t = (neighbourAreas[maxEnemyIndex] * maxEnemyCount) / this->area;

  std::random_device rd;
  std::mt19937 gen(rd());
  // FIXME this
  std::uniform_int_distribution<> dis(0, 2);
  int r = dis(gen);

  double v1t_plus_1 = density - e1t * r;
  setStateWithDensity(v1t_plus_1);
}

// killed by pesticides
void Ward::secondTransitionRule(double density) {
  double v1t_plus_1 = density * (1 - this->mortalityRate);
  setStateWithDensity(v1t_plus_1);
}

// natural migration - state based
void Ward::thirdTransitionRule(const std::vector<STATE> &neighbourStates) {
  int positiveStatesSum = 0;
  int positiveStatesCount = 0;
  for (STATE state : neighbourStates) {
    if (state >= NORMAL) {
      positiveStatesSum += state;
      positiveStatesCount++;
    }
  }
  int averageState = (positiveStatesCount > 0)
                         ? positiveStatesSum / positiveStatesCount
                         : 0;
  int deviation = abs(averageState - this->state);
  setState(static_cast<STATE>(deviation));
}
