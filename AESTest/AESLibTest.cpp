#include "CppUnitTest.h"
#include "string"
#include "AESLib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AESLib;

namespace AESTest
{
	TEST_CLASS(AESLibTest)
	{
	public:

		TEST_METHOD(Test_Sanity)
		{
			Assert::IsTrue(true);
		}

		TEST_METHOD(Test_AddPad)
		{
			using namespace PKCS7;
			vector<unsigned char> data = vector<unsigned char> { 'H','E','L','L','O' };
			vector<unsigned char> test = vector<unsigned char> { 0x48, 0x45, 0x4C, 0x4C, 0x4F, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B };
			AddPad(data);
			Assert::AreEqual(16, (int)data.size());
			Assert::AreEqual(test[0], data[0]);
			Assert::AreEqual(test[7], data[7]);
			Assert::AreEqual(test[15], data[15]);
		}

		TEST_METHOD(Test_RemovePad)
		{
			using namespace PKCS7;
			vector<unsigned char> data = vector<unsigned char>{ 0x48, 0x45, 0x4C, 0x4C, 0x4F, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B };
			vector<unsigned char> test = vector<unsigned char>{ 'H','E','L','L','O' };
			RemovePad(data);
			Assert::AreEqual(5, (int)data.size());
			Assert::AreEqual(test[0], data[0]);
			Assert::AreEqual(test[2], data[2]);
			Assert::AreEqual(test[4], data[4]);
		}

		TEST_METHOD(Test_DeriveKey)
		{
			using namespace AESLib::Auxilliary;
			string key = "mene, mene, tekel, parsin";
			vector<unsigned char> keyVector(key.begin(), key.end());
			string expected = "mene, mene, tekel, parsinmene, ";
			vector<unsigned char> expectedVector(expected.begin(), expected.end());
			vector<unsigned char> derivedVector = DeriveKey(keyVector,32);
			string derived(derivedVector.begin(), derivedVector.end());
			Assert::AreEqual(32, (int)derivedVector.size());
			Assert::AreEqual(expected.data(), derived.data());
		}

		/*
		TEST_METHOD(Test_Encrypt)
		{
			string info = "Lead the way my master";
			vector<unsigned char> data (info.begin(), info.end());
			string password = "28 08 1975";
			vector<unsigned char> key (password.begin(), password.end());
			Mode mode = Mode::AES128;
			vector<unsigned char> encryptedData = Encrypt(data, key, mode);
			string encryptedInfo(encryptedData.begin(), encryptedData.end());
			Assert::AreNotEqual(info, encryptedInfo);
		}
		*/
	};
}