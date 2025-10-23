#pragma once
#include "vector"
#include "array"
#include "Utility.h"
#include "AES.h"

using namespace std;
using namespace Utility;
using namespace AES;

namespace AESLib
{
	namespace PKCS7
	{
		void AddPad(vector<unsigned char>& data);
		bool RemovePad(vector<unsigned char>& data);
	}

	namespace Auxilliary
	{
		vector<unsigned char> DeriveKey(vector<unsigned char>& userKey, size_t keySize); //TODO: change function to usage SHA256 hash for key
	}
	
	enum Mode
	{
		AES128,
		AES192,
		AES256
	};

	vector<unsigned char> Encrypt(vector<unsigned char> data, vector<unsigned char> key, Mode mode);
	vector<unsigned char> Decrypt(vector<unsigned char> data, vector<unsigned char> key, Mode mode);
}