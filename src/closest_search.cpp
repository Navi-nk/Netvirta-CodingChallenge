#include "closest_search.hpp"

lvec ClosestSearch::executeSearch(lvec inputArr)
{
    if(inputArr.size() == 0)
        return {-1};

    matrixmap matrixMap = matrixData.matrixMap;

    //if (inputArr.size() > matrixData.matrix[0].size())
        //return {-1};
        
    std::unordered_map<long, long> searchMap;

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