#include <iostream>
#include <vector>
#include <unordered_map>
#include <gtest/gtest.h>

std::vector<long> search(std::vector<long> inputArr)
{
    //for (std::vector<long>::iterator it = inputArr.begin(); it != inputArr.end(); it++)
    //{
    //std::cout << *it << " " << std::endl;
    long i = 0;
    while (i<inputArr.size())
    {
        if (matrixMap.find(inputArr[i]) == matrixMap.end())
            return {-1};
        
    }
    //}

    return {0};
}

std::vector<std::vector<long>> matrix = {
    {1, 2, 4, 5, 7, 10, 30},
    {6, 10, 5, 25, 1, 25, 90},
    {10, 5, 25, 6, 7, 8, 30}};

std::unordered_map<std::string, std::vector<long> (*)(std::vector<long>)> funcMap = {
    {"search", &search},
};

std::unordered_map<long, std::unordered_map<long, std::vector<long>>> matrixMap;

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

    // printMap();

    std::string line;
    while (std::getline(std::cin, line)) // read from std::cin
    {
        if (line.compare("exit") == 0)
        {
            std::cout << "Bye Bye" << std::endl;
            break;
        }

        std::cout << "Line Received: " << line << '\n';
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

                funcMap[cmd](inputArr);
            }
            catch (...)
            {
                std::cout << "invalid input. try again" << std::endl;
            }
        }
    }

    return 0;
}