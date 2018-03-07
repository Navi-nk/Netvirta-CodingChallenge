#include "closest_search.hpp"

lvec ClosestSearch::executeSearch(lvec inputArr)
{
    if (inputArr.size() > matrixData.matrix[0].size())
        return {-1};
    std::unordered_map<long, long> searchMap;

    for (long i = 0; i < inputArr.size(); i++)
    {
        try
        {
            mapoflvec innerMap = matrixData.matrixMap.at(inputArr[i]);
            for (mapoflvec::iterator it = innerMap.begin(); it != innerMap.end(); it++)
            {
                searchMap[it->first]++;
            }
        }
        catch (...)
        {
            //return {-1};
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