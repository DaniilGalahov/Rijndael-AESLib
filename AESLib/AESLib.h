#pragma once
#include "vector"
#include "array"
#include "Utility.h"
#include "SHA256.h"
#include "AES.h"

using namespace std;
using namespace Utility;
using namespace AES;

namespace AESLib
{
	enum Mode
	{
		AES128,
		AES192,
		AES256
	};

	namespace PKCS7
	{
		void AddPad(vector<unsigned char>& data);
		bool RemovePad(vector<unsigned char>& data);
	}

	namespace Auxilliary
	{
		vector<unsigned char> DeriveKey(vector<unsigned char>& userKey, int keySize); //TODO: improve function to utilize PBKDF2-HMAC KDF logic
	}

	namespace Parameters
	{
		static int Nk = 4;
		static int Nr = 10;
		static int keySize = 16;
		void Set(Mode mode);
	}

	vector<unsigned char> Encrypt(vector<unsigned char> openData, vector<unsigned char> userKey, Mode mode);
	vector<unsigned char> Decrypt(vector<unsigned char> encryptedData, vector<unsigned char> userKey, Mode mode);
}