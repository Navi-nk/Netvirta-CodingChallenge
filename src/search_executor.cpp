#include "search_executor.hpp"
#include "ordered_search.hpp"
#include "unordered_search.hpp"
#include "closest_search.hpp"
#include <iostream>

bool SearchExecutor::preprocess(std::vector<std::string> strVec)
{
    long pos = 0;
    try
    {
        for (std::vector<std::string>::iterator it = strVec.begin(); it != strVec.end(); it++)
        {
            std::vector<long> innerVec;
            std::string line = std::regex_replace(*it, std::regex("^ +| +$|( ) +"), ""); //remove all whitespaces

            while ((pos = line.find(',')) != std::string::npos) //iterate through string using "," as delimiter
            {
                long val = std::stol(line.substr(0, pos), nullptr); //convert string to long
                innerVec.push_back(val);
                line.erase(0, pos + 1);
            }
            if (pos == std::string::npos)
                innerVec.push_back(std::stol(line.substr(0, line.length()), nullptr));

            if (innerVec.size() > 0)
                matrixData.matrix.push_back(innerVec);

            std::cout << *it << " " << std::endl;
        }
    }
    catch (...)
    {
        return false;
    }

    preprocessMatrix();

    return true;
}

void SearchExecutor::preprocessMatrix()
{
    for (long i = 0; i < matrixData.matrix.size(); i++)
    {
        for (long j = 0; j < matrixData.matrix[i].size(); j++)
        {
            if (matrixData.matrixMap.find(matrixData.matrix[i][j]) == matrixData.matrixMap.end())
            {
                std::unordered_map<long, std::vector<long>> innerMap = {{i, {j}}};
                matrixData.matrixMap.insert({matrixData.matrix[i][j], innerMap});
            }
            else
            {
                (matrixData.matrixMap[matrixData.matrix[i][j]])[i].push_back(j);
            }
        }
    }
}

bool SearchExecutor::setSearchStrategy(std::string cmd)
{
    resetStrategy();

    if (cmd.compare("searchOrdered") == 0)
        searchStrategy = new OrderedSearch(matrixData);
    else if (cmd.compare("searchUnordered") == 0)
        searchStrategy = new UnorderedSearch(matrixData);
    else if (cmd.compare("searchUnordered") == 0)
        searchStrategy = new ClosestSearch(matrixData);
    else
        return false;

    return true;
}

lvec SearchExecutor::performSearch(lvec inputArr)
{
    return searchStrategy->executeSearch(inputArr);
}

void SearchExecutor::resetStrategy()
{
    if (searchStrategy != nullptr)
    {
        delete searchStrategy;
        searchStrategy = NULL;
    }
}
