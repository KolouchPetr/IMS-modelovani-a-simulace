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
  /**
   * @brief parse the rows from the given stream
   *
   * @param stream The stream from which the rows will be parsed
   * @return std::vector<Ward> The parsed rows as a vector of wards
   */
  static std::vector<Ward> parseRowsFromFile(std::istream &stream);
};

#endif
