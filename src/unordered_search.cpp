#include "unordered_search.hpp"

lvec UnorderedSearch::executeSearch(lvec inputArr)
{
    const matrixmap &matrixMap = matrixData.matrixMap;

    if (inputArr.size() > matrixData.matrix[0].size())
        return {-1};

    std::unordered_map<long, long> searchMap;
    std::unordered_map<long, bool> checkedMap;
    std::vector<long> res;

    for (long i = 0; i < inputArr.size(); i++)
    {
        try
        {
            
            if (!checkedMap[inputArr[i]])
            {
                checkedMap[inputArr[i]] = true;
                mapoflvec innerMap = matrixMap.at(inputArr[i]);
                for (mapoflvec::iterator it = innerMap.begin(); it != innerMap.end(); it++)
                {
                    searchMap[it->first] += it->second.size();
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