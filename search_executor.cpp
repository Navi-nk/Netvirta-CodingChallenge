#include "search_executor.hpp"
#include <iostream>
#include <regex>

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
                matrix.push_back(innerVec);

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
    for (long i = 0; i < matrix.size(); i++)
    {
        for (long j = 0; j < matrix[i].size(); j++)
        {
            if (matrixMap.find(matrix[i][j]) == matrixMap.end())
            {
                std::unordered_map<long, std::vector<long>> innerMap = {{i, {j}}};
                matrixMap.insert({matrix[i][j], innerMap});
            }
            else
            {
                (matrixMap[matrix[i][j]])[i].push_back(j);
            }
        }
    }
}
