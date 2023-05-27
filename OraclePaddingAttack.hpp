#ifndef ORACLEPADDINGATTACK_HPP
#define ORACLEPADDINGATTACK_HPP

#include <string>
#include <vector>
#include <iomanip>
#include "Converter.hpp"
#include "CURLplusplus.hpp"

class OraclePaddingAttack
{
public:
    static std::string attack(std::string iv, std::string ciphertext, bool isLastBlock);
};

#endif