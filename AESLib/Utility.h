#pragma once
#include "array"
#include "GF256.h"

#define SBoxSize 256

using namespace std;
using namespace GF256;

namespace Utility
{
	namespace Auxilliary
	{
		unsigned char RotL8(unsigned char v, int r);
		unsigned char AffineTransform(unsigned char x);
	}
	
	array<byte, SBoxSize> BuildSBox();
	array<byte, SBoxSize> InverseSBox(array<byte, SBoxSize> SBox);
	array<array<byte, 4>, 10> BuildRcon();
}