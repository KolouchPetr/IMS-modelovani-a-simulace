#ifndef WARD_HPP
#define WARD_HPP
#include <vector>

enum STATE {
  NONE,
  NORMAL,
  LIGHT,
  MEDUIM,
  HIGH,
  VERY_HIGH,
};

const int thresholds[] = {0, 500, 1499, 2999, 9999};

class Ward {
public:
  Ward(STATE state, double area, int enemiesPerSquareMeter,
       double mortalityRate, int populationPerSquareMeter);
  ~Ward();
  void setState(STATE state);
  STATE getState();
  void updateState(double density, const std::vector<double> neighbourAreas,
                   const std::vector<int> neighbourEnemies);
  int getPopulationPerSquareMeter();
  double getArea();
  int getEnemiesPerSquareMeter();
  double getMortalityRate();

private:
  double area;
  int enemiesPerSquareMeter;
  double mortalityRate;
  int populationPerSquareMeter;
  STATE state;
};

#endif
