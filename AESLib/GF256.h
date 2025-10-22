#pragma once

namespace GF256
{
	unsigned char ClampToByte(unsigned char c);
	
	class byte
	{
	private:
		unsigned char value = 0x00;

	public:
		byte(unsigned char c);
		byte(int i);
		byte();
		operator unsigned char() const;
		operator int() const;
		bool operator == (byte other) const;
		bool operator == (unsigned char other) const;
		bool operator == (int other) const;
		bool operator != (byte other) const;
		bool operator != (unsigned char other) const;
		bool operator != (int other) const;
		byte operator+ (byte other) const;
		byte operator& (byte other) const;
		byte ShiftedLeft(int offset);
		byte ShiftedRight(int offset);
		byte operator* (byte other) const;
		byte Inversed();
	};

	byte xTimes(byte b);
}