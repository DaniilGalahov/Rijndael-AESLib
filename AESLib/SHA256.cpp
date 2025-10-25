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