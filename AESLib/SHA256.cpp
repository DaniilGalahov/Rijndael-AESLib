#include "SHA256.h"

uint32_t SHA256::Functions::ShR(uint32_t x, uint32_t n)
{
	return x >> n;
}

uint32_t SHA256::Functions::RotR(uint32_t x, uint32_t n, uint32_t w)
{
	return (x >> n) | (x << (w - n));
}

uint32_t SHA256::Functions::Ch(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) ^ (~x & z); // in .pdf of FIPS 180-2 and FIPS 180-4 symbol "~" is not visible!
}

uint32_t SHA256::Functions::Maj(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) ^ (x & z) ^ (y & z);
}

uint32_t SHA256::Functions::Sigma0(uint32_t x)
{
	return RotR(x, 2) ^ RotR(x, 13) ^ RotR(x, 22);
}

uint32_t SHA256::Functions::Sigma1(uint32_t x)
{
	return RotR(x, 6) ^ RotR(x, 11) ^ RotR(x, 25);
}

uint32_t SHA256::Functions::sigma0(uint32_t x)
{
	return RotR(x, 7) ^ RotR(x, 18) ^ ShR(x, 3);
}

uint32_t SHA256::Functions::sigma1(uint32_t x)
{
	return RotR(x, 17) ^ RotR(x, 19) ^ ShR(x, 10);
}

string SHA256::Functions::ToBitString(vector<unsigned char> input)
{
	string inputBits = "";
	for (uint32_t i = 0; i < input.size(); i++)
	{
		unsigned char currentByte = input[i];
		bitset<8> currentBits = bitset<8>(currentByte);
		inputBits += currentBits.to_string();
	}
	return inputBits;
}

string SHA256::Functions::Pad(string inputBits)
{
	uint32_t l = inputBits.size();
	uint32_t k = (448 - (l + 1)) % 512;
	inputBits += "1";
	for (uint32_t i = 0; i < k; i++)
	{
		inputBits += "0";
	}
	inputBits += bitset<64>(uint32_t(l)).to_string();
	return inputBits;
}

vector<array<uint32_t, BlockNumber>> SHA256::Functions::Parse(string paddedInputBits)
{
	uint32_t blockQty = paddedInputBits.size() / BlockSize;
	vector<array<uint32_t, BlockNumber>> M = vector<array<uint32_t, BlockNumber>>(blockQty);
	for (uint32_t i = 0; i < blockQty; i++)
	{
		string currentBlockBits = paddedInputBits.substr(i * BlockSize, BlockSize);
		array<uint32_t, BlockNumber> currentBlock = array<uint32_t, BlockNumber>();
		for (uint32_t j = 0; j < BlockNumber; j++)
		{
			string currentWordBits = currentBlockBits.substr(j * SHAWordSize, SHAWordSize);
			uint32_t word = stoul(currentWordBits, nullptr, 2);
			currentBlock[j] = word;
		}
		M[i] = currentBlock;
	}
	return M;
}

array<uint32_t, MessageScheduleSize> SHA256::Functions::PrepareMessageSchedule(array<uint32_t, BlockNumber> Mi)
{
	array<uint32_t, MessageScheduleSize> W = array<uint32_t, MessageScheduleSize>();
	for (uint32_t t = 0; t < MessageScheduleSize; t++)
	{
		if (t >= 0 && t <= 15)
		{
			W[t] = Mi[t];
		}
		if (t >= 16 && t <= 63)
		{
			W[t] = sigma1(W[t - 2]) + W[t - 7] + sigma0(W[t - 15]) + W[t - 16];
		}
	}
	return W;
}

array<uint32_t,8> SHA256::Hash(vector<unsigned char> input)
{
	using namespace Functions;
	uint32_t T1, T2;
	array<uint32_t, 8> H = Hinit;
	string inputBits = ToBitString(input);
	string paddedInputBits = Pad(inputBits);
	vector<array<uint32_t, BlockNumber>> M = Parse(paddedInputBits);
	uint32_t N = M.size();
	for (uint32_t i = 0; i < N; i++)
	{
		array<uint32_t, MessageScheduleSize> W = PrepareMessageSchedule(M[i]);
		uint32_t a = H[0];
		uint32_t b = H[1];
		uint32_t c = H[2];
		uint32_t d = H[3];
		uint32_t e = H[4];
		uint32_t f = H[5];
		uint32_t g = H[6];
		uint32_t h = H[7];
		for (uint32_t t = 0; t < MessageScheduleSize; t++)
		{
			T1 = h + Sigma1(e) + Ch(e, f, g) + K[t] + W[t];
			T2 = Sigma0(a) + Maj(a, b, c);
			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;
		}
		H[0] = a + H[0];
		H[1] = b + H[1];
		H[2] = c + H[2];
		H[3] = d + H[3];
		H[4] = e + H[4];
		H[5] = f + H[5];
		H[6] = g + H[6];
		H[7] = h + H[7];
	}
	return H;
}