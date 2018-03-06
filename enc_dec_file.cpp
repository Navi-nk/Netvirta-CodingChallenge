#include "enc_dec_file.hpp"

std::string EncDecHelper::encryptDecrypt(std::string inputStr)
{
    char key[] = {'N', 'E', 'T', 'V', 'I', 'R', 'T', 'A'};
    std::string outputStr = inputStr;

    for (int i = 0; i < inputStr.size(); i++)
        outputStr[i] = inputStr[i] ^ key[i % (sizeof(key) / sizeof(char))]; //xor encryption/decryption

    return outputStr;
}

bool EncDecHelper::encryptFile(std::string filePath, std::string fileName)
{
    std::string line;
    std::ifstream inFile(filePath+"/"+ fileName);
    std::ofstream outFile (filePath+"/enc-"+fileName);

    if (inFile.is_open() && outFile.is_open())
    {
        while (std::getline(inFile, line))
        {
            outFile<< encryptDecrypt(line)<<"\n";
        }
        inFile.close();
        outFile.close();
    }
    else
        return false;
        
    return true;
}

int main(int argc, const char *argv[])
{
    EncDecHelper encDecHelper;
    
    std::string filePath,fileName;

    std::cout<<"Please provide the filename to open"<<std::endl;
    std::cin>>fileName;
    std::cout<<"Please provide the path where "<<fileName<<" exists"<<std::endl;
    std::cin>>filePath;

    if(encDecHelper.encryptFile(filePath, fileName))
    {
        std::cout<<"The input file "<<filePath+"/"+fileName<<" has been encrypted"<<std::endl;
        std::cout<<"The Encrypted file is "<<filePath+"/enc-"+fileName<<std::endl;
    }
    else
    {
        std::cout<<"Provided file does not exists"<<std::endl;
    }
    return 0;
}