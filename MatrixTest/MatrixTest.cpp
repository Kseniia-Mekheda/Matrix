#include "pch.h"
#include "CppUnitTest.h"
#include "../Matrix/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTest
{
	TEST_CLASS(MatrixTest)
	{
	public:	
		TEST_METHOD(GetElemTest)
		{
			SparseMatrix S(2, 3);
			S.addElement(0, 1, 10);

			Assert::AreEqual(10, S.getElement(0, 1));
			Assert::AreEqual(0, S.getElement(1, 1));
		}

		TEST_METHOD(RemoveElem)
		{
			SparseMatrix S(2, 3);
			S.addElement(0, 1, 10);
			S.addElement(1, 1, 3);

			Assert::AreEqual(10, S.getElement(0, 1));

			S.removeElement(0, 1);
			Assert::AreEqual(0, S.getElement(0, 1));
		}
		TEST_METHOD(AddTest)
		{
			SparseMatrix A(4, 7);
			A.addElement(0, 2, 1);
			A.addElement(1, 5, 8);
			A.addElement(3, 4, 3);
			
			SparseMatrix B(4, 7);
			B.addElement(0, 2, 3);
			B.addElement(1, 1, 4);
			B.addElement(2, 2, 5);

			SparseMatrix Result = A.add_matrix(B);

			Assert::AreEqual(4, Result.getElement(0, 2));
		}
	};
}
