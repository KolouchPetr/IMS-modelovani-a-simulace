#ifndef WARD_HPP
#define WARD_HPP
#include <string>
#include <vector>

/**
 * @brief The STATE enum
 * @details The STATE enum is used to represent the state of a ward.
 */
enum STATE {
  NONE,
  NORMAL,
  LIGHT,
  MEDIUM,
  HIGH,
  VERY_HIGH,
};

// The thresholds for the states to change from one state to another
const int thresholds[] = {0, 500, 1499, 2999, 9999};

class Ward {
public:
  Ward();
  /**
   * @brief Construct a new Ward object
   *
   * @param id The id of the ward
   * @param name The name of the ward
   * @param area The area of the ward
   * @param enemiesPerSquareMeter The enemies per square meter of the ward
   * @param mortalityRate The mortality rate of the ward
   * @param populationPerSquareMeter The population per square meter of the ward
   * @param neighbourIDs The ids of the neighbors of the ward
   */
  Ward(int id, std::string name, double area, int enemiesPerSquareMeter,
       double mortalityRate, int populationPerSquareMeter,
       std::vector<int> neighbourIDs);
  /**
   * @brief Destroy the Ward object
   *
   */
  ~Ward();
  /**
   * @brief set the state of the ward
   *
   * @param state The state of the ward
   */
  void setState(STATE state);
  /**
   * @brief get the state of the ward
   *
   * @return STATE The state of the ward
   */
  STATE getState();
  /**
   * @brief print the information of the ward
   *
   */
  void printInfo();
  /**
   * @brief set the state of the ward based on the given density
   *
   * @param density The density that will be used to set the state of the ward
   */
  void setStateWithDensity(double density);
  /**
   * @brief apply the first transition rule
   *
   * @param density The density of the ward
   * @param neighbourAreas The areas of the neighbors of the ward
   * @param neighbourEnemies The enemies per square meter of the neighbors of
   * the ward
   */
  void firstTransitionRule(double density,
                           const std::vector<double> &neighbourAreas,
                           const std::vector<int> &neighbourEnemies);

  /**
   * @brief apply the second transition rule
   *
   * @param density The density of the ward
   */
  void secondTransitionRule(double density);

  /**
   * @brief apply the third transition rule
   *
   * @param neighbourStates The states of the neighbors of the ward
   */
  void thirdTransitionRule(const std::vector<STATE> &neighbourStates);
  /**
   * @brief get the population per square meter of the ward
   *
   * @return int The population per square meter of the ward
   */
  int getPopulationPerSquareMeter();
  /**
   * @brief set the population per square meter of the ward
   *
   * @param populationPerSquareMeter The population per square meter of the ward
   */
  void setPopulationPerSquareMeter(int populationPerSquareMeter);
  /**
   * @brief get the area of the ward
   *
   * @return double The area of the ward
   */
  double getArea();
  /**
   * @brief get the enemies per square meter of the ward
   *
   * @return int The enemies per square meter of the ward
   */
  int getEnemiesPerSquareMeter();
  /**
   * @brief get the mortality rate of the ward
   *
   * @return double The mortality rate of the ward
   */
  double getMortalityRate();
  /**
   * @brief set the mortality rate of the ward
   *
   * @param mortalityRate The mortality rate of the ward
   */
  void setMoralityRate(double mortalityRate);
  /**
   * @brief get the id of the ward
   *
   * @return int The id of the ward
   */
  int getID() { return this->id; }
  /**
   * @brief get the ids of the neighbors of the ward
   *
   * @return std::vector<int> The ids of the neighbors of the ward
   */
  std::vector<int> getNeighbourIDs() { return this->neighbourIDs; }
  /**
   * @brief get the name of the ward
   *
   * @return std::string The name of the ward
   */
  std::string getName() { return this->name; }

private:
  int id;
  std::string name;
  double area;
  int enemiesPerSquareMeter;
  double mortalityRate;
  int populationPerSquareMeter;
  std::vector<int> neighbourIDs;
  STATE state;
};

#endif
