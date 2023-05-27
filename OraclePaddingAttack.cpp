#include "OraclePaddingAttack.hpp"

std::string OraclePaddingAttack::attack(std::string iv, std::string ciphertext, bool isLastBlock)
{
    std::cout << "IV: " << iv << std::endl;
    std::cout << "Ciphertext: " << ciphertext << std::endl;
    std::array<char, 16> plaintext;
    std::vector<int> cipher_bytes = Converter::hexStringToBytes(iv);
    std::vector<int> cipher_bytes_copy;
    cipher_bytes_copy.assign(cipher_bytes.begin(), cipher_bytes.end());
    int count = 0;
    int paddingValue = 0;

    for (int padding = 1; padding < 16 + 1; padding++)
    {
        if (padding - count > 1)
        {
            std::cout << "Padding error: " << std::dec << count << std::endl;
            std::cout << "Padding error: " << std::dec << padding << std::endl;
            break;
        }

        // for (int character = 0x20; character < 0x7A; character++)

        int characterStart = isLastBlock && padding == 1 ? 0x02 : 0x20;
        int characterEnd = isLastBlock && padding == 1 ? 0x0F : 0x7A;

        // int character = characterStart;
        int character = isLastBlock && padding <= paddingValue ? paddingValue : characterStart;

        for (; character < characterEnd + 1; character++)
        {
            // std::cout << "Character: " << std::dec << character << std::endl;
            plaintext[16 - padding] = character;

            for (int i = 15; i >= 16 - padding; i--)
            {
                cipher_bytes[i] = cipher_bytes_copy[i] ^ padding ^ plaintext[i];
            }

            std::stringstream iv;
            for (int i = 0; i < cipher_bytes.size(); i++)
            {
                iv << std::hex << std::setw(2) << std::setfill('0') << cipher_bytes[i];
            }

            CURLplusplus curl;
            std::stringstream url;
            url << "http://crypto-class.appspot.com/po?er=" << iv.str() << ciphertext;
            curl.Get(url.str());
            int http_code = curl.GetHttpCode();
            if (http_code == 404)
            {
                std::cout << "Byte: " << std::hex << character << std::endl;
                std::cout << "IV: " << iv.str() << std::endl;
                cipher_bytes[16 - padding] = cipher_bytes_copy[16 - padding];
                count++;
                break;
            }
            else if (http_code != 403)
            {
                std::cout << "HTTP Code unknown: " << std::dec << http_code << std::endl;
                break;
            }
        }

        if (isLastBlock && padding == 1)
        {
            if (padding == 1)
            {
                paddingValue = character;
            }
        }
    }

    std::string plaintext_string;
    plaintext_string.assign(plaintext.begin(), plaintext.end());
    return plaintext_string;
}