#include "simpleMatrixTest.h"

namespace lhsTest{
	void simpleMatrixTest::Run()
	{
		printf("\tsimpleMatrixTest...");

		testConstructor();
		testAssignment();
		testElementAssignment();
		testElementExtraction();
		testTranspose();

		testUnsafeConstructor();
		testUnsafeAssignment();
		testUnsafeElementAssignment();
		testUnsafeElementExtraction();

		printf("passed\n");
	}

	void simpleMatrixTest::testConstructor()
	{
		matrix<int> a = matrix<int>(4, 3);
		Assert(a.nrows == 4 && a.ncols == 3, "Constructor 1 failed");
		matrix<int> b;
		b = matrix<int>(5, 6);
		Assert(b.nrows == 5 && b.ncols == 6, "Constructor 2 failed");
		matrix<int> c = matrix<int>();
		Assert(c.nrows == 0 && c.ncols == 0, "Constructor 3 failed");
		matrix<int> d = c;
		Assert(d.nrows == 0 && d.ncols == 0, "Constructor 4 failed");

		matrix<int> a2 = matrix<int>(4, 3, true);
		Assert(a2.nrows == 4 && a2.ncols == 3, "Constructor 1 failed");
		matrix<int> b2;
		b2 = matrix<int>(5, 6, true);
		Assert(b2.nrows == 5 && b2.ncols == 6, "Constructor 2 failed");

		double* e = new double[8];
		for (int i = 0; i < 8; i++)
			e[i] = static_cast<double>(i*2);
		double f[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

		matrix<double> g = matrix<double>(4, 2, e);
		matrix<double> g2 = matrix<double>(4, 2, e, true);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Assert(g(i, j) == e[j*4+i], "Constructor 5 failed");
				Assert(g2(i, j) == e[i*2 + j], "Constructor 5 failed");
			}
		}

