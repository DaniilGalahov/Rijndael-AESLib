#pragma once
#include "array"
#include "Define.h"
#include "GF256.h"

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
	array<array<byte, WordSize>, RconSize> BuildRcon();
	array<array<byte, StateCol>, StateRow> InputToState(array<byte, DataSize> input);
}