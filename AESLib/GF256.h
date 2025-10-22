#pragma once

namespace GF256
{
	char ClampToByte(char c);
	
	class byte
	{
	private:
		char value = 0x00;

	public:
		byte(char c);
		byte(int i);
		byte();
		operator char() const;
		operator int() const;
		bool operator == (byte other) const;
		bool operator == (char other) const;
		bool operator == (int other) const;
		bool operator != (byte other) const;
		bool operator != (char other) const;
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