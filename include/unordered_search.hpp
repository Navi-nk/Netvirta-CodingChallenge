#ifndef UNORD_SEARCH
#define UNORD_SEARCH
#include "search_strategy.hpp"

class UnorderedSearch : public SearchStrategy
{
  public:
    UnorderedSearch(MatrixData &matrixData) : SearchStrategy(matrixData) {}
    
    lvec executeSearch(lvec inputArr) override;

};

#endif