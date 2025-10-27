# Rijndael AESLib

## Summary
This repository includes:
- C++ implementation of [Advanced Encryption Standard (AES)](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard), as it described in [NIST.FIPS.197-upd1](/Documentation/NIST.FIPS.197-upd1.pdf)
- C++ implementation of [Secure Hash Standard (SHS) algorithm SHA-256](https://en.wikipedia.org/wiki/SHA-2), as it described in [NIST.FIPS.180-4](/Documentation/NIST.FIPS.180-4.pdf)
- C++/CLI interface library for usage C++ AES implementation in C#-based apps
- Simple C#-based cryptography tool **Rijndael**, utilising AES for encrypting/decrypting files.

## Usage
This section separated to two subsections - usage of [AESLib](#AESLib_usage) and usage of [Rijndael](#Rijndael_usage) app.

---
<a id="AESLib_usage"></a>
### AESLib

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
**AESLib** provides:
- Static C++ library AESLib, implementing basic functional of AES (encryption and decryption of data)
- C++/CLI interface AESBridge, providing access to AESLib functional from C#-based apps

#### Connecting to third-party project
Library made to be versalite and easy for usage, so to connect it to other project, you should follow standard library integration procedure.

**To use in C++ project**, add AESLib in list of projects of your solution, and add reference to AESLib in project references *or* add AESLib directory of this solution to **Include directory** of your project.
Here is a detailed [description of integration static C++ library into C++ project](https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-static-library-cpp?view=msvc-170).

**To use in C# project**, add AESBridge and AESLib in list of projects of your solution, and add reference to this projects in your project.
Here is a detailed [description of integration C++/CLI components into .NET project](https://learn.microsoft.com/en-us/cpp/build/adding-references-in-visual-cpp-projects?view=msvc-170)

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
	//open data as array of bytes (loaded from file, stream, etc.)
	vector<unsigned char> openData = yourData;
	
	//user-provided key as array of bytes
	vector<unsigned char> userKey = yourKey;
	
	//encrypting mode (AES128, AES192, AES256 available)
	Mode mode = Mode::AES128;
	
	//encrypt your data with provided key using given AES mode 
	//and return array of bytes (encrypted data).
	vector<unsigned char> encryptedData = Encrypt(openData, userKey, mode);
```
4. To decrypt data
``` c++
	//encrypted data as array of bytes (loaded from file, stream, etc.)
	vector<unsigned char> encryptedData = yourData;
	
	//user-provided key as array of bytes
	vector<unsigned char> userKey = yourKey;
	
	//encrypting mode (AES128, AES192, AES256 available)
	Mode mode = Mode::AES128;
	
	//decrypt your encrypted data using provided key and given AES mode, 
	//and return array of bytes (decrypted data).
	vector<unsigned char> openData = Decrypt(encryptedData, userKey, mode);
```

##### C#
1. Use `System` and `AESBridge`
``` c#
using System;
using AESBridge;
```
2. To encrypt data
``` c#
	//open data as array of bytes (loaded from file, stream, etc.)
	Byte[] openData = yourData;
	
	//user-provided key as array of bytes
	Byte[] userKey = yourKey;
	
	//encrypting mode (AES128, AES192, AES256 available)
	Mode mode = Mode.AES128;
	
	//encrypt your data with provided key using given AES mode 
	//and return array of bytes (encrypted data).
	Byte[] encryptedData = AES.Encrypt(openData, userKey, mode);
```
3. To decrypt data
``` c#
	//encrypted data as array of bytes (loaded from file, stream, etc.)
	Byte[] encryptedData = yourData;
	
	//user-provided key as array of bytes
	Byte[] userKey = yourKey;
	
	//encrypting mode (AES128, AES192, AES256 available)
	Mode mode = Mode.AES128;
	
	//decrypt your encrypted data using provided key and given AES mode,
	//and return array of bytes (decrypted data).
	Byte[] openData = AES.Decrypt(encryptedData, userKey, mode);
```

---
<a id="Rijndael_usage"></a>
### Rijndael

#### Purpose
This app provides core functionality of AES cryptography, especially:
- encrypting files
- decrypting files

#### Important notices
1. This app **does not (yet) realize PBKDF2-HMAC KDF logic** - i.e., the AES ciphering in this app utilize key **without** random salt. This is enough for typical tasks, but not yet *fully* followed modern standards of encrypting. Use *big* (10+ symbols) and *well-randomized* password for encrypting important information!
2. **WARNING!!!** You need clearly understand that this is **military grade** encrypting system. I.e., if you encrypt your data and forget (or lost) the password, **NO ONE** will be able to decrypt your information! Typical brute-force time for deciphering AES-256 exceeds time of heat death of Universe.

#### User interface
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
## Questions
Feel free to ask me through PM if you have any questions or offers.

## Legal notice
This software is distributing under MIT/BSD-like license. Full terms are available in the [License](/License.md) file.

Logo image of Rijndael AESLib and an icon of Rijndael application was generated by ChatGPT 5.