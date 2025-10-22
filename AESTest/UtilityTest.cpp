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
			Assert::AreEqual(char(0x63), char(SBox[0x00]));
			Assert::AreEqual(char(0xed), char(SBox[0x53]));
			Assert::AreEqual(char(0x16), char(SBox[0xff]));
		}
	};
}