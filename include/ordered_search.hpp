#ifndef ORD_SEARCH
#define ORD_SEARCH
#include "search_strategy.hpp"

class OrderedSearch : public SearchStrategy
{
  public:
    OrderedSearch(MatrixData &matrixData) : SearchStrategy(matrixData) {}

    lvec executeSearch(lvec inputArr) override;
};

#endif