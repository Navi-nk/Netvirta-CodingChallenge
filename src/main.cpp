#include "enc_dec_file.hpp"
#include "search_executor.hpp"

//function to print the vector
void printResult(std::vector<long> res)
{
    for (std::vector<long>::iterator it = res.begin(); it != res.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        std::cout << "Format: <Executable> <Encrypted matrix csv file>" << std::endl;
        return 0;
    }

    std::string file = argv[1];
    EncDecHelper encDecHelper;
    SearchExecutor searchExecutor;

    std::vector<std::string> strVec = encDecHelper.decryptFile(file); //decrypt the input file

    if (strVec.size() == 0)
    {
        std::cout << file << " File does not exists" << std::endl;
        return 0;
    }

    //preprocess the input matrix
    if (!searchExecutor.preprocess(strVec))
    {
        std::cout << file << " File contains invalid data" << std::endl;
        return 0;
    }

    std::cout << "\nAvailable Search Commands" << std::endl;
    std::cout << "1. searchOrdered <sequence of integers>" << std::endl;
    std::cout << "2. searchUnordered <sequence of integers>" << std::endl;
    std::cout << "3. searchClosest <sequence of integers>\n"
              << std::endl;
    std::cout << "use \"exit\" command to exit program\n"
              << std::endl;

    //continously take input from console
    std::string line;
    while (std::getline(std::cin, line))
    {
        //trim any extra spaces
        line = std::regex_replace(line, std::regex("( ) +"), " ");
        line = std::regex_replace(line, std::regex("^ +| +$"), "");

        //std::cout << "Line Received: " << line << '\n';

        //exit condition
        if (line.compare("exit") == 0)
        {
            std::cout << "Bye Bye" << std::endl;
            break;
        }

        int pos = 0;
        lvec inputArr;

        char *lineCh = strdup(line.c_str());
        char *token = strtok(lineCh, " ");


        //check if the command given is valid
        if (token != nullptr && searchExecutor.setSearchStrategy(std::string(token)))
        {
            token = strtok(NULL, " ");

            if(token == nullptr)
            {
                std::cout << "No input given. try again" << std::endl;
                free(lineCh);
                continue;
            }

            //validate if the sequence argument is valid
            long nonAllowedPos = std::string(token).find_first_not_of("0123456789 -");
            if (nonAllowedPos != std::string::npos)
            {
                std::cout << "invalid input. try again" << std::endl;
                free(lineCh);
                continue;
            }

            try
            {
                //read each number in the sequence
                while (token != NULL)
                {
                    long val = std::stol(token, nullptr); //convert to to long
                    inputArr.push_back(val);
                    token = strtok(NULL, " ");
                }

                lvec res = searchExecutor.performSearch(inputArr);  // perform search and return matching indices 

                printResult(res);
            }
            catch (...)
            {
                std::cout << "invalid input. try again" << std::endl;
            }
            free(lineCh);
        }
        else
        {
            std::cout << "command not recognized" << std::endl;
        }
    }
    return 0;
}