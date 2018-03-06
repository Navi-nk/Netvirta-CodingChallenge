#ifndef ENC_DEC_H
#define ENC_DEC_H
#include <iostream>
#include <fstream>
#include <string>

class EncDecHelper{
public:
    std::string encryptDecrypt(std::string);
    bool encryptFile(std::string, std::string);
};

#endif