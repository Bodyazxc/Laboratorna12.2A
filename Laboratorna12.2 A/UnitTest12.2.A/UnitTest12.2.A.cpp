#include "pch.h"
#include "CppUnitTest.h"
#include "../Laboratorna12.2 A/Laboratorna12.2 A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest122A
{
	TEST_CLASS(UnitTest122A)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int N = 3;
			Students* S = new Students[N];

			S[0].grade_physics = 3;
			S[0].grade_math = 3;
			S[0].grade_info = 3;

			S[1].grade_physics = 4;
			S[1].grade_math = 4;
			S[1].grade_info = 4;

			S[2].grade_physics = 2;
			S[2].grade_math = 2;
			S[2].grade_info = 2;

			double percentage = PercentageLowAverage(S, N);

			Assert::AreEqual(percentage, 66.6667, 0.01);

			delete[] S;
		}
	};
}
