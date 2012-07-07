#include "optSeededLHS_RTest.h"

namespace lhsTest{
	void optSeededLHS_RTest::Run()
	{
		printf("\toptSeededLHS_RTest...");
		testOptSeededLHS_R();
		testStress();
		printf("passed\n");
	}

	void optSeededLHS_RTest::testOptSeededLHS_R()
	{
		// start with input since it normally goes through the augment function
		double pOld[27] = {0.17522671, 0.07879704, 0.17583135, 0.91942996, 0.60287303, 0.87979332, 0.49834531,
			0.83027432, 0.60226876, 0.64048859, 0.40853803, 0.32700602, 0.83442996, 0.90739188,
			0.96706112, 0.35671102, 0.24239675, 0.37670171, 0.23648741, 0.48285498, 0.06292809,
			0.10114126, 0.20412818, 0.49293670, 0.73194844, 0.72583449, 0.68952544};
		int n = 9;
		int k = 3;
		int maxSweeps = 2;
		double eps = 0.1;
		double * pNew = new double[n*k];
		int jLen = 9 * 8 / 2 + 1; // 9 choose 2 + 1
		double * J1 = new double[jLen];
		int * J2 = new int[jLen];
		int * J3 = new int[jLen];
		int iVerbose = 0;

		set_seed(1976, 1968);

		optSeededLHS_C(&n, &k, &maxSweeps, &eps, pOld, &jLen, &iVerbose);
		int * result = new int[n*k];
		for (int i = 0; i < n*k; i++)
		{
			result[i] = static_cast<int>(std::floor(9*pOld[i])+1);
		}
		int expected[27] = {7,9,5,8,6,4,3,1,2,
			1,7,8,4,3,9,5,2,6,
			3,6,8,2,9,4,1,5,7};

		// transpose to compare
		for (int i = 0; i < k; i++) // columns
		{
			for (int j = 0; j < n; j++) // rows
			{
				Assert(expected[i*n+j] == result[j*k+i], "Failed 1");
			}
		}
	}


/*
require(lhs)

RNGkind("Marsaglia-Multicarry")
RNGkind()
.Random.seed

optSeededLHS <- function (seed, m = 1, maxSweeps = 2, eps = 0.1) 
{
  if (is.matrix(seed) == FALSE) 
    stop("Input seed Design must be in the Matrix class\n")
  if (length(m) != 1 | length(maxSweeps) != 1 | length(eps) != 
    1) 
    stop("m, eps, and maxSweeps may not be vectors")
  if (any(is.na(c(m, maxSweeps, eps)))) 
    stop("m, eps, and maxSweeps may not be NA or NaN")
  if (any(is.infinite(c(m, eps, maxSweeps)))) 
    stop("m, eps, and maxSweeps may not be infinite")
  if (eps >= 1 | eps <= 0) 
    stop("eps must fall in the interval (0,1)\n")
  if (floor(maxSweeps) != maxSweeps | maxSweeps < 1) 
    stop("maxSweeps must be a positive integer\n")
  if (floor(m) != m | m < 1) 
    stop("m must be a positive integer\n")
  if (try(is.function(augmentLHS), silent = TRUE) != TRUE) 
    stop("The augmentLHS.R function must be sourced\n")
  if (any(is.na(seed) == TRUE)) 
    stop("Input Design cannot contain any NA entries\n")
  if (max(seed) > 1 | min(seed) < 0) 
    stop("The seed design must be uniformly distributed on [0,1]\n")
  k <- ncol(seed)
  N <- m + nrow(seed)
  Pold <- augmentLHS(seed, m)
  if (m == 1) 
    return(Pold)
  Pold <- c(t(Pold))
  jLen <- choose(N, 2) + 1
  J1 <- numeric(jLen)
  J2 <- numeric(jLen)
  J3 <- numeric(jLen)
  Pnew <- numeric(N * k)
  print(Pold)
  resultList <- .C("optSeededLHS_C", as.integer(N), as.integer(k), 
                   as.integer(maxSweeps), as.double(eps), as.double(Pold), 
                   as.double(J1), as.integer(J2), as.integer(J3), as.integer(jLen), 
                   as.double(Pnew))
  result <- resultList[[5]]
  return(matrix(result, nrow = N, ncol = k, byrow = TRUE))
}

.Random.seed <- as.integer(c(401, 1976, 1968))
.Random.seed
lhsseed <- improvedLHS(4, 3, 5)
floor((4+5)*optSeededLHS(lhsseed, 5, 2, 0.1))+1
.Random.seed
*/
	void optSeededLHS_RTest::testStress()
	{
		double pOld[27] = {0.17522671, 0.07879704, 0.17583135, 0.91942996, 0.60287303, 0.87979332, 0.49834531,
			0.83027432, 0.60226876, 0.64048859, 0.40853803, 0.32700602, 0.83442996, 0.90739188,
			0.96706112, 0.35671102, 0.24239675, 0.37670171, 0.23648741, 0.48285498, 0.06292809,
			0.10114126, 0.20412818, 0.49293670, 0.73194844, 0.72583449, 0.68952544};
		int n = 9;
		int k = 3;
		int maxSweeps = 2;
		double eps = 0.1;
		double * pNew = new double[n*k];
		int jLen = 9 * 8 / 2 + 1; // 9 choose 2 + 1
		double * J1 = new double[jLen];
		int * J2 = new int[jLen];
		int * J3 = new int[jLen];
		int iVerbose = 0;

		set_seed(1976, 1968);

		for (int i = 0; i < 10000; i++)
			optSeededLHS_C(&n, &k, &maxSweeps, &eps, pOld, &jLen, &iVerbose);
	}
}