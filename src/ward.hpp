#ifndef WARD_HPP
#define WARD_HPP
#include <vector>

enum STATE {
  NONE,
  NORMAL,
  LIGHT,
  MEDIUM,
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
  void printInfo();
  void setStateWithDensity(double density);
  void firstTransitionRule(double density,
                           const std::vector<double> &neighbourAreas,
                           const std::vector<int> &neighbourEnemies,
                           double mortalityRate,
                           const std::vector<STATE> &neighbourStates);

  void secondTransitionRule(double density,
                            const std::vector<double> &neighbourAreas,
                            const std::vector<int> &neighbourEnemies,
                            double mortalityRate,
                            const std::vector<STATE> &neighbourStates);

  void thirdTransitionRule(double density,
                           const std::vector<double> &neighbourAreas,
                           const std::vector<int> &neighbourEnemies,
                           double mortalityRate,
                           const std::vector<STATE> &neighbourStates);
  int getPopulationPerSquareMeter();
  void setPopulationPerSquareMeter(int populationPerSquareMeter);
  double getArea();
  int getEnemiesPerSquareMeter();
  double getMortalityRate();
  void setMoralityRate(double mortalityRate);

private:
  double area;
  int enemiesPerSquareMeter;
  double mortalityRate;
  int populationPerSquareMeter;
  STATE state;
};

#endif
