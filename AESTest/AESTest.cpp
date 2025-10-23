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
			Assert::AreEqual(unsigned char(0x01), unsigned char(wr[0]));
			Assert::AreEqual(unsigned char(0x02), unsigned char(wr[1]));
			Assert::AreEqual(unsigned char(0x03), unsigned char(wr[2]));
			Assert::AreEqual(unsigned char(0x00), unsigned char(wr[3]));
		}

		TEST_METHOD(Test_SubWord)
		{
			array<byte, SBoxSize> SBox = BuildSBox();
			array<byte, WordSize> w = array<byte, WordSize> {0x00, 0x01, 0x02, 0x03};
			array<byte, WordSize> ws = SubWord(w, SBox);
			Assert::AreEqual(unsigned char(0x63), unsigned char(ws[0]));
			Assert::AreEqual(unsigned char(0x7c), unsigned char(ws[1]));
			Assert::AreEqual(unsigned char(0x77), unsigned char(ws[2]));
			Assert::AreEqual(unsigned char(0x7b), unsigned char(ws[3]));
		}

		TEST_METHOD(Test_KeyExpansion)
		{
			array<byte, SBoxSize> SBox = BuildSBox();
			array<array<byte, WordSize>, RconSize> Rcon = BuildRcon();
			vector<array<byte, WordSize>> w = KeyExpansion(Example::key128, SBox, Rcon);
			
			Assert::AreEqual(unsigned char(0x2b), unsigned char(w[0][0]));
			Assert::AreEqual(unsigned char(0x7e), unsigned char(w[0][1]));
			Assert::AreEqual(unsigned char(0x15), unsigned char(w[0][2]));
			Assert::AreEqual(unsigned char(0x16), unsigned char(w[0][3]));

			Assert::AreEqual(unsigned char(0x11), unsigned char(w[23][0]));
			Assert::AreEqual(unsigned char(0xf9), unsigned char(w[23][1]));
			Assert::AreEqual(unsigned char(0x15), unsigned char(w[23][2]));
			Assert::AreEqual(unsigned char(0xbc), unsigned char(w[23][3]));

			Assert::AreEqual(unsigned char(0xb6), unsigned char(w[43][0]));
			Assert::AreEqual(unsigned char(0x63), unsigned char(w[43][1]));
			Assert::AreEqual(unsigned char(0x0c), unsigned char(w[43][2]));
			Assert::AreEqual(unsigned char(0xa6), unsigned char(w[43][3]));
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

		TEST_METHOD(Test_Cipher)
		{
			int Nk = 4;
			int Nr = 10;
			array<array<byte, StateCol>, StateRow> in = InputToState(Example::input);
			array<byte, SBoxSize> SBox = BuildSBox();
			array<array<byte, WordSize>, RconSize> Rcon = BuildRcon();
			vector<array<byte, WordSize>> w = KeyExpansion(Example::key128, SBox, Rcon, Nk, Nr);
			array<array<byte, StateCol>, StateRow> state = Cipher(in, Nr, w, SBox);
			Assert::AreEqual(unsigned char(0x39), unsigned char(state[0][0]));
			Assert::AreEqual(unsigned char(0xdc), unsigned char(state[1][1]));
			Assert::AreEqual(unsigned char(0x85), unsigned char(state[2][2]));
			Assert::AreEqual(unsigned char(0x32), unsigned char(state[3][3]));
		}

		TEST_METHOD(Test_InvMixColumns)
		{
			array<array<byte, StateCol>, StateRow> state = InputToState(Example::input);
			array<array<byte, StateCol>, StateRow> mixedState = MixColumns(state);
			array<array<byte, StateCol>, StateRow> invertedMixedState = InvMixColumns(mixedState);
			Assert::AreEqual(unsigned char(state[0][0]), unsigned char(invertedMixedState[0][0]));
			Assert::AreEqual(unsigned char(state[1][1]), unsigned char(invertedMixedState[1][1]));
			Assert::AreEqual(unsigned char(state[2][2]), unsigned char(invertedMixedState[2][2]));
			Assert::AreEqual(unsigned char(state[3][3]), unsigned char(invertedMixedState[3][3]));
		}

		TEST_METHOD(Test_KeyExpansionEIC)
		{
			array<byte, SBoxSize> SBox = BuildSBox();
			array<array<byte, WordSize>, RconSize> Rcon = BuildRcon();
			vector<array<byte, WordSize>> dw = KeyExpansionEIC(Example::key128, SBox, Rcon);

			Assert::AreEqual(unsigned char(0x2b), unsigned char(dw[0][0]));
			Assert::AreEqual(unsigned char(0x7e), unsigned char(dw[0][1]));
			Assert::AreEqual(unsigned char(0x15), unsigned char(dw[0][2]));
			Assert::AreEqual(unsigned char(0x16), unsigned char(dw[0][3]));

			Assert::AreEqual(unsigned char(0xe9), unsigned char(dw[23][0]));
			Assert::AreEqual(unsigned char(0xfd), unsigned char(dw[23][1]));
			Assert::AreEqual(unsigned char(0xb9), unsigned char(dw[23][2]));
			Assert::AreEqual(unsigned char(0x72), unsigned char(dw[23][3]));

			Assert::AreEqual(unsigned char(0xb6), unsigned char(dw[43][0]));
			Assert::AreEqual(unsigned char(0x63), unsigned char(dw[43][1]));
			Assert::AreEqual(unsigned char(0x0c), unsigned char(dw[43][2]));
			Assert::AreEqual(unsigned char(0xa6), unsigned char(dw[43][3]));
		}

		TEST_METHOD(Test_InvShiftRows)
		{
			array<array<byte, StateCol>, StateRow> state = InputToState(Example::input);
			array<array<byte, StateCol>, StateRow> invertedShiftedState = InvShiftRows(state);
			Assert::AreEqual(unsigned char(state[0][0]), unsigned char(invertedShiftedState[0][0]));
			Assert::AreEqual(unsigned char(state[1][0]), unsigned char(invertedShiftedState[1][1]));
			Assert::AreEqual(unsigned char(state[2][0]), unsigned char(invertedShiftedState[2][2]));
			Assert::AreEqual(unsigned char(state[3][0]), unsigned char(invertedShiftedState[3][3]));
		}

		TEST_METHOD(Test_InvSubBytes)
		{
			array<byte, SBoxSize> SBox = BuildSBox();
			array<byte, SBoxSize> InvSBox = InverseSBox(SBox);
			array<array<byte, StateCol>, StateRow> state = InputToState(Example::input);
			array<array<byte, StateCol>, StateRow> subState = SubBytes(state, SBox);
			array<array<byte, StateCol>, StateRow> invSubState = InvSubBytes(subState, InvSBox);
			Assert::AreEqual(unsigned char(state[0][0]), unsigned char(invSubState[0][0]));
			Assert::AreEqual(unsigned char(state[1][3]), unsigned char(invSubState[1][3]));
			Assert::AreEqual(unsigned char(state[3][3]), unsigned char(invSubState[3][3]));
		}
	};
}