#ifndef PARSE_HPP
#define PARSE_HPP

#include "ward.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Parser {
public:
  static std::vector<Ward> parseRowsFromFile(std::istream &stream);
};

#endif
