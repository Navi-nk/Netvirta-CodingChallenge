#include "enc_dec_file.hpp"
#include "search_executor.hpp"

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

    std::vector<std::string> strVec = encDecHelper.decryptFile(file);

    if (strVec.size() == 0)
    {
        std::cout << file << " File does not exists" << std::endl;
        return 0;
    }

    if (!searchExecutor.preprocess(strVec))
    {
        std::cout << file << " File contains invalid data" << std::endl;
        return 0;
    }

    std::cout << "\n\nAvailable Search Commands" << std::endl;
    std::cout << "1. searchOrdered <sequence of integers>" << std::endl;
    std::cout << "2. searchUnordered <sequence of integers>" << std::endl;
    std::cout << "3. searchClosest <sequence of integers>\n"
              << std::endl;
    std::cout << "use \"exit\" command to exit program\n"
              << std::endl;

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
        //std::string cmd;
        lvec inputArr;

        char *lineCh = strdup(line.c_str());
        char *token = strtok(lineCh, " ");

        if (searchExecutor.setSearchStrategy(std::string(token)))
        {
            token = strtok(NULL, " ");
            long nonAllowedPos = std::string(token).find_first_not_of("0123456789 ");

            if (nonAllowedPos != std::string::npos)
            {
                std::cout << "invalid input. try again" << std::endl;
                continue;
            }
            try
            {
                while (token != NULL)
                {
                    long val = std::stol(token, nullptr);
                    inputArr.push_back(val);
                    token = strtok(NULL, " ");
                }
                lvec res = searchExecutor.performSearch(inputArr);

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