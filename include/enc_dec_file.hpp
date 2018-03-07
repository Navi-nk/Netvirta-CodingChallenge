#ifndef ENC_DEC_H
#define ENC_DEC_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class EncDecHelper{
public:
    std::string encryptDecrypt(std::string);
    bool encryptFile(std::string, std::string);
    std::vector<std::string> decryptFile(std::string);
};

#endif