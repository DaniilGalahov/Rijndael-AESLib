#include "AESABI.h"
#include <stdlib.h>
#include <string.h>
#include "AESLib.h"  // Native C++ AES implementation

int Encrypt
(
    const uint8_t* input,
    size_t inputSize,
    const uint8_t* key,
    size_t keySize,
    AESMode mode,
    uint8_t** output,
    size_t* outputSize
)
{
    if (!input || !key || !output || !outputSize) return -1;

    *output = NULL;
    *outputSize = 0;

    int result = 0;
    try
    {
        std::vector<unsigned char> inVec(input, input + inputSize);
        std::vector<unsigned char> keyVec(key, key + keySize);
        auto outVec = AESLib::Encrypt(std::move(inVec), std::move(keyVec), static_cast<AESLib::Mode>(mode));

        *outputSize = outVec.size();
        *output = (uint8_t*)malloc(*outputSize);
        if (!*output) return -2;

        memcpy(*output, outVec.data(), *outputSize);
    }
    catch (...)
    {
        result = -3;
    }

    return result;
}

int Decrypt
(
    const uint8_t* input,
    size_t inputSize,
    const uint8_t* key,
    size_t keySize,
    AESMode mode,
    uint8_t** output,
    size_t* outputSize
)
{
    if (!input || !key || !output || !outputSize) return -1;

    *output = NULL;
    *outputSize = 0;

    int result = 0;
    try
    {
        std::vector<unsigned char> inVec(input, input + inputSize);
        std::vector<unsigned char> keyVec(key, key + keySize);
        auto outVec = AESLib::Decrypt(std::move(inVec), std::move(keyVec), static_cast<AESLib::Mode>(mode));

        *outputSize = outVec.size();
        *output = (uint8_t*)malloc(*outputSize);
        if (!*output) return -2;

        memcpy(*output, outVec.data(), *outputSize);
    }
    catch (...)
    {
        result = -3;
    }

    return result;
}

void FreeBuffer(uint8_t* buffer)
{
    if (buffer)
    {
        free(buffer);
    }
}