#include "enc_dec_file.hpp"
#include "search_executor.hpp"

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
    
    if(strVec.size() == 0)
    {
        std::cout<<file<<" File does not exists"<< std::endl;
        return 0;
    }    

    if(!searchExecutor.preprocess(strVec))
    {
        std::cout<<file<<" File contains invalid data"<< std::endl;
        return 0;
    }
    
    std::cout<<"\n\nAvailable Search Commands"<<std::endl;
    
    return 0;
}