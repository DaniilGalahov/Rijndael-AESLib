#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <array>
#include "AESLib.h"
#include "SHA256.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum AESMode
    {
        AESMode_128 = 0,
        AESMode_192 = 1,
        AESMode_256 = 2
    } AESMode;

    // Encrypts `input` using `key` of size `keySize` and AES mode.
    // The output buffer is allocated inside the function; caller must free it via FreeBuffer.
    // Returns 0 on success, non-zero on error.
    int Encrypt
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
    int Decrypt
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
    int Hash
    (
        const uint8_t* input,
        size_t inputSize,
        uint8_t** output,
        size_t* outputSize
    );

    // Frees buffer allocated by Encrypt/Decrypt
    void FreeBuffer(uint8_t* buffer);

#ifdef __cplusplus
}
#endif