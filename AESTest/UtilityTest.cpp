#include "CppUnitTest.h"
#include "Utility.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Utility;

namespace AESTest
{
	TEST_CLASS(UtilityTest)
	{
	public:

		TEST_METHOD(Test_Sanity)
		{
			Assert::IsTrue(true);
		}

		TEST_METHOD(Test_BuildSBox)
		{
			array<byte, SBoxSize> SBox = BuildSBox();
			Assert::AreEqual(unsigned char(0x63), unsigned char(SBox[0x00]));
			Assert::AreEqual(unsigned char(0xed), unsigned char(SBox[0x53]));
			Assert::AreEqual(unsigned char(0x16), unsigned char(SBox[0xff]));
		}

		TEST_METHOD(Test_InverseSBox)
		{
			array<byte, SBoxSize> SBox = BuildSBox();
			array<byte, SBoxSize> InvSBox = InverseSBox(SBox);
			Assert::AreEqual(unsigned char(0x52), unsigned char(InvSBox[0x00]));
			Assert::AreEqual(unsigned char(0x50), unsigned char(InvSBox[0x53]));
			Assert::AreEqual(unsigned char(0x7d), unsigned char(InvSBox[0xff]));
		}

		TEST_METHOD(Test_BuildRcon)
		{
			array<array<byte, 4>, 10> Rcon = BuildRcon();
			Assert::AreEqual(unsigned char(Rcon[1 - 1][0]), unsigned char(0x01));
			Assert::AreEqual(unsigned char(Rcon[5 - 1][3]), unsigned char(0x00));
			Assert::AreEqual(unsigned char(Rcon[9 - 1][0]), unsigned char(0x1b));
		}
	};
}