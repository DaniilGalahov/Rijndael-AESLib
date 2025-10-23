#pragma once
#include "array"
#include "vector"
#include "Define.h"
#include "GF256.h"
#include "Utility.h"

using namespace std;
using namespace GF256;
using namespace Utility;

namespace AES
{
	namespace Auxilliary
	{
		array<array<byte, WordSize>, StateRow> RoundKey(vector<array<byte, WordSize>> w, int round);  //TODO: works correct, add tests
	}

	array<byte, WordSize> RotWord(array<byte, WordSize> a);
	array<byte, WordSize> SubWord(array<byte, WordSize> a, array<byte, SBoxSize> SBox);
	vector<array<byte, WordSize>> KeyExpansion(vector<byte> key, array<byte, SBoxSize> SBox, array<array<byte, WordSize>, RconSize> Rcon, int Nk=4, int Nr=10);
	array<array<byte, StateCol>, StateRow> SubBytes(array<array<byte, StateCol>, StateRow> state, array<byte, SBoxSize> SBox);
	array<array<byte, StateCol>, StateRow> ShiftRows(array<array<byte, StateCol>, StateRow> state);
	array<array<byte, StateCol>, StateRow> MixColumns(array<array<byte, StateCol>, StateRow> state);
	array<array<byte, StateCol>, StateRow> AddRoundKey(array<array<byte, StateCol>, StateRow> state, vector<array<byte, WordSize>> &w, int round);
}