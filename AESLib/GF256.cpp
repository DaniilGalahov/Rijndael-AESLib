#include "GF256.h"

char GF256::ClampToByte(char c)
{
	return c & 0xff;
}

GF256::byte::byte(char c)
{
	value = GF256::ClampToByte(c);
}

GF256::byte::byte(int i)
	:byte(char(i)) {}

GF256::byte::byte()
	:byte(0x00) {}


GF256::byte::operator char() const
{
	return value;
}

GF256::byte::operator int() const
{
	return int(operator char());
}

bool GF256::byte::operator==(byte other) const
{
	if (value == other.value)
		return true;
	else
		return false;
}

bool GF256::byte::operator==(char other) const
{
	return operator==(byte(other));
}

bool GF256::byte::operator==(int other) const
{
	return operator==(char(other));
}

bool GF256::byte::operator!=(byte other) const
{
	return !(operator==(other));
}

bool GF256::byte::operator!=(char other) const
{
	return operator!=(byte(other));
}

bool GF256::byte::operator!=(int other) const
{
	return operator!=(char(other));
}

GF256::byte GF256::byte::operator+(byte other) const
{
	return byte(value ^ other.value);
}

GF256::byte GF256::byte::operator&(byte other) const
{
	return byte(value & other.value);
}

GF256::byte GF256::byte::ShiftedLeft(int offset)
{
	return byte(value << offset);
}

GF256::byte GF256::byte::ShiftedRight(int offset)
{
	return byte(value >> offset);
}

GF256::byte GF256::byte::operator*(byte other) const
{
	byte b = 0x00;
	byte result = 0x00;
	byte bitMask = 0x01;
	for (int shift = 0; shift < 8; shift++)
	{
		if (bitMask == 0x01)
		{
			b = value;
		}
		else
		{
			b = xTimes(b);
		}
		if ((other & bitMask) != 0x00)
		{
			result=result+b;
		}
		bitMask = bitMask.ShiftedLeft(1);
	}
	return result;
}

GF256::byte GF256::byte::Inversed()
{
	byte result = 0x01;
	byte base = value;
	int exp = 254;
	while (exp > 0)
	{
		if ((byte(exp) & byte(1)) != 0x00)
		{
			result = result * base;
		}
		base = base * base;
		exp >>= 1;
	}
	return result;
}

GF256::byte GF256::xTimes(GF256::byte b)
{
	if ((b & byte(0x80)) == 0x00)
	{
		return b.ShiftedLeft(1);
	}
	else
	{
		return b.ShiftedLeft(1) + byte(0x1b);
	}
}