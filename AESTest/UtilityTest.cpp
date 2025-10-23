#include "CppUnitTest.h"
#include "Utility.h"
#include "Example.h"

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
			array<array<byte, WordSize>, RconSize> Rcon = BuildRcon();
			Assert::AreEqual(unsigned char(0x01), unsigned char(Rcon[1][0]));
			Assert::AreEqual(unsigned char(0x00), unsigned char(Rcon[5][3]));
			Assert::AreEqual(unsigned char(0x1b), unsigned char(Rcon[9][0]));
		}

		TEST_METHOD(Test_InputToState)
		{
			array<array<byte, StateCol>, StateRow> state = InputToState(Example::input);
			Assert::AreEqual(unsigned char(Example::input[0]), unsigned char(state[0][0]));
			Assert::AreEqual(unsigned char(Example::input[13]), unsigned char(state[1][3]));
			Assert::AreEqual(unsigned char(Example::input[15]), unsigned char(state[3][3]));
		}

		TEST_METHOD(Test_StateToOutput)
		{
			array<array<byte, StateCol>, StateRow> state = InputToState(Example::input);
			array<byte, DataSize> output = StateToOutput(state);
			Assert::AreEqual(unsigned char(Example::input[0]), unsigned char(output[0]));
			Assert::AreEqual(unsigned char(Example::input[13]), unsigned char(output[13]));
			Assert::AreEqual(unsigned char(Example::input[15]), unsigned char(output[15]));
		}
	};
}