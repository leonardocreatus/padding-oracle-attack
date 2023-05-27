#include "Converter.hpp"

int Converter::byteStringToInt(std::string input)
{
    std::stringstream ss;
    ss << std::hex << input;
    int byte;
    ss >> byte;
    return byte;
}

std::vector<std::string> Converter::splitStringToBlocks(std::string input, int block_size)
{
    std::vector<std::string> blocks;
    for (int i = 0; i < input.length(); i += block_size)
    {
        blocks.push_back(input.substr(i, block_size));
    }
    return blocks;
}

std::vector<int> Converter::hexStringToBytes(std::string input)
{
    std::vector<int> bytes;
    for (int i = 0; i < input.length(); i += 2)
    {
        int byte = Converter::byteStringToInt(input.substr(i, 2));
        bytes.push_back(byte);
    }
    return bytes;
}