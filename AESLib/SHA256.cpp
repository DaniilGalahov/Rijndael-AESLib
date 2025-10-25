#include "SHA256.h"

unsigned long SHA256::Functions::ShR(unsigned long x, unsigned long n)
{
	return x >> n;
}

unsigned long SHA256::Functions::RotR(unsigned long x, unsigned long n, unsigned long w)
{
	return (x >> n) | (x << (w - n));
}

unsigned long SHA256::Functions::Ch(unsigned long x, unsigned long y, unsigned long z)
{
	return (x & y) ^ (x & z);
}

unsigned long SHA256::Functions::Maj(unsigned long x, unsigned long y, unsigned long z)
{
	return (x & y) ^ (x & z) ^ (y & z);
}

unsigned long SHA256::Functions::Sigma0(unsigned long x)
{
	return RotR(x, 2) ^ RotR(x, 13) ^ RotR(x, 22);
}

unsigned long SHA256::Functions::Sigma1(unsigned long x)
{
	return RotR(x, 6) ^ RotR(x, 11) ^ RotR(x, 25);
}

unsigned long SHA256::Functions::sigma0(unsigned long x)
{
	return RotR(x, 7) ^ RotR(x, 18) ^ ShR(x, 3);
}

unsigned long SHA256::Functions::sigma1(unsigned long x)
{
	return RotR(x, 17) ^ RotR(x, 19) ^ ShR(x, 10);
}

string SHA256::Functions::ToBitString(vector<unsigned char> input)
{
	string inputBits = "";
	for (unsigned long i = 0; i < input.size(); i++)
	{
		unsigned char currentByte = input[i];
		bitset<8> currentBits = bitset<8>(currentByte);
		inputBits += currentBits.to_string();
	}
	return inputBits;
}

string SHA256::Functions::Pad(string inputBits)
{
	unsigned long l = inputBits.size();
	unsigned long k = (448 - (l + 1)) % 512;
	inputBits += "1";
	for (unsigned long i = 0; i < k; i++)
	{
		inputBits += "0";
	}
	inputBits += bitset<64>(unsigned long long(l)).to_string();
	return inputBits;
}

vector<array<unsigned long, BlockNumber>> SHA256::Functions::Parse(string paddedInputBits)
{
	unsigned long blockQty = paddedInputBits.size() / BlockSize;
	vector<array<unsigned long, BlockNumber>> M = vector<array<unsigned long, BlockNumber>>(blockQty);
	for (unsigned long i = 0; i < blockQty; i++)
	{
		string currentBlockBits = paddedInputBits.substr(i * BlockSize, BlockSize);
		array<unsigned long, BlockNumber> currentBlock = array<unsigned long, BlockNumber>();
		for (unsigned long j = 0; j < BlockNumber; j++)
		{
			string currentWordBits = currentBlockBits.substr(j * WordSize, WordSize);
			unsigned long word = stoul(currentWordBits, nullptr, 2);
			currentBlock[j] = word;
		}
		M[i] = currentBlock;
	}
	return M;
}

array<unsigned long, MessageScheduleSize> SHA256::Functions::PrepareMessageSchedule(array<unsigned long, BlockNumber> Mi)
{
	array<unsigned long, MessageScheduleSize> W = array<unsigned long, MessageScheduleSize>();
	for (unsigned long t = 0; t < MessageScheduleSize; t++)
	{
		if (t >= 0 && t <= 15)
		{
			W[t] = Mi[t];
		}
		if (t >= 16 && t <= 63)
		{
			W[t] = sigma1(W[t - 2]) ^ W[t - 7] ^ sigma0(W[t - 15]) ^ W[t - 16];
		}
	}
	return W;
}

vector<unsigned char> SHA256::Hash(vector<unsigned char> input)
{
	using namespace Functions;
	string inputBits = ToBitString(input);
	string paddedInputBits = Pad(inputBits);
	vector<array<unsigned long, BlockNumber>> M = Parse(paddedInputBits);
	unsigned long N = M.size();
	for (unsigned long i = 1; i < N; i++)
	{
		array<unsigned long, MessageScheduleSize> W = PrepareMessageSchedule(M[i]);
	}

	return vector<unsigned char>(0);
}