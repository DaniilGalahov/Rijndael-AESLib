#include "CppUnitTest.h"
#include "string"
#include <iomanip>
#include <iostream>
#include "AESLib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AESLib;

namespace AESTest
{
	TEST_CLASS(AESLibTest)
	{
		void LogAsHexString(vector<unsigned char> encryptedData) //ChatGPT hint
		{
			std::ostringstream oss;
			oss << std::hex << std::setfill('0');
			for (size_t i = 0; i < encryptedData.size(); ++i)
			{
				oss << "0x" << std::setw(2) << static_cast<int>(encryptedData[i]);
				if (i != encryptedData.size() - 1)
					oss << ", ";
			}
			Logger::WriteMessage(oss.str().c_str());
		}

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
			vector<unsigned char> data = vector<unsigned char>();
			bool result = RemovePad(data);
			Assert::IsFalse(result);

			data = vector<unsigned char>{ 0x48, 0x45, 0x4C, 0x4C };
			result = RemovePad(data);
			Assert::IsFalse(result);

			data = vector<unsigned char>{ 0x48, 0x45, 0x4C, 0x4C, 0x4F, 0x37};
			result = RemovePad(data);
			Assert::IsFalse(result);
			
			data = vector<unsigned char>{ 0x48, 0x45, 0x4C, 0x4C, 0x4F, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B };
			vector<unsigned char> test = vector<unsigned char>{ 'H','E','L','L','O' };
			result = RemovePad(data);
			Assert::IsTrue(result);
			Assert::AreEqual(5, (int)data.size());
			Assert::AreEqual(test[0], data[0]);
			Assert::AreEqual(test[2], data[2]);
			Assert::AreEqual(test[4], data[4]);
		}

		TEST_METHOD(Test_DeriveKey)
		{
			using namespace AESLib::Auxilliary;
			string password = "mene, mene, tekel, parsin";
			string expected16 = "mene, mene, tek";
			string expected32 = "mene, mene, tekel, parsinmene, ";

			vector<unsigned char> userKey(password.begin(), password.end());

			vector<unsigned char> derivedKey16 = DeriveKey(userKey, 16);
			Assert::AreEqual(16, (int)derivedKey16.size());
			string derived16(derivedKey16.begin(), derivedKey16.end());
			Assert::AreEqual(expected16.data(), derived16.data());
			
			vector<unsigned char> derivedKey32 = DeriveKey(userKey, 32);
			Assert::AreEqual(32, (int)derivedKey32.size());
			string derived32(derivedKey32.begin(), derivedKey32.end());
			Assert::AreEqual(expected32.data(), derived32.data());
		}

		TEST_METHOD(Test_Encrypt)
		{
			string info = "God has numbered the days of your reign and brought it to an end.";
			vector<unsigned char> openData (info.begin(), info.end());
			string password = "mene, mene, tekel, parsin";
			vector<unsigned char> userKey (password.begin(), password.end());
			vector<unsigned char> encryptedData = Encrypt(openData, userKey, Mode::AES128);

			string encryptedInfo(encryptedData.begin(), encryptedData.end());
			Assert::AreNotEqual(info.data(), encryptedInfo.data());

			LogAsHexString(encryptedData);

			vector<unsigned char> expected = vector<unsigned char>{ 0x88, 0x80, 0xea, 0xd0, 0xea, 0xb8, 0x3b, 0x1a, 0x8b, 0x18, 0xae, 0xbc, 0x8d, 0xe3, 0x92, 0x63, 0xec, 0x12, 0xb9, 0x1b, 0x21, 0x33, 0xe4, 0x02, 0x70, 0x92, 0xb4, 0x90, 0xa1, 0x2d, 0x01, 0x96, 0xe2, 0xd6, 0x54, 0x71, 0x8a, 0x2e, 0x5f, 0x90, 0x2c, 0x69, 0x04, 0x29, 0x07, 0xa6, 0x28, 0x8f, 0x79, 0xf5, 0xa0, 0x8f, 0xb7, 0x8d, 0xef, 0xcd, 0x1a, 0x6f, 0x9e, 0x83, 0x2e, 0xc9, 0x7b, 0xb5, 0x2f, 0xa8, 0x3b, 0x42, 0x8b, 0xb6, 0xa5, 0x93, 0x54, 0x91, 0x6f, 0xc9, 0xbc, 0xc4, 0x05, 0x15 };
			Assert::AreEqual(expected.size(), encryptedData.size());
			for (int i = 0; i < encryptedData.size(); i++)
			{
				Assert::AreEqual(expected[i], encryptedData[i]);
			}
		}

		TEST_METHOD(Test_Decrypt)
		{
			vector<unsigned char> encryptedData = vector<unsigned char>{ 0x88, 0x80, 0xea, 0xd0, 0xea, 0xb8, 0x3b, 0x1a, 0x8b, 0x18, 0xae, 0xbc, 0x8d, 0xe3, 0x92, 0x63, 0xec, 0x12, 0xb9, 0x1b, 0x21, 0x33, 0xe4, 0x02, 0x70, 0x92, 0xb4, 0x90, 0xa1, 0x2d, 0x01, 0x96, 0xe2, 0xd6, 0x54, 0x71, 0x8a, 0x2e, 0x5f, 0x90, 0x2c, 0x69, 0x04, 0x29, 0x07, 0xa6, 0x28, 0x8f, 0x79, 0xf5, 0xa0, 0x8f, 0xb7, 0x8d, 0xef, 0xcd, 0x1a, 0x6f, 0x9e, 0x83, 0x2e, 0xc9, 0x7b, 0xb5, 0x2f, 0xa8, 0x3b, 0x42, 0x8b, 0xb6, 0xa5, 0x93, 0x54, 0x91, 0x6f, 0xc9, 0xbc, 0xc4, 0x05, 0x15 };
			string password = "mene, mene, tekel, parsin";
			vector<unsigned char> userKey(password.begin(), password.end());
			vector<unsigned char> openData = Decrypt(encryptedData, userKey, Mode::AES128);

			string info(openData.begin(), openData.end());
			string expected = "God has numbered the days of your reign and brought it to an end.";
			Assert::AreEqual(expected.size(), info.size());
			Assert::AreEqual(expected.data(), info.data());
		}
	};
}