		matrix<double> h = matrix<double>(3, 2, f);
		matrix<double> h2 = matrix<double>(3, 2, f, true);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Assert(h(i, j) == f[j*3 + i], "Constructor 6 failed");
				Assert(h2(i, j) == f[i*2 + j], "Constructor 6 failed");
			}
		}

		matrix<double> k = h;
		matrix<double> k2 = h2;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Assert(k(i, j) == f[j*3+i], "Constructor 7 failed");
				Assert(k2(i, j) == f[i*2+j], "Constructor 7 failed");
			}
		}

		matrix<unsigned int> * m = new matrix<unsigned int>(1, 10);
		Assert(m->nrows == 1 && m->ncols == 10, "Constructor 8 failed");
	}

	void simpleMatrixTest::testAssignment()
	{
		matrix<int> a = matrix<int>(2,3);
		a(1,1) = 5;
		matrix<int> b = matrix<int>(4,5);
		b(2,2) = 8;
		a = b;
		Assert(a.nrows == 4 && a.ncols == 5, "Assignment Test 1 failed");
		Assert(a(2,2) == 8, "Assignment Test 2 failed");

		matrix<int> a2 = matrix<int>(2,3, true);
		a2(1,1) = 5;
		matrix<int> b2 = matrix<int>(4,5,true);
		b2(2,2) = 8;
		a2 = b2;
		Assert(a2.nrows == 4 && a2.ncols == 5, "Assignment Test 1 failed");
		Assert(a2(2,2) == 8, "Assignment Test 2 failed");
	}

	void simpleMatrixTest::testElementAssignment()
	{
		matrix<int> a = matrix<int>(2,3);
		a(0,0) = 5;
		Assert(a(0,0) == 5, "Element Assignment Test 1 failed");
		a(0,1) = a(0,0);
		Assert(a(0,1) == 5, "Element Assignment Test 2 failed");
		a(0,0) = a(0,1) = a(1,0) = a(1,2) = 7;
		Assert(a(0,0) == 7 && a(1,2) == 7, "Element Assignment Test 3 failed");

		matrix<int> a2 = matrix<int>(2,3,true);
		a2(0,0) = 5;
		Assert(a2(0,0) == 5, "Element Assignment Test 1 failed");
		a2(0,1) = a2(0,0);
		Assert(a2(0,1) == 5, "Element Assignment Test 2 failed");
		a2(0,0) = a2(0,1) = a2(1,0) = a2(1,2) = 7;
		Assert(a2(0,0) == 7 && a2(1,2) == 7, "Element Assignment Test 3 failed");
	}
	
	void simpleMatrixTest::testElementExtraction()
	{
		double f[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
		matrix<double> h = matrix<double>(3, 2, f);
		Assert(h(0,0) == 1.0, "Element Extraction Test 1 failed");
		Assert(h(1,0)*3.0 == 6.0, "Element Extraction Test 2 failed");

		matrix<double> h2 = matrix<double>(3, 2, f, true);
		Assert(h2(0,0) == 1.0, "Element Extraction Test 1 failed");
		Assert(h2(1,0)*3.0 == 9.0, "Element Extraction Test 2 failed");
	}

	void simpleMatrixTest::testTranspose()
	{
		double f[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
		matrix<double> h = matrix<double>(3, 2, f);
		h.transpose();
		Assert(h.nrows == 2 && h.ncols == 3, "Transpose Test 1 failed");
		Assert(h(0,0) == 1.0 && h(1,2) == 6.0, "Transpose Test 2 failed");

		matrix<double> h2 = matrix<double>(3, 2, f);
		h2.transpose();
		Assert(h.nrows == 2 && h.ncols == 3, "Transpose Test 1 failed");
		Assert(h(0,0) == 1.0 && h(1,2) == 6.0, "Transpose Test 2 failed");
	}

/***********************************************/

	void simpleMatrixTest::testUnsafeConstructor()
	{
		matrix_unsafe<int> c = matrix_unsafe<int>();
		Assert(c.nrows == 0 && c.ncols == 0, "Unsafe Constructor 3 failed");
		matrix_unsafe<int> d = c;
		Assert(d.nrows == 0 && d.ncols == 0, "Unsafe Constructor 4 failed");

		double* e = new double[8];
		for (int i = 0; i < 8; i++)
			e[i] = static_cast<double>(i*2);
		double f[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

		matrix_unsafe<double> g = matrix_unsafe<double>(4, 2, e);
		matrix_unsafe<double> g2 = matrix_unsafe<double>(4, 2, e, true);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Assert(g(i, j) == e[j*4+i], "Unsafe Constructor 5 failed");
				Assert(g2(i, j) == e[i*2+j], "Unsafe Constructor 5 failed");
			}
		}

		matrix_unsafe<double> h = matrix_unsafe<double>(3, 2, f);
		matrix_unsafe<double> h2 = matrix_unsafe<double>(3, 2, f, true);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Assert(h(i, j) == f[j*3+i], "Unsafe Constructor 6 failed");
				Assert(h2(i, j) == f[i*2+j], "Unsafe Constructor 6 failed");
			}
		}

		matrix_unsafe<double> k = h;
		matrix_unsafe<double> k2 = h2;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Assert(k(i, j) == f[j*3+i], "Unsafe Constructor 7 failed");
				Assert(k2(i, j) == f[i*2+j], "Unsafe Constructor 7 failed");
			}
		}
		
		int w[3] = {1,2,3};
		matrix_unsafe<int> z = matrix_unsafe<int>(1,3,w);
		Assert(z(0,0) == w[0], "Unsafe Constructor 8 failed");
		Assert(z(0,1) == w[1], "Unsafe Constructor 8 failed");
		Assert(z(0,2) == w[2], "Unsafe Constructor 8 failed");
	}

	void simpleMatrixTest::testUnsafeAssignment()
	{
		double f[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
		matrix_unsafe<double> a = matrix_unsafe<double>(2,3,f);
		a(1,1) = 5.0;
		matrix_unsafe<double> b = matrix_unsafe<double>(1,6,f);
		b(0,2) = 8.0;
		a = b;
		Assert(a.nrows == 1 && a.ncols == 6, "Unsafe Assignment Test 1 failed");
		Assert(a(0,0) == 1.0, "Unsafe Assignment Test 2 failed");
		Assert(a(0,1) == 2.0, "Unsafe Assignment Test 2 failed");
		Assert(a(0,2) == 8.0, "Unsafe Assignment Test 2 failed");
		Assert(a(0,3) == 5.0, "Unsafe Assignment Test 2 failed");
		Assert(a(0,4) == 5.0, "Unsafe Assignment Test 2 failed");
		Assert(a(0,5) == 6.0, "Unsafe Assignment Test 2 failed");
	}

	void simpleMatrixTest::testUnsafeElementAssignment()
	{
		double f[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
		matrix_unsafe<double> a = matrix_unsafe<double>(2,3,f);
		a(0,0) = 5.0;
		Assert(a(0,0) == 5.0, "Unsafe Element Assignment Test 1 failed");
		Assert(f[0] == 5.0, "Unsafe Element Assignment Test 1 failed");
		a(0,1) = a(0,0);
		Assert(a(0,1) == 5.0, "Unsafe Element Assignment Test 2 failed");
		Assert(f[2] == 5.0, "Unsafe Element Assignment Test 2 failed");
		a(0,0) = a(0,1) = a(1,0) = a(1,2) = 7;
		Assert(a(0,0) == 7 && a(1,2) == 7, "Unsafe Element Assignment Test 3 failed");
		Assert(f[0] == 7 && f[5] == 7, "Unsafe Element Assignment Test 3 failed");
	}
	
	void simpleMatrixTest::testUnsafeElementExtraction()
	{
		double f[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
		matrix_unsafe<double> h = matrix_unsafe<double>(3, 2, f);
		Assert(h(0,0) == 1.0, "Unsafe Element Extraction Test 1 failed");
		Assert(f[0] == 1.0, "Unsafe Element Extraction Test 1 failed");
		Assert(h(1,0)*3.0 == 6.0, "Unsafe Element Extraction Test 2 failed");
		Assert(f[1]*3.0 == 6.0, "Unsafe Element Extraction Test 2 failed");
	}
}

