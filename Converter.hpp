#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <string>
#include <sstream>
#include <vector>

class Converter
{
public:
    static int byteStringToInt(std::string input);
    static std::vector<std::string> splitStringToBlocks(std::string input, int block_size);
    static std::vector<int> hexStringToBytes(std::string input);
};

#endif