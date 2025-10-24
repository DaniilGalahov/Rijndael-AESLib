#include "CppUnitTest.h"
#include "GF256.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GF256;

namespace AESTest
{
	TEST_CLASS(GF256Test)
	{
	public:

		TEST_METHOD(Test_Sanity)
		{
			Assert::IsTrue(true);
		}

		TEST_METHOD(Test_ClampToByte)
		{
			unsigned char a = unsigned char(0x15c); //0x57 * 4 - more than what can be represented by one byte
			unsigned char b = ClampToByte(a);
			Assert::AreEqual(unsigned char(0x5c), b);
		}

		TEST_METHOD(Test_Equal)
		{
			byte a = 0x57;
			byte b = 0x57;
			byte c = 0x83;
			Assert::IsTrue(a==b);
			Assert::IsFalse(a==c);
			Assert::IsFalse(b==c);
		}

		TEST_METHOD(Test_NotEqual)
		{
			byte a = 0x57;
			byte b = 0x83;
			Assert::IsTrue(a != b);
		}

		TEST_METHOD(Test_Add)
		{
			byte a = 0x57;
			byte b = 0x83;
			byte c = a + b;
			Assert::AreEqual(unsigned char(0xd4), unsigned char(c));
		}

		TEST_METHOD(Test_And)
		{
			byte a = 0x57;
			byte b = 0x83;
			byte c = a & b;
			Assert::AreEqual(unsigned char(0x03), unsigned char(c));
		}

		TEST_METHOD(Test_ShiftedLeft)
		{
			byte a = 0x57;
			Assert::AreEqual(unsigned char(0xae), unsigned char(a.ShiftedLeft(1)));
		}

		TEST_METHOD(Test_ShiftedRight)
		{
			byte a = 0x57;
			Assert::AreEqual(unsigned char(0x2b), unsigned char(a.ShiftedRight(1)));
		}

		TEST_METHOD(Test_xTimes)
		{
			Assert::AreEqual(unsigned char(0xae), unsigned char(xTimes(0x57)));
			Assert::AreEqual(unsigned char(0x47), unsigned char(xTimes(0xae)));
			Assert::AreEqual(unsigned char(0x8e), unsigned char(xTimes(0x47)));
			Assert::AreEqual(unsigned char(0x07), unsigned char(xTimes(0x8e)));
			Assert::AreEqual(unsigned char(0x0e), unsigned char(xTimes(0x07)));
			Assert::AreEqual(unsigned char(0x1c), unsigned char(xTimes(0x0e)));
			Assert::AreEqual(unsigned char(0x38), unsigned char(xTimes(0x1c)));
		}

		TEST_METHOD(Test_Multiply)
		{
			byte a = 0x57;
			byte b = 0x13;
			byte c = a * b;
			Assert::AreEqual(unsigned char(0xfe), unsigned char(c));
		}

		TEST_METHOD(Test_Inversed)
		{
			byte a = 0x57;
			byte i = a.Inversed();
			Assert::AreEqual(unsigned char(0x01), unsigned char(a * i));
		}
	};
}