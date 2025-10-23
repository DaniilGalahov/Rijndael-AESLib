#include "AESLib.h"

void AESLib::PKCS7::AddPad(vector<unsigned char>& data)
{
	size_t blockSize = 16;
	size_t pad = blockSize - (data.size() % blockSize);
	if (pad == 0)
	{
		pad = blockSize;
	}
	data.insert(data.end(), pad, unsigned char(pad));
}

bool AESLib::PKCS7::RemovePad(vector<unsigned char>& data)
{
	if (data.empty())
	{
		return false;
	}
	unsigned char pad = data.back();
	if (pad == 0 || pad > 16 || data.size() < pad)
	{
		return false;
	}
	for (size_t i = 0; i < size_t(pad); ++i)
	{
		if (data[data.size() - 1 - i] != pad)
		{
			return false;
		}
	}
	data.resize(data.size() - pad);
}

vector<unsigned char> AESLib::Auxilliary::DeriveKey(vector<unsigned char>& userKey, size_t keySize)
{
	vector<unsigned char> derivedKey = vector<unsigned char>(keySize, 0x00);
	array<byte, SBoxSize> SBox = BuildSBox();
	int i = 0;
	while (i < keySize)
	{
		if (i < userKey.size())
		{
			derivedKey[i] = userKey[i];
		}
		else
		{
			derivedKey[i] = SBox[i];
		}
		i++;
	}
	return derivedKey;
}