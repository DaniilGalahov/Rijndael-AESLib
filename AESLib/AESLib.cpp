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
	return true;
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

void AESLib::Parameters::Set(Mode mode)
{
	if (mode == Mode::AES192)
	{
		Nk = 6;
		Nr = 12;
		keySize = 24;
	}

	if (mode == Mode::AES256)
	{
		Nk = 8;
		Nr = 14;
		keySize = 32;
	}
}

vector<unsigned char> AESLib::Encrypt(vector<unsigned char> data, vector<unsigned char> key, Mode mode)
{
	using namespace AESLib::PKCS7;
	using namespace AESLib::Auxilliary;
	using namespace AESLib::Parameters;

	Set(mode);

	array<byte, SBoxSize> SBox = BuildSBox();
	array<array<byte, WordSize>, RconSize> Rcon = BuildRcon();

	vector<unsigned char> derivedKey = DeriveKey(key,keySize);
	vector<byte> byteKey(derivedKey.begin(), derivedKey.end());
	vector<array<byte, WordSize>> w = KeyExpansion(byteKey, SBox, Rcon, Nk, Nr);

	AddPad(data);

	vector<unsigned char> output = vector<unsigned char>(data.size(), 0x00);

	for (int i = 0; i < data.size(); i = i + DataSize)
	{
		array<byte, DataSize> input = array<byte, DataSize>();
		for (int j = 0; j < DataSize; j++)
		{
			input[j] = byte(data[i + j]);
		}

		array<array<byte, StateCol>, StateRow> in = InputToState(input);
		array<array<byte, StateCol>, StateRow> state = Cipher(in, Nr, w, SBox);
		array<byte, DataSize> out = StateToOutput(state);

		for (int j = 0; j < DataSize; j++)
		{
			output[i + j] = unsigned char(out[j]);
		}
	}

	return output; //TODO: continue from here
}