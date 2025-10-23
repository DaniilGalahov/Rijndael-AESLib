#include "Utility.h"

unsigned char Utility::Auxilliary::RotL8(unsigned char v, int r)
{
	return ClampToByte(((v << r) | (v >> (8 - r))));
}

unsigned char Utility::Auxilliary::AffineTransform(unsigned char x)
{
	unsigned char y = x ^ RotL8(x, 1) ^ RotL8(x, 2) ^ RotL8(x, 3) ^ RotL8(x, 4) ^ 0x63;
	return y & 0xff;
}

array<byte, SBoxSize> Utility::BuildSBox()
{
	using namespace Auxilliary;
	array<byte, SBoxSize> SBox;
	for (int a = 0; a < SBoxSize; a++)
	{
		SBox[a] = byte(AffineTransform(byte(a).Inversed()));
	}
	return SBox;
}

array<byte, SBoxSize> Utility::InverseSBox(array<byte, SBoxSize> SBox)
{
	array<byte, SBoxSize> InvSBox;
	for (int a = 0; a < SBoxSize; a++)
	{
		InvSBox[(int)SBox[a]] = byte(a);
	}
	return InvSBox;
}

array<array<byte, WordSize>, RconSize> Utility::BuildRcon()
{
	array<array<byte, WordSize>, RconSize> Rcon;
	Rcon[0] = array<byte, WordSize> {0x00, 0xff, 0xff, 0xff};
	Rcon[1] = array<byte, WordSize> {0x01, 0x00, 0x00, 0x00};
	Rcon[2] = array<byte, WordSize>{0x02, 0x00, 0x00, 0x00};
	Rcon[3] = array<byte, WordSize> {0x04, 0x00, 0x00, 0x00};
	Rcon[4] = array<byte, WordSize> {0x08, 0x00, 0x00, 0x00};
	Rcon[5] = array<byte, WordSize> {0x10, 0x00, 0x00, 0x00};
	Rcon[6] = array<byte, WordSize> {0x20, 0x00, 0x00, 0x00};
	Rcon[7] = array<byte, WordSize> {0x40, 0x00, 0x00, 0x00};
	Rcon[8] = array<byte, WordSize> {0x80, 0x00, 0x00, 0x00};
	Rcon[9] = array<byte, WordSize> {0x1b, 0x00, 0x00, 0x00};
	Rcon[10] = array<byte, WordSize> {0x36, 0x00, 0x00, 0x00};
	return Rcon;
}