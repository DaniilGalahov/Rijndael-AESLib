#Example of usage AESABI.dll in Python (created with ChatGPT as co-programmer)
import ctypes
from ctypes import c_uint8, c_size_t, c_int, POINTER, byref

# Load the DLL (assuming we running script from %repository_folder%\Python)
dll_path = "..\\x64\\Release\\AESABI.dll"
aes_dll = ctypes.CDLL(dll_path)

# Enum for AESMode
AESMode_128 = 0
AESMode_192 = 1
AESMode_256 = 2

# Define function signatures
aes_dll.Encrypt.argtypes = [
    POINTER(c_uint8), c_size_t,   # input, inputSize
    POINTER(c_uint8), c_size_t,   # key, keySize
    c_int,                         # mode
    POINTER(POINTER(c_uint8)),    # output
    POINTER(c_size_t)              # outputSize
]
aes_dll.Encrypt.restype = c_int

aes_dll.Decrypt.argtypes = [
    POINTER(c_uint8), c_size_t,
    POINTER(c_uint8), c_size_t,
    c_int,
    POINTER(POINTER(c_uint8)),
    POINTER(c_size_t)
]
aes_dll.Decrypt.restype = c_int

aes_dll.FreeBuffer.argtypes = [POINTER(c_uint8)]
aes_dll.FreeBuffer.restype = None

# Helper functions for Python
def encrypt(data: bytes, key: bytes, mode: int = AESMode_256) -> bytes:
    input_buf = (c_uint8 * len(data))(*data)
    key_buf = (c_uint8 * len(key))(*key)
    output_ptr = POINTER(c_uint8)()
    output_size = c_size_t(0)

    result = aes_dll.Encrypt(
        input_buf, len(data),
        key_buf, len(key),
        mode,
        byref(output_ptr),
        byref(output_size)
    )

    if result != 0:
        raise RuntimeError(f"Encrypt failed with error code {result}")

    output = bytes(output_ptr[:output_size.value])
    aes_dll.FreeBuffer(output_ptr)
    return output

def decrypt(data: bytes, key: bytes, mode: int = AESMode_256) -> bytes:
    input_buf = (c_uint8 * len(data))(*data)
    key_buf = (c_uint8 * len(key))(*key)
    output_ptr = POINTER(c_uint8)()
    output_size = c_size_t(0)

    result = aes_dll.Decrypt(
        input_buf, len(data),
        key_buf, len(key),
        mode,
        byref(output_ptr),
        byref(output_size)
    )

    if result != 0:
        raise RuntimeError(f"Decrypt failed with error code {result}")

    output = bytes(output_ptr[:output_size.value])
    aes_dll.FreeBuffer(output_ptr)
    return output

# Example usage
if __name__ == "__main__":
    key = b"Reliable_32_byte_key_for_AES-256"  # 32 bytes for AES-256
    plaintext = b"A very secret message"

    encrypted = encrypt(plaintext, key, AESMode_256)
    print("Encrypted:", encrypted.hex())

    decrypted = decrypt(encrypted, key, AESMode_256)
    print("Decrypted:", decrypted.decode())
