#include "CppUnitTest.h"
#include "GF28.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AESTest
{
	TEST_CLASS(GF28Test)
	{
	public:

		TEST_METHOD(Test_Sanity)
		{
			Assert::IsTrue(true);
		}

		TEST_METHOD(Test_Equal)
		{
			char a = 0x57;
			char b = 0x57;
			char c = 0x83;

			Assert::IsTrue(GF28::Equal(a, b));
			Assert::IsFalse(GF28::Equal(a, c));
			Assert::IsFalse(GF28::Equal(b, c));
		}
	};
}