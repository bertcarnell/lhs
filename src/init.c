#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP create_oalhs(SEXP, SEXP, SEXP, SEXP);
extern SEXP geneticLHS_cpp(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP improvedLHS_cpp(SEXP, SEXP, SEXP);
extern SEXP maximinLHS_cpp(SEXP, SEXP, SEXP);
extern SEXP oa_to_lhs(SEXP, SEXP, SEXP, SEXP);
extern SEXP oa_type1(SEXP, SEXP, SEXP, SEXP);
extern SEXP oa_type2(SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP optimumLHS_cpp(SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP optSeededLHS_cpp(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP randomLHS_cpp(SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"create_oalhs",     (DL_FUNC) &create_oalhs,     4},
    {"geneticLHS_cpp",   (DL_FUNC) &geneticLHS_cpp,   7},
    {"improvedLHS_cpp",  (DL_FUNC) &improvedLHS_cpp,  3},
    {"maximinLHS_cpp",   (DL_FUNC) &maximinLHS_cpp,   3},
    {"oa_to_lhs",        (DL_FUNC) &oa_to_lhs,        4},
    {"oa_type1",         (DL_FUNC) &oa_type1,         4},
    {"oa_type2",         (DL_FUNC) &oa_type2,         5},
    {"optimumLHS_cpp",   (DL_FUNC) &optimumLHS_cpp,   5},
    {"optSeededLHS_cpp", (DL_FUNC) &optSeededLHS_cpp, 6},
    {"randomLHS_cpp",    (DL_FUNC) &randomLHS_cpp,    3},
    {NULL, NULL, 0}
};

void R_init_lhs(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
