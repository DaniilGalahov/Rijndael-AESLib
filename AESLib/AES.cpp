#include "AES.h"

array<array<byte, WordSize>, StateRow> AES::Auxilliary::RoundKey(vector<array<byte, WordSize>> w, int round)
{
	array<array<byte, WordSize>, StateRow> roundKey = array<array<byte, WordSize>, StateRow>();
	for (int i = 0; i < StateRow; i++)
	{
		for (int j = 0; j < WordSize;j++)
		{
			roundKey[j][i] = w[(4*round)+i][j];
		}
	}
	return roundKey;
}

array<array<byte, StateCol>, StateRow> AES::Auxilliary::WordsToState(vector<array<byte, WordSize>> words)
{
	array<array<byte, StateCol>, StateRow> state = array<array<byte, StateCol>, StateRow>();
	for (int r = 0; r < StateRow; r++)
	{
		for (int c = 0; c < StateCol; c++)
		{
			state[c][r] = words[r][c];
		}
	}
	return state;
}

vector<array<byte, WordSize>> AES::Auxilliary::StateToWords(array<array<byte, StateCol>, StateRow> state)
{
	vector<array<byte, WordSize>> words = vector<array<byte, WordSize>>(StateRow);
	for (int r = 0; r < StateRow; r++)
	{
		for (int c = 0; c < WordSize; c++)
		{
			words[r][c] = state[c][r];
		}
	}
	return words;
}

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

array<array<byte, StateCol>, StateRow> AES::MixColumns(array<array<byte, StateCol>, StateRow> state)
{
	array<array<byte, StateCol>, StateRow> mixedState = array<array<byte, StateCol>, StateRow>();
	for (int c = 0; c < StateCol; c++)
	{
		mixedState[0][c] = (byte(0x02) * state[0][c]) + (byte(0x03) * state[1][c]) + state[2][c] + state[3][c];
		mixedState[1][c] = state[0][c] + (byte(0x02) * state[1][c]) + (byte(0x03) * state[2][c]) + state[3][c];
		mixedState[2][c] = state[0][c] + state[1][c] + (byte(0x02) * state[2][c]) + (byte(0x03) * state[3][c]);
		mixedState[3][c] = (byte(0x03) * state[0][c]) + state[1][c] + state[2][c] + (byte(0x02) * state[3][c]);
	}
	return mixedState;
}

array<array<byte, StateCol>, StateRow> AES::AddRoundKey(array<array<byte, StateCol>, StateRow> state, vector<array<byte, WordSize>> w, int round)
{
	using namespace Auxilliary;
	array<array<byte, WordSize>, StateRow> roundKey = RoundKey(w, round);
	array<array<byte, StateCol>, StateRow> stateWithKey = array<array<byte, StateCol>, StateRow>();
	for (int c = 0; c < StateCol; c++)
	{
		for (int r = 0; r < StateRow; r++)
		{
			stateWithKey[r][c] = state[r][c] + roundKey[r][c];
		}
	}
	return stateWithKey;
}

array<array<byte, StateCol>, StateRow> AES::Cipher(array<array<byte, StateCol>, StateRow> in, int Nr, vector<array<byte, WordSize>> w, array<byte, SBoxSize> SBox)
{
	array<array<byte, StateCol>, StateRow> state = in;
	state = AddRoundKey(state, w, 0);
	for (int round = 1; round <= Nr - 1; round++)
	{
		state = SubBytes(state,SBox);
		state = ShiftRows(state);
		state = MixColumns(state);
		state = AddRoundKey(state, w, round);
	}
	state = SubBytes(state, SBox);
	state = ShiftRows(state);
	state = AddRoundKey(state, w, Nr);
	return state;
}

array<array<byte, StateCol>, StateRow> AES::InvShiftRows(array<array<byte, StateCol>, StateRow> state)
{
	array<array<byte, StateCol>, StateRow> invertedShiftedState = array<array<byte, StateCol>, StateRow>();
	for (int r = 0; r < StateRow; r++)
	{
		for (int c = 0; c < StateCol; c++)
		{
			int offset = (c - r) % 4;
			if (offset < 0)
			{
				offset = 4 + offset;
			}
			invertedShiftedState[r][c] = state[r][offset];
		}
	}
	return invertedShiftedState;
}

