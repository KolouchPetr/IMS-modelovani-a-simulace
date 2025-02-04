#include "parser.hpp"
#include <random>

std::vector<Ward> Parser::parseRowsFromFile(std::istream &stream) {
  std::vector<Ward> wards;
  std::string line;
  bool firstLine = true;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrEnemies(0, 10);
  std::uniform_real_distribution<> distrMortality(0.14, 0.22);

  while (std::getline(stream, line)) {

    if (firstLine) {
      firstLine = false;
      continue;
    }

    std::istringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, ',')) {
      tokens.push_back(token);
    }
    int id = std::stoi(tokens[0]);
    std::string name = tokens[1];
    double area = std::stod(tokens[2]);
    area /= 1000000;

    // TODO keep 0 or generate random number?
    int enemiesPerSquareMeter = std::stoi(tokens[3]);
    double mortalityRate = distrMortality(gen);
    int populationPerSquareMeter = std::stoi(tokens[5]);

    std::vector<int> neighbourIDs;
    for (size_t i = 6; i < tokens.size(); i++) {
      if (!tokens.empty()) {
        neighbourIDs.push_back(std::stoi(tokens[i]));
      }
    }
    Ward ward(id, name, area, enemiesPerSquareMeter, mortalityRate,
              populationPerSquareMeter, neighbourIDs);
    wards.push_back(ward);
  }
  return wards;
}
