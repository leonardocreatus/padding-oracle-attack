#include "CURLplusplus.hpp"
#include <iostream>
#include <vector>
#include <iomanip>

int byteStringToInt(std::string byteString)
{
    std::stringstream ss;
    ss << std::hex << byteString;
    int byte;
    ss >> byte;
    return byte;
}

int main(int argc, char **argv)
{
    std::string ciphertext = "f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeb4";
    std::vector<std::string> blocks;
    std::array<std::array<char, 16>, 3> plaintext;

    for (int i = 0; i < ciphertext.length(); i += 32)
    {
        blocks.push_back(ciphertext.substr(i, 32));
    }

    for (int i = 0; i < blocks.size(); i++)
    {
        std::cout << "Block " << i << ": " << blocks[i] << std::endl;
    }

    for (int it_block = 0; it_block < blocks.size() - 1; it_block++)
    {
        std::string block = blocks[it_block];
        std::vector<int> cipher_bytes;
        std::vector<int> cipher_bytes_copy;
        for (int i = 0; i < block.length(); i += 2)
        {
            int byte = byteStringToInt(block.substr(i, 2));
            cipher_bytes.push_back(byteStringToInt(block.substr(i, 2)));
            cipher_bytes_copy.push_back(byteStringToInt(block.substr(i, 2)));
        }

        for (int padding = 1; padding <= 16; padding++)
        {
            std::cout << "Padding: " << std::dec << padding << std::endl;
            // for (int character = ; character < 256; character++)
            for (int character = 0x20; character < 0x7A; character++)
            {
                plaintext[it_block][16 - padding] = character;

                for (int i = 15; i >= 16 - padding; i--)
                {
                    cipher_bytes[i] = cipher_bytes_copy[i] ^ padding ^ plaintext[it_block][i];
                }

                std::stringstream iv;
                for (int i = 0; i < cipher_bytes.size(); i++)
                {
                    iv << std::hex << std::setw(2) << std::setfill('0') << cipher_bytes[i];
                }
                std::cout << "IV: " << iv.str() << std::endl;

                CURLplusplus curl;
                std::stringstream url;
                url << "http://crypto-class.appspot.com/po?er=" << iv.str() << blocks[it_block + 1];
                curl.Get(url.str());
                int http_code = curl.GetHttpCode();
                if (http_code == 404)
                {
                    std::cout << "Byte: " << std::hex << character << std::endl;
                    std::cout << "IV: " << iv.str() << std::endl;
                    cipher_bytes[16 - padding] = cipher_bytes_copy[16 - padding];
                    break;
                }
                else if (http_code != 403)
                {
                    std::cout << "HTTP Code unknown: " << std::dec << http_code << std::endl;
                    break;
                }
            }
        }

        std::stringstream ss;
        for (int i = 0; i < 16; i++)
        {
            ss << plaintext[it_block][i];
        }
        std::cout << ss.str() << std::endl;
        break;
    }

    // std::stringstream result;
    // int padding = 1;
    // int i = 0;
    // unsigned int byte = 0x00;
    // std::stringstream ss;
    // ss << std::hex << blocks[0].substr(blocks[0].length() - (2 * i), blocks[0].length() - (2 * i) + 2) << std::endl;
    // ss >> byte;
    // int character = 0x20;
    // std::cout << "Byte: " << std::hex << byte << std::endl;
    // int byte_res = byte ^ padding ^ character;
    // std::stringstream iv;
    // iv << blocks[0].substr(0, blocks[0].length() - (2 * (i + 1))) << std::hex << byte_res << (i != 0 ? blocks[0].substr(blocks[0].length() - (2 * (i + 1)) + 2, blocks[0].length()) : "");
    // std::cout << "IV: " << iv.str() << std::endl;
    // CURLplusplus curl;
    // std::stringstream url;
    // url << "http://crypto-class.appspot.com/po?er=" << iv.str() << blocks[1];
    // std::cout << "URL: " << url.str() << std::endl;
    // curl.Get(url.str());
    // std::cout << (curl.GetHttpCode() == 404) << std::endl;

    return 0;
}