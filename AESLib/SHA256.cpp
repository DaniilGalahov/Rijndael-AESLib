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