#ifndef ClOSEST_SEARCH
#define ClOSEST_SEARCH
#include "search_strategy.hpp"

class ClosestSearch : public SearchStrategy
{
  public:
    ClosestSearch(MatrixData &matrixData) : SearchStrategy(matrixData) {}

    lvec executeSearch(lvec inputArr) override;
};

#endif