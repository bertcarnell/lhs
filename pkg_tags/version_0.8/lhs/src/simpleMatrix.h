/*
 *
 * simpleMatrix.h: A C++ header for a matrix class
 *                  used in the LHS package
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

#pragma once

#ifdef VISUAL_STUDIO
// in visual studio debugging, use assert
#ifdef _DEBUG
#else
#ifndef NDEBUG
#define NDEBUG
#endif
#endif
#else
// in anyother implementation, exclude asserts
#ifndef NDEBUG
#define NDEBUG
#endif
#endif

#include <vector>
#include <cassert>

#define ASSERT(x,y) \
	assert(x >= 0 && x < nrows); \
	assert(y >= 0 && y < ncols);

template<class T> class matrix 
{
public:
	size_t nrows;
	size_t ncols;
	std::vector<T> values;

	matrix();
	matrix(size_t rows, size_t cols, bool byRow=false);
	matrix(int rows, int cols, bool byRow=false);
	matrix(size_t rows, size_t cols, const T* m, bool byRow=false);
	matrix(int rows, int cols, const T* m, bool byRow=false);
	matrix(const matrix<T>& mat);
    ~matrix();
	
	matrix<T>& operator=(const matrix<T>& mat);

	T & operator()(size_t i, size_t j);
	T operator()(size_t i, size_t j) const;
	T & operator()(int i, int j);
	T operator()(int i, int j) const;
    
	void transpose();
private:
	void matrix_init(size_t rows, size_t cols, bool byRow);
	void matrix_init(size_t rows, size_t cols, const T* m, bool byRow);
	bool isByRow;
};

template<class T> class matrix_unsafe
{
public:
	size_t nrows;
	size_t ncols;
	T* values;

	matrix_unsafe();
	matrix_unsafe(size_t rows, size_t cols, T* m, bool byRow=false);
	matrix_unsafe(int rows, int cols, T* m, bool byRow=false);
    ~matrix_unsafe();
	
	T & operator()(size_t i, size_t j);
	T operator()(size_t i, size_t j) const;
	T & operator()(int i, int j);
	T operator()(int i, int j) const;
private:
	void matrix_unsafe_init(size_t rows, size_t cols, T* m, bool byRow);
	bool isByRow;
};

/***********************************************/

template<class T>
inline
T & matrix<T>::operator()(size_t i, size_t j)
{
	ASSERT(i,j)
	if (!isByRow) // most often this choice
		return values[j*nrows + i];
	else
		return values[i*ncols + j];
}

template<class T>
inline
T & matrix<T>::operator()(int i, int j)
{
	ASSERT(static_cast<size_t>(i),static_cast<size_t>(j))
	if (!isByRow) // most often this choice
		return values[static_cast<size_t>(j*nrows + i)];
	else
		return values[static_cast<size_t>(i*ncols + j)];
}

template<class T>
inline
T matrix<T>::operator()(size_t i, size_t j) const
{
	ASSERT(i,j)
	if (!isByRow)
		return values[j*nrows + i];
	else
		return values[i*ncols + j];
}

template<class T>
inline
T matrix<T>::operator()(int i, int j) const
{
	ASSERT(i,j)
	if (!isByRow)
		return values[static_cast<size_t>(j*nrows + i)];
	else
		return values[static_cast<size_t>(i*ncols + j)];
}

template<class T>
inline
matrix<T>& matrix<T>::operator=(const matrix<T>& mat)
{
	nrows = mat.nrows;
	ncols = mat.ncols;
	isByRow = mat.isByRow;
	values.resize(nrows*ncols);
	for (size_t i = 0; i < values.size(); i++)
		values[i] = mat.values[i];
	return *this;
}

template<class T>
void matrix<T>::matrix_init(size_t rows, size_t cols, const T* m, bool byRow)
{
	assert(rows > 0 && cols > 0);
	nrows = rows;
	ncols = cols;
	isByRow = byRow;
	values = std::vector<T>(rows*cols);
	for(size_t i = 0; i < rows*cols; i++)
		values[i] = m[i];
}

template<class T>
matrix<T>::matrix(size_t rows, size_t cols, const T* m, bool byRow)
{
	matrix_init(rows, cols, m, byRow);
}

