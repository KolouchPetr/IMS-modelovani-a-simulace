#include "ward.hpp"
#include <iostream>

Ward::Ward(STATE state, double area, int enemiesPerSquareMeter,
           double mortalityRate, int populationPerSquareMeter)
    : state(state), area(area), enemiesPerSquareMeter(enemiesPerSquareMeter),
      mortalityRate(mortalityRate),
      populationPerSquareMeter(populationPerSquareMeter) {}

Ward::~Ward() {}

void Ward::setState(STATE state) { this->state = state; }
STATE Ward::getState() { return this->state; }
