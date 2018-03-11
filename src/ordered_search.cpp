#include "ordered_search.hpp"
#include <iostream>

lvec OrderedSearch::executeSearch(lvec inputArr)
{
    if(inputArr.size() == 0)  //check for empty input
        return {-1};

    const matrixmap & matrixMap = matrixData.matrixMap;
    const matrixtype & matrix = matrixData.matrix;

    //check if first element is present in the matrix and is the size of input array is greater than row length
    if (matrixMap.find(inputArr[0]) == matrixMap.end() || inputArr.size() > matrix[0].size())
        return {-1};

    lvec res;
    long i = 0;

    //The logic here is: 
    //1. We will first identify the rows where the first element of input array is present.
    //2. Then identify the position in a given row where this element appears
    //3. Traverse the matrix from this position till position + length of input array and during each step,
    //   check if the element in matrix is same as that in input array
    //4. If the number of matches is same input array length then the row index is stored and the process is repeated to find all such rows
    mapoflvec innerMap = matrixMap.at(inputArr[0]);
    for (mapoflvec::iterator it = innerMap.begin(); it != innerMap.end(); it++)
    {
        lvec innerVec = it->second;
        for (lvec::iterator it1 = innerVec.begin(); it1 != innerVec.end(); it1++)
        {
            long j = 1, pos = *it1;
            long rowSize = matrix[it->first].size();

            while (j < inputArr.size() && ((pos + j) < rowSize))
            {
                if (matrix[it->first][pos + j] == inputArr[j])
                {
                    j++;
                    continue;
                }
                break;
            }
            if (j == inputArr.size())
            {
                res.push_back(it->first);
                break;
            }
        }
    }
    if (res.size() == 0)
        res.push_back(-1);
    return res;
}