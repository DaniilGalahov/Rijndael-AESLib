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
			char a = 0x15c; //0x57 * 4 - more than what can be represented by one byte
			char b = ClampToByte(a);
			Assert::AreEqual(char(0x5c), b);
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
			Assert::AreEqual(char(0xd4), char(c));
		}

		TEST_METHOD(Test_And)
		{
			byte a = 0x57;
			byte b = 0x83;
			byte c = a & b;
			Assert::AreEqual(char(0x03), char(c));
		}

		TEST_METHOD(Test_ShiftedLeft)
		{
			byte a = 0x57;
			Assert::AreEqual(char(0xae), char(a.ShiftedLeft(1)));
		}

		TEST_METHOD(Test_ShiftedRight)
		{
			byte a = 0x57;
			Assert::AreEqual(char(0x2b), char(a.ShiftedRight(1)));
		}

		TEST_METHOD(Test_xTimes)
		{
			Assert::AreEqual(char(0xae), char(xTimes(0x57)));
			Assert::AreEqual(char(0x47), char(xTimes(0xae)));
			Assert::AreEqual(char(0x8e), char(xTimes(0x47)));
			Assert::AreEqual(char(0x07), char(xTimes(0x8e)));
			Assert::AreEqual(char(0x0e), char(xTimes(0x07)));
			Assert::AreEqual(char(0x1c), char(xTimes(0x0e)));
			Assert::AreEqual(char(0x38), char(xTimes(0x1c)));
		}

		TEST_METHOD(Test_Multiply)
		{
			byte a = 0x57;
			byte b = 0x13;
			byte c = a * b;
			Assert::AreEqual(char(0xfe), char(c));
		}

		TEST_METHOD(Test_Inversed)
		{
			byte a = 0x57;
			byte i = a.Inversed();
			Assert::AreEqual(char(0x01), char(a * i));
		}
	};
}