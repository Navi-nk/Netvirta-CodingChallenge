#include "closest_search.hpp"

lvec ClosestSearch::executeSearch(lvec inputArr)
{
    if(inputArr.size() == 0) //check for empty input
        return {-1};

    matrixmap matrixMap = matrixData.matrixMap;

    //if (inputArr.size() > matrixData.matrix[0].size())
        //return {-1};
        
    std::unordered_map<long, long> searchMap;

    //The logic here is:
    //1. We will traverse the input array and for each integer identify the rows of the matrix where it appears.
    //2. For each of these rows, identify the number of position in which this number appears.
    //3. Accumulate this count and associate with the given row index in a map. Make sure the position once counted isn't counted again.
    //4. At the end, for each row index in the map check which of these rows has the maximum count value. The row which max count is the required result.
    //   if more than one row has same max count then they are stored in result.
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
            //return {-1}; //dont stop search
        }
    }

    long max = 0;
    lvec position;
    for (std::unordered_map<long, long>::iterator it = searchMap.begin(); it != searchMap.end(); it++)
    {
        if (it->second > max)
        {
            max = it->second;
            std::vector<long> newPosition = {it->first};
            position.swap(newPosition);
        }
        else if (it->second == max && max != 0)
        {
            position.push_back(it->first);
        }
    }

    if (position.size() == 0)
        position.push_back(-1);

    return position;
}