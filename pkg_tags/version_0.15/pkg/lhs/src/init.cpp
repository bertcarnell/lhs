/*
 *
 * lhs.c: A C file to hold R interface functions
 * Copyright (C) 2017  Robert Carnell
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

#include "defines.h"

static R_NativePrimitiveArgType improvedLHS_C_t[] = {
	INTSXP, INTSXP, INTSXP, INTSXP
};

static R_NativePrimitiveArgType maximinLHS_C_t[] = {
	INTSXP, INTSXP, INTSXP, INTSXP
};

static R_NativePrimitiveArgType optimumLHS_C_t[] = {
	INTSXP, INTSXP, INTSXP, REALSXP, INTSXP, INTSXP, INTSXP
};

static R_NativePrimitiveArgType optSeededLHS_C_t[] = {
	INTSXP, INTSXP, INTSXP, REALSXP, REALSXP, INTSXP, INTSXP
};

static const R_CMethodDef cMethods[] = {
	{"improvedLHS_C", (DL_FUNC) &improvedLHS_C, 4, improvedLHS_C_t},
	{"maximinLHS_C", (DL_FUNC) &maximinLHS_C, 4, maximinLHS_C_t},
	{"optimumLHS_C", (DL_FUNC) &optimumLHS_C, 7, optimumLHS_C_t},
	{"optSeededLHS_C", (DL_FUNC) &optSeededLHS_C, 7, optSeededLHS_C_t},
	{NULL, NULL, 0, NULL}
};

void R_init_lhs(DllInfo *dll)
{
	R_registerRoutines(dll, cMethods, NULL, NULL, NULL);
	R_useDynamicSymbols(dll, FALSE);
	R_forceSymbols(dll, TRUE);
}

