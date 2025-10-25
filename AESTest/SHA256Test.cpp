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
			unsigned long x = 65536;
			unsigned long n = 1;
			unsigned long result = ShR(x, n);
			Assert::AreEqual(unsigned long(32768), result);
		}

		TEST_METHOD(Test_RotR)
		{
			using namespace Functions;
			unsigned long x = 65536;
			unsigned long n = 1;
			unsigned long result = RotR(x, n);
			Assert::AreEqual(unsigned long(140737488388096), result);
		}

		TEST_METHOD(Test_Ch)
		{
			using namespace Functions;
			unsigned long x = 65536;
			unsigned long y = 65536;
			unsigned long z = 32768;
			unsigned long result = Ch(x, y, z);
			Assert::AreEqual(unsigned long(65536), result);
		}
	};
}