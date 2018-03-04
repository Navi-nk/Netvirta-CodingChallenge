#include <iostream>
#include <vector>
#include <unordered_map>
#include <gtest/gtest.h>
#include <string>
#include <regex>

std::vector<std::vector<long>> matrix = {
    {1, 2, 4, 5, 7, 10, 30},
    {6, 10, 5, 25, 1, 25, 90},
    {10, 5, 25, 6, 7, 8, 30}};

std::unordered_map<long, std::unordered_map<long, std::vector<long>>> matrixMap;

std::vector<long> searchOrdered(std::vector<long> inputArr)
{
    if (matrixMap.find(inputArr[0]) == matrixMap.end() || inputArr.size() > matrix[0].size())
        return {-1};

    std::vector<long> res;
    long i = 0;

    std::unordered_map<long, std::vector<long>> innerMap = matrixMap[inputArr[0]];
    for (std::unordered_map<long, std::vector<long>>::iterator it = innerMap.begin(); it != innerMap.end(); it++)
    {
        std::vector<long> innerVec = it->second;
        for (std::vector<long>::iterator it1 = innerVec.begin(); it1 != innerVec.end(); it1++)
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

std::vector<long> searchUnordered(std::vector<long> inputArr)
{
    if (inputArr.size() > matrix[0].size())
        return {-1};
    std::unordered_map<long, long> searchMap;
    std::vector<long> res;

    for (long i = 0; i < inputArr.size(); i++)
    {
        //if (matrixMap.find(inputArr[i]) == matrixMap.end())
        //return {-1};
        try
        {
            std::unordered_map<long, std::vector<long>> innerMap = matrixMap.at(inputArr[i]);
            for (std::unordered_map<long, std::vector<long>>::iterator it = innerMap.begin(); it != innerMap.end(); it++)
            {
                searchMap[it->first]++;
            }
        }
        catch (...)
        {
            return {-1};
        }
    }

    for (std::unordered_map<long, long>::iterator it = searchMap.begin(); it != searchMap.end(); it++)
    {
        ///std::cout<<it->first<<" "<<it->second<<std::endl;
        if (it->second == inputArr.size())
        {
            res.push_back(it->first);
        }
    }

    if (res.size() == 0)
        res.push_back(-1);

    return res;
}

std::vector<long> searchClosest(std::vector<long> inputArr)
{
    if (inputArr.size() > matrix[0].size())
        return {-1};
    std::unordered_map<long, long> searchMap;

    for (long i = 0; i < inputArr.size(); i++)
    {
        try
        {
            std::unordered_map<long, std::vector<long>> innerMap = matrixMap.at(inputArr[i]);
            for (std::unordered_map<long, std::vector<long>>::iterator it = innerMap.begin(); it != innerMap.end(); it++)
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
    std::vector<long> position;
    for (std::unordered_map<long, long>::iterator it = searchMap.begin(); it != searchMap.end(); it++)
    {
        ///std::cout<<it->first<<" "<<it->second<<std::endl;
        if (it->second > max)
        {
            max = it->second;
            std::vector<long> newPosition = {it->first};
            position.swap(newPosition);
        }
        else if(it->second == max && max != 0)
        {
            position.push_back(it->first);
        }
    }

    if (position.size() == 0)
        position.push_back(-1);

    return position;
}

void preprocessMatrix()
{
    //for(std::vector<vector<long>>::iterator it_r=matrix.begin(); it_r!= matrix.end();it_r++){
    //for(std::vector<long>::iterator it_c= it_r->begin(); it_c != it_r->end(); it_c++){
    for (long i = 0; i < matrix.size(); i++)
    {
        for (long j = 0; j < matrix[i].size(); j++)
        {
            //cout<<(*it_c)<<" ";
            //std::cout<< matrix[i][j]<<std::endl;
            if (matrixMap.find(matrix[i][j]) == matrixMap.end())
            {
                std::unordered_map<long, std::vector<long>> innerMap = {{i, {j}}};
                matrixMap.insert({matrix[i][j], innerMap});
            }
            else
            {
                //innerMap = matrixMap[matrix[i][j]];
                //if(innerMap.find(i) == innerMap.end())
                //{
                //innerMap.insert({i,{j}});
                //}
                //else
                //{
                (matrixMap[matrix[i][j]])[i].push_back(j);
                //}
            }
        }
        //cout<<endl;
    }
}

void printMap()
{
    for (std::unordered_map<long, std::unordered_map<long, std::vector<long>>>::iterator it = matrixMap.begin(); it != matrixMap.end(); it++)
    {
        std::cout << it->first << "->";
        for (std::unordered_map<long, std::vector<long>>::iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
        {
            std::cout << it1->first << "->";
            for (std::vector<long>::iterator it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
            {
                std::cout << *it2 << ",";
            }
        }
        std::cout << std::endl;
    }
}

void printResult(std::vector<long> res)
{
    for (std::vector<long>::iterator it = res.begin(); it != res.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

std::unordered_map<std::string, std::vector<long> (*)(std::vector<long>)> funcMap = {
    {"searchOrdered", &searchOrdered},
    {"searchUnordered", &searchUnordered},
    {"searchClosest", &searchClosest},
};

int main(int argc, char **argv)
{
    /*cout << "You have entered " << argc
         << " arguments:" << "\n";
    std::string args[argc];
    for (int i = 0; i < argc; ++i){
         args[i] = argv[i] ;
        cout<<args[i]<<' ';
        
    }*/

    preprocessMatrix();

    printMap();
    //std::cout<<matrix[0].size()<<std::endl;
    std::string line;
    while (std::getline(std::cin, line))
    {
        line = std::regex_replace(line, std::regex("( ) +"), " ");
        line = std::regex_replace(line, std::regex("^ +| +$"), "");

        std::cout << "Line Received: " << line << '\n';

        if (line.compare("exit") == 0)
        {
            std::cout << "Bye Bye" << std::endl;
            break;
        }

        int pos = 0;
        std::string cmd;
        std::vector<long> inputArr;
        if ((pos = line.find(' ')) != std::string::npos)
        {
            cmd = line.substr(0, pos);
            line.erase(0, pos + 1);
        }

        if (funcMap.find(cmd) != funcMap.end())
        {
            try
            {
                while ((pos = line.find(' ')) != std::string::npos)
                {
                    long val = std::stol(line.substr(0, pos), nullptr);
                    inputArr.push_back(val);
                    line.erase(0, pos + 1);
                }
                if (pos == std::string::npos)
                    inputArr.push_back(std::stol(line.substr(0, line.length()), nullptr));

                std::vector<long> res = funcMap[cmd](inputArr);

                printResult(res);
            }
            catch (...)
            {
                std::cout << "invalid input. try again" << std::endl;
            }
        }
        else
        {
            std::cout << "command not recognized" << std::endl;
        }
    }

    return 0;
}