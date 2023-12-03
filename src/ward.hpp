#ifndef WARD_HPP
#define WARD_HPP

enum STATE {
  NONE,
  NORMAL,
  LIGHT,
  MEDUIM,
  HIGH,
  VERY_HIGH,
};

class Ward {
public:
  Ward(STATE state, double area, int enemiesPerSquareMeter,
       double mortalityRate, int populationPerSquareMeter);
  ~Ward();
  void setState(STATE state);
  STATE getState();

private:
  double area;
  int enemiesPerSquareMeter;
  double mortalityRate;
  int populationPerSquareMeter;
  STATE state;
};

#endif
