#ifndef SEARCH_H
#define SEARCH_H
#include "matrix_struct.hpp"

class SearchStrategy
{
  protected:
    const MatrixData& matrixData;

  public:
    SearchStrategy(MatrixData& matrixData) :
            matrixData{matrixData} {}

    virtual lvec executeSearch(lvec inputArr) = 0;
    virtual ~SearchStrategy(){};
};
#endif