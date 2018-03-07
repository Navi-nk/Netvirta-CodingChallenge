#include "ordered_search.hpp"

lvec OrderedSearch::executeSearch(lvec inputArr)
{
    const matrixmap & matrixMap = matrixData.matrixMap;
    const matrixtype & matrix = matrixData.matrix;

    if (matrixMap.find(inputArr[0]) == matrixMap.end() || inputArr.size() > matrix[0].size())
        return {-1};

    lvec res;
    long i = 0;

    mapoflvec innerMap = matrixMap.at(inputArr[0]);
    for (mapoflvec::iterator it = innerMap.begin(); it != innerMap.end(); it++)
    {
        lvec innerVec = it->second;
        for (lvec::iterator it1 = innerVec.begin(); it1 != innerVec.end(); it1++)
        {
            long j = 1, pos = *it1;
            while (j < inputArr.size())
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