#include "unordered_search.hpp"

lvec UnorderedSearch::executeSearch(lvec inputArr)
{
    if (inputArr.size() == 0) //check for empty input
        return {-1};

    //const matrixmap &matrixMap = matrixData.matrixMap;
    matrixmap matrixMap = matrixData.matrixMap;

    //check if the size of input array is greater than row length
    if (inputArr.size() > matrixData.matrix[0].size())
        return {-1};

    std::unordered_map<long, long> searchMap;
    std::vector<long> res;

    //The logic here is:
    //1. We will traverse the input array and for each integer identify the rows of the matrix where it appears.
    //2. For each of these rows, identify the number of position in which this number appears.
    //3. Accumulate this count and associate with the given row index in a map. Make sure the position once counted isn't counted again.
    //4. At the end, for each row index in the map check if the count matched the length of the input array. The matched row indices the required result  
    for (long i = 0; i < inputArr.size(); i++)
    {
        try
        {
            mapoflvec &innerMap = matrixMap.at(inputArr[i]);
            for (mapoflvec::iterator it = innerMap.begin(); it != innerMap.end(); it++)
            {
                if (it->second.size() > 0)
                {
                    searchMap[it->first]++;
                    (it->second).pop_back();
                }
            }
        }
        catch (...)
        {
            return {-1};
        }
    }

    for (std::unordered_map<long, long>::iterator it = searchMap.begin(); it != searchMap.end(); it++)
    {
        if (it->second == inputArr.size())
        {
            res.push_back(it->first);
        }
    }

    if (res.size() == 0)
        res.push_back(-1);

    return res;
}