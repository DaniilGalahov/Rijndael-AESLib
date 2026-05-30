#pragma once
#include <array>
#include "AESLib.h"
#include "SHA256.h"

#ifdef _WIN32
#define DLL_FUNCTION extern "C" __declspec(dllexport)
#else
#define DLL_FUNCTION extern "C"
#endif

DLL_FUNCTION typedef enum AESMode
{
    AESMode_128 = 0,
    AESMode_192 = 1,
    AESMode_256 = 2
} AESMode;

// Encrypts `input` using `key` of size `keySize` and AES mode.
// The output buffer is allocated inside the function; caller must free it via FreeBuffer.
// Returns 0 on success, non-zero on error.
DLL_FUNCTION int Encrypt
(
    const uint8_t* input,
    size_t inputSize,
    const uint8_t* key,
    size_t keySize,
    AESMode mode,
    uint8_t** output,
    size_t* outputSize
);

// Decrypts `input` using `key` of size `keySize` and AES mode.
// The output buffer is allocated inside the function; caller must free it via FreeBuffer.
// Returns 0 on success, non-zero on error.
DLL_FUNCTION int Decrypt
(
    const uint8_t* input,
    size_t inputSize,
    const uint8_t* key,
    size_t keySize,
    AESMode mode,
    uint8_t** output,
    size_t* outputSize
);

//Calculated SHA256 hash
DLL_FUNCTION int Hash
(
    const uint8_t* input,
    size_t inputSize,
    uint8_t** output,
    size_t* outputSize
);

// Frees buffer allocated by Encrypt/Decrypt
DLL_FUNCTION void FreeBuffer(uint8_t* buffer);