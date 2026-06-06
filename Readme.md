# Rijndael AESLib

![Rijndael logo](/Images/Logo.png)

## Summary
This repository includes:
- Simple C#-based cryptography tool **Rijndael**, utilising AES for encrypting/decrypting files.
- C++ implementation of [Advanced Encryption Standard (AES)](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard), as it described in [NIST.FIPS.197-upd1](/Documentation/NIST.FIPS.197-upd1.pdf)
- C++ implementation of [Secure Hash Standard (SHS) algorithm SHA-256](https://en.wikipedia.org/wiki/SHA-2), as it described in [NIST.FIPS.180-4](/Documentation/NIST.FIPS.180-4.pdf)
- C++/CLI interface library for usage C++ AES implementation in C#-based apps
- C ABI .dll for usage C++ AES implementation with any managed language (Java, Python, TypeScript, anything).

## Usage
This section separated to two subsections - usage of [Rijndael](#Rijndael_usage) app and usage of [C++ AES framework](#AES_development).

---
<a id="Rijndael_usage"></a>
### Rijndael

#### Purpose
This app provides core functionality of AES cryptography, especially:
- encrypting files
- decrypting files

#### Download
Latest version of Rijndael app can be downloaded [here](https://github.com/DaniilGalahov/Rijndael-AESLib/releases).

#### Important notices
1. This app **does not (yet) realize PBKDF2-HMAC KDF logic** - i.e., the AES ciphering in this app utilize key **without** random salt. This is enough for typical tasks, but not yet *fully* followed modern standards of encrypting. Use *big* (10+ symbols) and *well-randomized* password for encrypting important information!
2. **WARNING!!!** You need clearly understand that this is **military grade** encrypting system. I.e., if you encrypt your data and forget (or lost) the password, **NO ONE** will be able to decrypt your information! Typical brute-force time for deciphering AES-256 exceeds time of heat death of Universe.

#### User interface

![User interface](/Images/GUI.png)

User interface of the app allows to set up source, destination and parameters of encrypting/decrypting, initialize encryption/decryption process, and receive feedback from the app.

##### UI elements
- **Source file** field - displays and allows to input path to source file (file with data you want to *process*). You can type the path to file by yourself or select it via GUI dialogue through *"Browse"* button near the end of the field.
- **Destination file** field - displays and allows to input path to destination file (file where *processed* data will be saved). You can type the path to file by yourself or select it via GUI dialogue through *"Browse"* button near the end of the field.
- **Password** field - allows to input your password (any symbols accepted).
- **AES standard** combo box - displays selected AES standard and allows to select other available (*AES-128*, *AES-192* or *AES-256*).
- **Encrypt** button - initializes encrytion process.
*Open data from your source file will be encrypted and saved as AES-ciphered data in destination file*.
- **Decrypt** button - initializes decrytion process.
*Encrypted data from your source file will be decrypted and saved as open data in destination file*.
- **Status** string - displays current application status.
- **Help** link - opens your default web browser and deliver you to the project page (this one you are reading now).

*Notice: system does not touch any info in source file (read-only access), and does not allow to overwrite destination file.*

---
<a id="AES_development"></a>
### C++ AES framework

#### Purpose
This library provides open-source, independent and fully-tested (code coverage by tests ~90%) implementation of AES, "closely following the textbook". Feel free to use it in your own projects (of course, following [License](/License.md) terms).

#### Requirements
- Windows-based OS (Developed on Win 10)
- [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/) 2022 Version 17.14.18 (October 2025)
	- Microsoft.Component.MSBuild
	- Visual C++ 2022 (package ***"Desktop development with C++"*** in VS Installer)
		- Microsoft.VisualStudio.Component.VC.Redist.14.Latest
		- Microsoft.VisualStudio.Component.VC.CLI.Support
	- C# Tools 4.14.0 (package   in VS Installer)
		- Microsoft.Net.Component.4.8.SDK
		- Microsoft.Net.Component.4.8.TargetingPack
		
#### IDE/SDK configuration
For installation of all required components you need to open **Visual Studio Installer -> Workloads**, and install next packages:
- ***Desktop development with C++***
- ***.NET desktop development***

After this, you need to open **Visual Studio Installer -> Individual components**, and there install next components:
- ***.NET Framework 4.8 SDK***
- ***.NET Framework 4.8 targeting pack***
- ***C++/CLI support for v143 build tools (Latest)***

#### Deployment
1. Clone this repo to your computer using:
`git clone https://github.com/DaniilGalahov/Rijndael-AESLib.git`
2. Open it in Visual Studio
3. Rebuild solution (typically *Ctrl+Alt+F7*)
4. ...
5. ~~PROFIT!~~ Ready!

#### Contents
This repository provides:
- Static C++ library **AESLib**, implementing basic functional of AES (encryption and decryption of data)
- C++/CLI interface **AESBridge**, providing access to AESLib functional from C#-based apps
- C ABI **AESABI**, providing access to AESLib functional from any managed language (Java, Python, Rust, TypeScript, you name it)

#### Connecting to third-party project
Library made to be versalite and easy for usage, so to connect it to other project, you should follow standard library integration procedure.

**To use in C++ project**, add AESLib in list of projects of your solution, and add reference to AESLib in project references *or* add AESLib directory of this solution to **Include directory** of your project.
Here is a detailed [description of integration static C++ library into C++ project](https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-static-library-cpp?view=msvc-170).

**To use in C# project**, add AESBridge and AESLib in list of projects of your solution, and add reference to this projects in your project.
Here is a detailed [description of integration C++/CLI components into .NET project](https://learn.microsoft.com/en-us/cpp/build/adding-references-in-visual-cpp-projects?view=msvc-170)

**To use with other programming languages**, follow the standard library integration procedure for selected language. For example, in Python you can use [ctypes](https://docs.python.org/3/library/ctypes.html) library.

#### Coding

##### C++
1. Include `std::vector` (you will need it for work with library) and library header itself
``` c++
#include "vector"
#include "AESLib.h"
```
2. Use required namespaces
``` c++
	using namespace std;
	using namespace AESLib;
```
3. To encrypt data
``` c++
	vector<unsigned char> openData = yourData; //open data as array of bytes (loaded from file, stream, etc.)
	vector<unsigned char> userKey = yourKey; //user-provided key as array of bytes
	Mode mode = Mode::AES128; //encrypting mode (AES128, AES192, AES256 available)
	vector<unsigned char> encryptedData = Encrypt(openData, userKey, mode); //encrypt your data with provided key using given AES mode and return array of bytes (encrypted data).
```
4. To decrypt data
``` c++
	vector<unsigned char> encryptedData = yourData; //encrypted data as array of bytes (loaded from file, stream, etc.)
	vector<unsigned char> userKey = yourKey; //user-provided key as array of bytes
	Mode mode = Mode::AES128; //encrypting mode (AES128, AES192, AES256 available)
	vector<unsigned char> openData = Decrypt(encryptedData, userKey, mode); //decrypt your encrypted data using provided key and given AES mode, and return array of bytes (decrypted data).
```

##### C#
1. Use `System` and `AESBridge`
``` c#
using System;
using AESBridge;
```
2. To encrypt data
``` c#
	Byte[] openData = yourData; //open data as array of bytes (loaded from file, stream, etc.)
	Byte[] userKey = yourKey; //user-provided key as array of bytes
	Mode mode = Mode.AES128; //encrypting mode (AES128, AES192, AES256 available)
	Byte[] encryptedData = AESNative.Encrypt(openData, userKey, mode); //encrypt your data with provided key using given AES mode and return array of bytes (encrypted data).
```
3. To decrypt data
``` c#
	Byte[] encryptedData = yourData; //encrypted data as array of bytes (loaded from file, stream, etc.)
	Byte[] userKey = yourKey; //user-provided key as array of bytes
	Mode mode = Mode.AES128; //encrypting mode (AES128, AES192, AES256 available)
	Byte[] openData = AESNative.Decrypt(encryptedData, userKey, mode); //decrypt your encrypted data using provided key and given AES mode, and return array of bytes (decrypted data).
```

##### Python
*As an example of usage in managed languages*
1. Use `ctypes` to load **AESABI.dll**
``` python
import ctypes

dll_path = "path\to\AESABI.dll" #your actual path to AESABI.dll
aes_dll = ctypes.CDLL(dll_path)
```

2. Define .dll functions signatures
``` python
from ctypes import c_uint8, c_size_t, c_int, POINTER, byref

# Enum for AESMode
AESMode_128 = 0
AESMode_192 = 1
AESMode_256 = 2

#Signature for Encrypt function
aes_dll.Encrypt.argtypes = [
    POINTER(c_uint8), c_size_t,   # input, inputSize
    POINTER(c_uint8), c_size_t,   # key, keySize
    c_int,                         # mode
    POINTER(POINTER(c_uint8)),    # output
    POINTER(c_size_t)              # outputSize
]
aes_dll.Encrypt.restype = c_int

#Signature for Decrypt function
aes_dll.Decrypt.argtypes = [
    POINTER(c_uint8), c_size_t,
    POINTER(c_uint8), c_size_t,
    c_int,
    POINTER(POINTER(c_uint8)),
    POINTER(c_size_t)
]
aes_dll.Decrypt.restype = c_int

#Signature for FreeBuffer function
aes_dll.FreeBuffer.argtypes = [POINTER(c_uint8)]
aes_dll.FreeBuffer.restype = None
```

3. Define Python helper functions
``` python
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
```

Then, use this helper functions to encrypt and decrypt data.

**Important!** Always use `aes_dll.FreeBuffer()` to free memory buffer after usage of `aes_dll.Encrypt()` and `aes_dll.Decrypt()` *exactly* as it shown above to avoid memory leaks.

Full source code of Python example you may find in file [Python/example.py](https://github.com/DaniilGalahov/Rijndael-AESLib/blob/master/Python/example.py).

---
## Questions
Feel free to ask me if you have any questions or offers.

## Legal notice
This software is distributing under MIT/BSD-like license. Full terms are available in the [License](/License.md) file.

Logo image of Rijndael AESLib and an icon of Rijndael application was generated by ChatGPT 5.

---
## Support & donations
If you like this software, please, support me with donations. This will allow me to spend more time on improvement of my projects. Any help will count.

**VISA card (Halyk bank, Worldwide):** 4003 0351 5709 6871

**МИР card (T-bank, Russia only):** 2200 7021 5287 4603

**Recepient:** Daniil Galakhov