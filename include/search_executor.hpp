#ifndef SEARCH_EXE_H
#define SEARCH_EXE_H
#include "search_strategy.hpp"
#include <regex>
#include <iostream>

class SearchExecutor
{
private:
  MatrixData matrixData;
  SearchStrategy *searchStrategy = NULL;

  void preprocessMatrix();
  void resetStrategy();

public:
  bool preprocess(std::vector<std::string>);
  bool setSearchStrategy(std::string);
  lvec performSearch(lvec);

  ~SearchExecutor()
  {
    std::cout << "delete called" << std::endl;
    if (searchStrategy != nullptr)
      delete searchStrategy;
  }
};

#endif