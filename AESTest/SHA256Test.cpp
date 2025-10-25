#include "CppUnitTest.h"
#include "SHA256.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SHA256;

namespace AESTest
{
	TEST_CLASS(SHA256Test)
	{
	public:

		TEST_METHOD(Test_Sanity)
		{
			Assert::IsTrue(true);
		}

		TEST_METHOD(Test_ShR)
		{
			using namespace Functions;
			uint32_t x = 65536;
			uint32_t n = 1;
			uint32_t result = ShR(x, n);
			Assert::AreEqual(uint32_t(32768), result);
		}

		TEST_METHOD(Test_RotR)
		{
			using namespace Functions;
			uint32_t x = 65536;
			uint32_t n = 1;
			uint32_t result = RotR(x, n);
			Assert::AreEqual(uint32_t(140737488388096), result);
		}

		TEST_METHOD(Test_Ch)
		{
			using namespace Functions;
			uint32_t x = 65536;
			uint32_t y = 65536;
			uint32_t z = 32768;
			uint32_t result = Ch(x, y, z);
			Assert::AreEqual(uint32_t(65536), result);
		}

		TEST_METHOD(Test_Maj)
		{
			using namespace Functions;
			uint32_t x = 65536;
			uint32_t y = 65536;
			uint32_t z = 65536;
			uint32_t result = Maj(x, y, z);
			Assert::AreEqual(uint32_t(65536), result);
		}

		TEST_METHOD(Test_Sigma0)
		{
			using namespace Functions;
			uint32_t x = 65536;
			uint32_t result = Sigma0(x);
			Assert::AreEqual(uint32_t(67125256), result);
		}

		TEST_METHOD(Test_Sigma1)
		{
			using namespace Functions;
			uint32_t x = 65536;
			uint32_t result = Sigma1(x);
			Assert::AreEqual(uint32_t(8389664), result);
		}

		TEST_METHOD(Test_sigma0)
		{
			using namespace Functions;
			uint32_t x = 65536;
			uint32_t result = sigma0(x);
			Assert::AreEqual(uint32_t(1073750528), result);
		}

		TEST_METHOD(Test_sigma1)
		{
			using namespace Functions;
			uint32_t x = 65536;
			uint32_t result = sigma1(x);
			Assert::AreEqual(uint32_t(2684354624), result);
		}

		TEST_METHOD(Test_ToBitString)
		{
			using namespace Functions;
			string characters = "abc";
			vector<unsigned char> input = vector<unsigned char>(characters.begin(), characters.end());
			string bits = ToBitString(input);
			Assert::AreEqual(string("011000010110001001100011"), bits);
		}

		TEST_METHOD(Test_Pad)
		{
			using namespace Functions;
			string characters = "abc";
			vector<unsigned char> input = vector<unsigned char>(characters.begin(), characters.end());
			string inputBits = ToBitString(input);
			string paddedInputBits = Pad(inputBits);
			Assert::AreEqual(size_t(512), paddedInputBits.size());
			Assert::AreEqual(string("011000010110001001100011"), paddedInputBits.substr(0,24));
			Assert::AreEqual(string("011000"), paddedInputBits.substr(506, 6));
		}

		TEST_METHOD(Test_Parse)
		{
			using namespace Functions;
			string characters = "abc";
			vector<unsigned char> input = vector<unsigned char>(characters.begin(), characters.end());
			string inputBits = ToBitString(input);
			string paddedInputBits = Pad(inputBits);
			vector<array<uint32_t, BlockNumber>> M = Parse(paddedInputBits);
			Assert::AreEqual(size_t(1), M.size());
			Assert::AreEqual(size_t(16), M[0].size());
			Assert::AreEqual(uint32_t(1633837952), M[0][0]);
		}

		TEST_METHOD(Test_PrepareMessageSchedule)
		{
			using namespace Functions;
			string characters = "abc";
			vector<unsigned char> input = vector<unsigned char>(characters.begin(), characters.end());
			string inputBits = ToBitString(input);
			string paddedInputBits = Pad(inputBits);
			vector<array<uint32_t, BlockNumber>> M = Parse(paddedInputBits);
			array<uint32_t, MessageScheduleSize> W = PrepareMessageSchedule(M[0]);
			Assert::AreEqual(size_t(64), W.size());
			Assert::AreEqual(uint32_t(1633837952), W[0]);
			Assert::AreEqual(uint32_t(3552024379), W[31]);
			Assert::AreEqual(uint32_t(313650667), W[63]);
		}
	};
}