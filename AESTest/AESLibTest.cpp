#include "CppUnitTest.h"
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
			Assert::AreEqual(test[7], data[7]);
		}

		TEST_METHOD(Test_RemovePad)
		{
			using namespace PKCS7;
			vector<unsigned char> data = vector<unsigned char>{ 0x48, 0x45, 0x4C, 0x4C, 0x4F, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B };
			vector<unsigned char> test = vector<unsigned char>{ 'H','E','L','L','O' };
			RemovePad(data);
			Assert::AreEqual(5, (int)data.size());
			Assert::AreEqual(unsigned char('O'), data[4]);
		}
	};
}