#define UNREFERENCED_PARAMETER(P) (P)

extern "C" {
void optimumLHS_C(int* N, int* K, int* MAXSWEEPS, double* EPS, int* pOld,
                  double* J1, int* J2, int* J3, int* jLen, int* pNew);
}

int main (char ** argv, int argc)
{
	UNREFERENCED_PARAMETER(argv);
	UNREFERENCED_PARAMETER(argc);

	int n = 4;
	int k = 3;
	int maxsweeps = 5;
	double eps = 0.05;
	int * pOld = new int[n*k];
	int * pNew = new int[n*k];
	int jlen = 7;  // 7= 4 choose 2 plus 1
	double * j1 = new double[jlen];
	int * j2 = new int[jlen];
	int * j3 = new int[jlen];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < k; j++)
		{
			pOld[i * k + j] = ((i * k + j) % n) + 1;
		}
	}
	//pOld[0] = pOld[3] = pOld[6] = pOld[9] = 1;
	//pOld[1] = pOld[4] = pOld[7] = pOld[10] = 2;
	//pOld[2] = pOld[5] = pOld[8] = pOld[11] = 3;

	optimumLHS_C(&n, &k, &maxsweeps, &eps, pOld, j1, j2, j3, &jlen, pNew);

	return 0;
}
