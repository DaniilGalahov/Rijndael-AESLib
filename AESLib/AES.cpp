#include "AES.h"

array<byte, WordSize> AES::RotWord(array<byte, WordSize> a)
{
	return array<byte, WordSize> {a[1], a[2], a[3], a[0]};
}

array<byte, WordSize> AES::SubWord(array<byte, WordSize> a, array<byte, SBoxSize> SBox)
{
	return array<byte, WordSize> {SBox[int(a[0])], SBox[int(a[1])], SBox[int(a[2])], SBox[int(a[3])]};
}

vector<array<byte, WordSize>> AES::KeyExpansion(vector<byte> key, array<byte, SBoxSize> SBox, array<array<byte, WordSize>, RconSize> Rcon, int Nk, int Nr)
{
	vector<array<byte, WordSize>> w = vector<array<byte, WordSize>>((4 * Nr) + 3 + 1);
	int i = 0;
	while (i <= (Nk - 1))
	{
		for (int j = 0; j < WordSize; j++)
		{
			w[i][j] = key[(WordSize * i) + j];
		}
		i++;
	}
	while (i <= (4 * Nr) + 3)
	{
		array<byte, WordSize> temp = w[i - 1];
		if (i % Nk == 0)
		{
			temp = SubWord(RotWord(temp), SBox);
			for (int j = 0; j < WordSize; j++)
			{
				temp[j] = temp[j] + Rcon[int(i / Nk)][j];
			}
		}
		else if ((Nk > 6) && (i % Nk == 4))
		{
			temp = SubWord(temp, SBox);
		}
		for (int j = 0; j < WordSize; j++)
		{
			w[i][j] = w[i - Nk][j] + temp[j];
		}
		i++;
	}
	return w;
}

array<array<byte, StateCol>, StateRow> AES::SubBytes(array<array<byte, StateCol>, StateRow> state, array<byte, SBoxSize> SBox)
{
	array<array<byte, StateCol>, StateRow> subState = array<array<byte, StateCol>, StateRow>();
	for (int r = 0; r < StateRow; r++)
	{
		for (int c = 0; c < StateCol; c++)
		{
			subState[r][c] = SBox[int(state[r][c])];
		}
	}
	return subState;
}

array<array<byte, StateCol>, StateRow> AES::ShiftRows(array<array<byte, StateCol>, StateRow> state)
{
	array<array<byte, StateCol>, StateRow> shiftedState = array<array<byte, StateCol>, StateRow>();
	for (int r = 0; r < StateRow; r++)
	{
		for (int c = 0; c < StateCol; c++)
		{
			shiftedState[r][c] = state[r][(c+r)%4];
		}
	}
	return shiftedState;
}