template<class T>
matrix<T>::matrix(int rows, int cols, const T* m, bool byRow)
{
	matrix_init(static_cast<size_t>(rows), static_cast<size_t>(cols), m, byRow);
}

template<class T>
void matrix<T>::matrix_init(size_t rows, size_t cols, bool byRow)
{
	assert(rows > 0 && cols > 0);
	nrows = rows;
	ncols = cols;
	isByRow = byRow;
	values = std::vector<T>(rows*cols);
}

template<class T>
matrix<T>::matrix(size_t rows, size_t cols, bool byRow)
{
	matrix_init(rows, cols, byRow);
}

template<class T>
matrix<T>::matrix(int rows, int cols, bool byRow)
{
	matrix_init(static_cast<size_t>(rows), static_cast<size_t>(cols), byRow);
}

template<class T>
matrix<T>::matrix(const matrix<T> & mat)
{
	nrows = mat.nrows;
	ncols = mat.ncols;
	isByRow = mat.isByRow;
	values = std::vector<T>(nrows*ncols);
	for (size_t i = 0; i < nrows; i++)
	{
		for (size_t j = 0; j < ncols; j++)
		{
			if (!isByRow) // default option
				values[j*nrows + i] = mat(i, j);
			else
				values[i*ncols + j] = mat(i, j);
		}
	}
}

template<class T>
matrix<T>::matrix()
{
	nrows = 0;
	ncols = 0;
	isByRow = false;
	values = std::vector<T>();
}

template<class T>
void matrix<T>::transpose()
{
	std::vector<T> temp = std::vector<T>(nrows*ncols);
	size_t newrows = ncols;
	size_t newcols = nrows;
	for (size_t i = 0; i < nrows; i++)
	{
		for (size_t j = 0; j < ncols; j++)
		{
			if (!isByRow) // most likely
				temp[i*ncols + j] = values[j*nrows + i];
			else
				temp[j*nrows + i] = values[i*ncols + j];
		}
	}
	ncols = newcols;
	nrows = newrows;
	values = temp;
}

template<class T>
matrix<T>::~matrix()
{
}

/***************************************************/

template<class T>
inline
T & matrix_unsafe<T>::operator()(int i, int j)
{
	ASSERT(static_cast<size_t>(i),static_cast<size_t>(j))
	if (!isByRow)
		return values[j*nrows + i];
	else
		return values[i*ncols + j];
}

template<class T>
inline
T matrix_unsafe<T>::operator()(int i, int j) const
{
	ASSERT(i,j)
	if (!isByRow)
		return values[j*nrows + i];
	else
		return values[i*ncols + j];
}

template<class T>
inline
T & matrix_unsafe<T>::operator()(size_t i, size_t j)
{
	ASSERT(i,j)
	if (!isByRow)
		return values[j*nrows + i];
	else
		return values[i*ncols + j];
}

template<class T>
inline
T matrix_unsafe<T>::operator()(size_t i, size_t j) const
{
	ASSERT(i,j)
	if (!isByRow)
		return values[j*nrows + i];
	else
		return values[i*ncols + j];
}

template<class T>
void matrix_unsafe<T>::matrix_unsafe_init(size_t rows, size_t cols, T* m, bool byRow)
{
	assert(rows > 0 && cols > 0);
	nrows = rows;
	ncols = cols;
	isByRow = byRow;
	values = m;
}

template<class T>
matrix_unsafe<T>::matrix_unsafe(int rows, int cols, T* m, bool byRow)
{
	matrix_unsafe_init(static_cast<size_t>(rows), static_cast<size_t>(cols), m, byRow);
}

template<class T>
matrix_unsafe<T>::matrix_unsafe(size_t rows, size_t cols, T* m, bool byRow)
{
	matrix_unsafe_init(rows, cols, m, byRow);
}

template<class T>
matrix_unsafe<T>::matrix_unsafe()
{
	nrows = 0;
	ncols = 0;
	isByRow = false;
	values = 0;
}

template<class T>
matrix_unsafe<T>::~matrix_unsafe()
{
	// release the pointer, but do not delete
	values = 0;
}
