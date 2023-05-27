
#include "Converter.hpp"
#include "OraclePaddingAttack.hpp"
#include <iostream>

int main(int argc, char **argv)
{

    std::string ciphertext = "f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeb4";
    std::vector<std::string> blocks = Converter::splitStringToBlocks(ciphertext, 32);

    std::stringstream ss;
    for (int i = 0; i < blocks.size() - 1; i++)
    {
        // int i = 2;
        std::string iv = blocks[i];
        std::string ciphertext_block = blocks[i + 1];

        std::string plaintext = OraclePaddingAttack::attack(iv, ciphertext_block, i == blocks.size() - 2);
        ss << plaintext;
    }

    std::cout << "Decipher: " << ss.str() << std::endl;

    return 0;
}