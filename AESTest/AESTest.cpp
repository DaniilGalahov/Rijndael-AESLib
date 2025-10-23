#include "CppUnitTest.h"
#include "AES.h"
#include "Utility.h"
#include "Example.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AES;
using namespace Utility;

namespace AESTest
{
	TEST_CLASS(AESTest)
	{
	public:
		
		TEST_METHOD(Test_Sanity)
		{
			Assert::IsTrue(true);
		}

		TEST_METHOD(Test_RotWord)
		{
			array<byte, WordSize> w = array<byte, WordSize> {0x00, 0x01, 0x02, 0x03};
			array<byte, WordSize> wr = RotWord(w);
			Assert::AreEqual(unsigned char(wr[0]), unsigned char(0x01));
			Assert::AreEqual(unsigned char(wr[1]), unsigned char(0x02));
			Assert::AreEqual(unsigned char(wr[2]), unsigned char(0x03));
			Assert::AreEqual(unsigned char(wr[3]), unsigned char(0x00));
		}

		TEST_METHOD(Test_SubWord)
		{
			array<byte, SBoxSize> SBox = BuildSBox();
			array<byte, WordSize> w = array<byte, WordSize> {0x00, 0x01, 0x02, 0x03};
			array<byte, WordSize> ws = SubWord(w, SBox);
			Assert::AreEqual(unsigned char(ws[0]), unsigned char(0x63));
			Assert::AreEqual(unsigned char(ws[1]), unsigned char(0x7c));
			Assert::AreEqual(unsigned char(ws[2]), unsigned char(0x77));
			Assert::AreEqual(unsigned char(ws[3]), unsigned char(0x7b));
		}

		TEST_METHOD(Test_KeyExpansion)
		{
			array<byte, SBoxSize> SBox = BuildSBox();
			array<array<byte, WordSize>, RconSize> Rcon = BuildRcon();
			vector<array<byte, WordSize>> w = KeyExpansion(Example::key128, SBox, Rcon);
			
			Assert::AreEqual(unsigned char(w[0][0]), unsigned char(0x2b));
			Assert::AreEqual(unsigned char(w[0][1]), unsigned char(0x7e));
			Assert::AreEqual(unsigned char(w[0][2]), unsigned char(0x15));
			Assert::AreEqual(unsigned char(w[0][3]), unsigned char(0x16));

			Assert::AreEqual(unsigned char(w[23][0]), unsigned char(0x11));
			Assert::AreEqual(unsigned char(w[23][1]), unsigned char(0xf9));
			Assert::AreEqual(unsigned char(w[23][2]), unsigned char(0x15));
			Assert::AreEqual(unsigned char(w[23][3]), unsigned char(0xbc));

			Assert::AreEqual(unsigned char(w[43][0]), unsigned char(0xb6));
			Assert::AreEqual(unsigned char(w[43][1]), unsigned char(0x63));
			Assert::AreEqual(unsigned char(w[43][2]), unsigned char(0x0c));
			Assert::AreEqual(unsigned char(w[43][3]), unsigned char(0xa6));
		}

		TEST_METHOD(Test_SubBytes)
		{
			array<byte, SBoxSize> SBox = BuildSBox();
			array<array<byte, StateCol>, StateRow> state = InputToState(Example::input);
			array<array<byte, StateCol>, StateRow> subState = SubBytes(state, SBox);
			Assert::AreEqual(unsigned char(0x23), unsigned char(subState[0][0]));
			Assert::AreEqual(unsigned char(0x9a), unsigned char(subState[1][3]));
			Assert::AreEqual(unsigned char(0x18), unsigned char(subState[3][3]));
		}

		TEST_METHOD(Test_ShiftRows)
		{
			array<array<byte, StateCol>, StateRow> state = InputToState(Example::input);
			array<array<byte, StateCol>, StateRow> shiftedState = ShiftRows(state);
			Assert::AreEqual(unsigned char(state[0][0]), unsigned char(shiftedState[0][0]));
			Assert::AreEqual(unsigned char(state[1][0]), unsigned char(shiftedState[1][3]));
			Assert::AreEqual(unsigned char(state[2][0]), unsigned char(shiftedState[2][2]));
			Assert::AreEqual(unsigned char(state[3][0]), unsigned char(shiftedState[3][1]));
		}

		TEST_METHOD(Test_MixColumns)
		{
			array<array<byte, StateCol>, StateRow> state = InputToState(Example::input);
			array<array<byte, StateCol>, StateRow> mixedState = MixColumns(state);
			Assert::AreEqual(unsigned char(0xff), unsigned char(mixedState[0][0]));
			Assert::AreEqual(unsigned char(0xb3), unsigned char(mixedState[1][3]));
			Assert::AreEqual(unsigned char(0x63), unsigned char(mixedState[3][3]));
		}

		TEST_METHOD(Test_AddRoundKey)
		{
			array<array<byte, StateCol>, StateRow> state = InputToState(Example::input);
			array<byte, SBoxSize> SBox = BuildSBox();
			array<array<byte, WordSize>, RconSize> Rcon = BuildRcon();
			vector<array<byte, WordSize>> w = KeyExpansion(Example::key128, SBox, Rcon);
			array<array<byte, StateCol>, StateRow> stateWithKey = AddRoundKey(state, w, 0);
			Assert::AreEqual(unsigned char(0x19), unsigned char(stateWithKey[0][0]));
			Assert::AreEqual(unsigned char(0xf4), unsigned char(stateWithKey[1][1]));
			Assert::AreEqual(unsigned char(0x8d), unsigned char(stateWithKey[2][2]));
			Assert::AreEqual(unsigned char(0x08), unsigned char(stateWithKey[3][3]));
		}
	};
}