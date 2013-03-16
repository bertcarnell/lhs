#include <math.h>
#include <Rmath.h>
/* VISUAL_STUDIO is defined as a preprocessor directive in the build */
#ifndef VISUAL_STUDIO
#include <R.h>
#else
#include <stdio.h>
#endif

#define PRINT_RESULT 0

#ifndef VISUAL_STUDIO
#define PRINT_MACRO Rprintf
#define ERROR_MACRO error
#else
#define PRINT_MACRO printf
#define ERROR_MACRO printf
#endif

int lhsCheck(int * N, int * K, int * result, int bTranspose);
void lhsPrint(int * N, int * K, int * result, int bTranspose);
void lhsPrint_double(int * N, int * K, double * result);
double sumInvDistance_double(double * matrix, int * nr, int * nc);
double sumInvDistance_int(int * matrix, int * nr, int * nc);

