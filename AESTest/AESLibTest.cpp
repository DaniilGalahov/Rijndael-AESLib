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
			oss << "\r\n";
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
			vector<unsigned char> expectedKey16 = vector<unsigned char>{ 0x4e, 0xcf, 0x89, 0x0c, 0x63, 0x82, 0x36, 0xf8, 0xbe, 0xe1, 0xf8, 0x2b, 0x60, 0x0e, 0x70, 0x7a };
			vector<unsigned char> expectedKey32 = vector<unsigned char>{ 0x4e, 0xcf, 0x89, 0x0c, 0x63, 0x82, 0x36, 0xf8, 0xbe, 0xe1, 0xf8, 0x2b, 0x60, 0x0e, 0x70, 0x7a, 0x72, 0x76, 0x61, 0x26, 0xe6, 0x62, 0x5e, 0x6a, 0x17, 0x71, 0x09, 0x3b, 0xd9, 0x03, 0x27, 0x21 };

			vector<unsigned char> userKey(password.begin(), password.end());

			vector<unsigned char> derivedKey16 = DeriveKey(userKey, 16);
			LogAsHexString(derivedKey16);
			Assert::AreEqual(16, (int)derivedKey16.size());
			Assert::AreEqual(expectedKey16[0], derivedKey16[0]);
			Assert::AreEqual(expectedKey16[4], derivedKey16[4]);
			Assert::AreEqual(expectedKey16[8], derivedKey16[8]);
			Assert::AreEqual(expectedKey16[15], derivedKey16[15]);

			vector<unsigned char> derivedKey32 = DeriveKey(userKey, 32);
			LogAsHexString(derivedKey32);
			Assert::AreEqual(32, (int)derivedKey32.size());
			Assert::AreEqual(expectedKey32[0], derivedKey32[0]);
			Assert::AreEqual(expectedKey32[8], derivedKey32[8]);
			Assert::AreEqual(expectedKey32[16], derivedKey32[16]);
			Assert::AreEqual(expectedKey32[31], derivedKey32[31]);
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

			vector<unsigned char> expected = vector<unsigned char>{ 0x69, 0x15, 0x6b, 0xca, 0xd7, 0xe8, 0xe8, 0x7f, 0x11, 0x7e, 0xb8, 0xa1, 0x5c, 0x3b, 0x16, 0x90, 0xbd, 0xf1, 0x57, 0xf7, 0x4a, 0x25, 0xe3, 0x80, 0xfe, 0x6e, 0x87, 0xbe, 0x1e, 0x65, 0xad, 0x3c, 0x2f, 0xe4, 0xee, 0xb5, 0x7a, 0xf1, 0x10, 0x80, 0x35, 0x0f, 0x8a, 0xad, 0xfc, 0xd7, 0x94, 0xf0, 0x90, 0x98, 0x27, 0x21, 0xf1, 0xa4, 0x9b, 0x5a, 0xae, 0x1f, 0x16, 0xcc, 0xa3, 0x8a, 0x5a, 0x59, 0x88, 0xf0, 0xa5, 0xcc, 0x56, 0xad, 0x56, 0xb2, 0xc3, 0xac, 0x4a, 0x23, 0xa5, 0x75, 0xb9, 0xc0 };
			Assert::AreEqual(expected.size(), encryptedData.size());
			for (int i = 0; i < encryptedData.size(); i++)
			{
				Assert::AreEqual(expected[i], encryptedData[i]);
			}
		}

		TEST_METHOD(Test_Decrypt)
		{
			vector<unsigned char> encryptedData = vector<unsigned char>{ 0x69, 0x15, 0x6b, 0xca, 0xd7, 0xe8, 0xe8, 0x7f, 0x11, 0x7e, 0xb8, 0xa1, 0x5c, 0x3b, 0x16, 0x90, 0xbd, 0xf1, 0x57, 0xf7, 0x4a, 0x25, 0xe3, 0x80, 0xfe, 0x6e, 0x87, 0xbe, 0x1e, 0x65, 0xad, 0x3c, 0x2f, 0xe4, 0xee, 0xb5, 0x7a, 0xf1, 0x10, 0x80, 0x35, 0x0f, 0x8a, 0xad, 0xfc, 0xd7, 0x94, 0xf0, 0x90, 0x98, 0x27, 0x21, 0xf1, 0xa4, 0x9b, 0x5a, 0xae, 0x1f, 0x16, 0xcc, 0xa3, 0x8a, 0x5a, 0x59, 0x88, 0xf0, 0xa5, 0xcc, 0x56, 0xad, 0x56, 0xb2, 0xc3, 0xac, 0x4a, 0x23, 0xa5, 0x75, 0xb9, 0xc0 };
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