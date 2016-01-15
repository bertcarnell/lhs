/*
 *
 * defines.h: A C++ header used in the LHS package
 * Copyright (C) 2012  Robert Carnell
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef DEFINES
#define DEFINES

#include <cstdlib>
#include <cmath>
#include <exception>
#include <vector>
#include <algorithm>
#include <functional>
#include <cfloat>
#include <climits>
/* VISUAL_STUDIO is defined as a preprocessor directive in the Visual Studio build */
/* in visual studio, the following warnings are disabled
 * 4514 "unreferenced inline function has been removed"
 * 4820 "2 bytes padding added after data member"
 * 4710 "function not inlined"
 */
#ifndef VISUAL_STUDIO
#include "R.h"
#include "Rmath.h"
#else
#include <cstdio>
#ifndef MATHLIB_STANDALONE
#define MATHLIB_STANDALONE
#include "Rmath.h"
#endif
#endif
#include "simpleMatrix.h"

#define PRINT_RESULT 0

#ifndef VISUAL_STUDIO
#define PRINT_MACRO Rprintf
#define ERROR_MACRO error
#else
#define PRINT_MACRO printf
#define ERROR_MACRO printf
#endif

/* include after PRINT_MACRO is defined */
#include "utilityLHS_R.h"

extern "C" {
	void improvedLHS_C(int* N, int* K, int* DUP, int* result);
	void maximinLHS_C(int* N, int* K, int* DUP, int* result);
	void optimumLHS_C(int* N, int* K, int* MAXSWEEPS, double* EPS, int* pOld, int* JLen, int* bVerbose);
	void optSeededLHS_C(int* N, int* K, int* MAXSWEEPS, double* EPS, double* pOld, int* JLen, int* bVerbose);
}

#endif