array<array<byte, StateCol>, StateRow> AES::InvSubBytes(array<array<byte, StateCol>, StateRow> state, array<byte, SBoxSize> InvSBox)
{
	array<array<byte, StateCol>, StateRow> invSubState = array<array<byte, StateCol>, StateRow>();
	for (int r = 0; r < StateRow; r++)
	{
		for (int c = 0; c < StateCol; c++)
		{
			invSubState[r][c] = InvSBox[int(state[r][c])];
		}
	}
	return invSubState;
}

array<array<byte, StateCol>, StateRow> AES::InvMixColumns(array<array<byte, StateCol>, StateRow> state)
{
	array<array<byte, StateCol>, StateRow> invertedMixedState = array<array<byte, StateCol>, StateRow>();
	for (int c = 0; c < StateCol; c++)
	{
		invertedMixedState[0][c] = (byte(0x0e) * state[0][c]) + (byte(0x0b) * state[1][c]) + (byte(0x0d) * state[2][c]) + (byte(0x09) * state[3][c]);
		invertedMixedState[1][c] = (byte(0x09) * state[0][c]) + (byte(0x0e) * state[1][c]) + (byte(0x0b) * state[2][c]) + (byte(0x0d) * state[3][c]);
		invertedMixedState[2][c] = (byte(0x0d) * state[0][c]) + (byte(0x09) * state[1][c]) + (byte(0x0e) * state[2][c]) + (byte(0x0b) * state[3][c]);
		invertedMixedState[3][c] = (byte(0x0b) * state[0][c]) + (byte(0x0d) * state[1][c]) + (byte(0x09) * state[2][c]) + (byte(0x0e) * state[3][c]);
	}
	return invertedMixedState;
}

array<array<byte, StateCol>, StateRow> AES::InvCipher(array<array<byte, StateCol>, StateRow> in, int Nr, vector<array<byte, WordSize>> w, array<byte, SBoxSize> InvSBox)
{
	array<array<byte, StateCol>, StateRow> state = in;
	state = AddRoundKey(state, w, Nr);
	for (int round = Nr - 1; round >= 1; round--)
	{
		state = InvShiftRows(state);
		state = InvSubBytes(state, InvSBox);
		state = AddRoundKey(state, w, round);
		state = InvMixColumns(state);
	}
	state = InvShiftRows(state);
	state = InvSubBytes(state, InvSBox);
	state = AddRoundKey(state, w, 0);
	return state;
}

vector<array<byte, WordSize>> AES::KeyExpansionEIC(vector<byte> key, array<byte, SBoxSize> SBox, array<array<byte, WordSize>, RconSize> Rcon, int Nk, int Nr)
{
	using namespace Auxilliary;
	vector<array<byte, WordSize>> dw = KeyExpansion(key, SBox, Rcon, Nk, Nr);
	for (int round = 1; round <= Nr - 1; round++)
	{
		int i = 4 * round;
		vector<array<byte, WordSize>> words = vector<array<byte, WordSize>>(StateRow);
		for (int j = 0; j < StateRow; j++)
		{
			words[j] = dw[i + j];
		}
		vector<array<byte, WordSize>> invertedWords = StateToWords(InvMixColumns(WordsToState(words)));
		for (int j = 0; j < StateRow; j++)
		{
			dw[i + j] = invertedWords[j];
		}
	}
	return dw;
}

array<array<byte, StateCol>, StateRow> AES::EqInvCipher(array<array<byte, StateCol>, StateRow> in, int Nr, vector<array<byte, WordSize>> dw, array<byte, SBoxSize> InvSBox)
{
	array<array<byte, StateCol>, StateRow> state = in;
	state = AddRoundKey(state, dw, Nr);
	for (int round = Nr - 1; round >= 1; round--)
	{
		state = InvSubBytes(state, InvSBox);
		state = InvShiftRows(state);
		state = InvMixColumns(state);
		state = AddRoundKey(state, dw, round);
	}
	state = InvSubBytes(state, InvSBox);
	state = InvShiftRows(state);
	state = AddRoundKey(state, dw, 0);
	return state;
}