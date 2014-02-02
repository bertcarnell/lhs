/**
 * @file matrix.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
 * 
 * @license <a href="http://www.gnu.org/licenses/lgpl.html">GNU Lesser General Public License (LGPL v3)</a>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MATRIX_H
#define	MATRIX_H

#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>

/**
 * @namespace The bertcarnell template library namespace
 */
namespace bclib {

/**
 * Matrix Class
 * @tparam a generic type of the kind that can be used in std::vector
 */
template<class T>
class matrix 
{
   public:
      /**
       * Define the size_type the same as it is defined for std::vector
       */
      typedef typename std::vector<T>::size_type size_type;
   private:
      size_type rows;  /**< number of rows */
      size_type cols;  /**< number of columns */
      std::vector<T> elements; /**< array of elements */
      bool bTranspose; /**< is the matrix transposed from creation */
      size_type calcLocation(const size_type row, const size_type col)
      {
          return (!bTranspose) ? (row*cols + col) : (col*rows + row);
      }
      size_type calcLocation(const size_type row, const size_type col) const
      {
          return (!bTranspose) ? (row*cols + col) : (col*rows + row);
      }
   public:
       /**
        * row size
        * @return the number of rows in the matrix
        */
       size_type rowsize() const 
       {
           return rows;
       }
       /**
        * column size
        * @return the number of columns in the matrix
        */
       size_type colsize() const 
       {
           return cols;
       }
      
      /**
       * matrix element access
       * @note does not check for index in range
       * @param row row index (zero based)
       * @param col column index (zero based)
       * @return a reference to the requested element
       */
      T& operator()(size_type row, size_type col) 
      {
          return elements[calcLocation(row, col)];
      }
      /**
       * matrix element access
       * @note does not check for arguments out of range
       * @param row row index (zero based)
       * @param col column index (zero based)
       * @return a const reference to the requested element
       */
      const T& operator()(size_type row, size_type col) const 
      {
         return elements[calcLocation(row, col)];
      }
      /**
       * matrix element access
       * @throws std::out_of_range from the internal std::vector
       * @param row row index (zero based)
       * @param col column index (zero based)
       * @return a const reference to the requested element
       */
      const T& at(size_type row, size_type col) const 
      {
         return elements.at(calcLocation(row, col));
      }
      /**
       * matrix element access
       * @throws std::out_of_range from the internal std::vector
       * @param row row index (zero based)
       * @param col column index (zero based)
       * @return a reference to the requested element
       */
      T& at(size_type row, size_type col) 
      {
         return elements.at(calcLocation(row,col));
      }
      /**
       * matrix element access
       * @throws std::out_of_range from the internal std::vector
       * @param i vector index (zero based)
       * @return a reference to the requested element
       */
      T& at(size_type loc)
      {
          return elements.at(loc);
      }
      /**
       * matrix element access
       * @throws std::out_of_range from the internal std::vector
       * @param i vector index (zero based)
       * @return const a reference to the requested element
       */
      const T& at(size_type loc) const
      {
          return elements.at(loc);
      }
      /**
       * a pointer to the internal data array
       * @return a pointer
       */
      T* data()
      {
          return elements.data();
      }
      /**
       * Get the data vector
       * @return 
       */
      std::vector<T> getDataVector() const
      {
          return elements;
      }
      /**
       * Default Constructor with zero rows and zero columns
       */
      matrix();
      /**
       * Constructor
       * @param rows the number of rows in the matrix
       * @param cols the number of columns in the matrix
       */
      matrix(size_type rows, size_type cols);
      /**
       * Constructor
       * @param rows the number of rows in the matrix
       * @param cols the number of columns in the matrix
       * @param elementArray an array to use as the initial values
       */
      matrix(size_type rows, size_type cols, const T* elementArray);
      /**
       * Constructor
       * @param rows the number of rows in the matrix
       * @param cols the number of columns in the matrix
       * @param elementVector a std::vector to use as the initial values
       */
      matrix(size_type rows, size_type cols, const std::vector<T> & elementVector);
      /**
       * Copy Constructor
       * @param the matrix to be copied
       */
      matrix(const matrix<T> &);
      /**
       * Destructor
       */
      ~matrix();

      /**
       * Matrix assignment
       * @param right hand side matrix
       * @return the left hand side matrix
       */
      matrix<T>& operator=( const matrix<T>& );

      /**
       * Equality comparison operator
       * @param the right hand side matrix
       * @return true if the matrices are equivalent
       */
      bool operator==( const matrix<T> &) const;

      /**
       * Get a row of the matrix as a std::vector
       * @note does not check to ensure the row is in range
       * @param row the row number
       * @return a vector representation of that row
       */
      std::vector<T> getrow(size_type row) const;
      /**
       * Get a row of the matrix as a std::vector
       * @throws std::out_of_range when the row is not in range
       * @param row the row number
       * @return a vector representation of that row
       */
      std::vector<T> getrow_at(size_type row) const;
      /**
       * Get a row of the matrix as a row matrix
       * @note does not check to ensure argument is in range
       * @param row the row number
       * @return a matrix representation of that row
       */
      matrix<T> getRowMatrix(size_type row) const;
      /**
       * Get a row of the matrix as a row matrix
       * @throws an out of range exception for an argument out of range
       * @param row the row number
       * @return a matrix representation of that row
       */
      matrix<T> getRowMatrix_at(size_type row) const;

      /**
       * get a column of the matrix as a vector
       * @note does not check the array bounds
       * @param col column number
       * @return a vector of the requested column
       */
      std::vector<T> getcol(size_type col) const;
      /**
       * Get a column of the matrix as a vector
       * @throws out_of_range error if the column requested is out of bounds
       * @param col the column number
       * @return a vector of the requested column
       */
      std::vector<T> getcol_at(size_type col) const;
      /**
       * Get a column of the matrix as a column matrix
       * @note does not check if the requested column is in bounds
       * @param col the column number
       * @return a column matrix of the requested column
       */
      matrix<T> getColumnMatrix(size_type col) const;
      /**
       * Get a column of the matrix as a column matrix
       * @throws if the requested column is out of range
       * @param col the column number
       * @return a column matrix of the requested column
       */
      matrix<T> getColumnMatrix_at(size_type col) const;
      
      /**
       * fill the matrix with a value
       * @param x the value to fill the matrix with
       */
      void fill(const T & x)
      {
          elements.assign(rows*cols, x);
      };

      /**
       * fill the matrix with a value
       * @param x the value to fill the matrix with
       */
      void fill(const T x)
      {
          elements.assign(rows*cols, x);
      };
      
      /**
       * clear the matrix to zero rows and columns
       */
      void clear();

      /**
       * Check if the matrix is empty
       * @return true if the matrix is empty
       */
      bool isEmpty()
      {
          return elements.empty();
      };

      /**
       * change the matrix to a string
       * @return 
       */
      const char* toString();
      
      /**
       * Transpose the matrix
       */
      void transpose();
      
      /**
       * is this matrix operating as a transposed matrix from the original definition
       * @return true if tranposed
       */
      bool isTransposed()
      {
          return bTranspose;
      }
};

template<class T>
matrix<T>::matrix(size_type rows, size_type cols)
  : rows(rows), cols(cols), bTranspose(false)
{
   if ( rows == 0 || cols == 0 )
   {
      throw std::range_error("attempt to create a degenerate matrix");
   }
   elements = std::vector<T>(rows*cols);
}

template<class T>
matrix<T>::matrix(size_type rows, size_type cols, const T* elementArray)
  : rows(rows), cols(cols), bTranspose(false)
{
    if ( rows == 0 || cols == 0 )
    {
       throw std::range_error("attempt to create a degenerate matrix");
    }
    // initialize from array
    elements = std::vector<T>(rows*cols);
   
    for (size_t i = 0; i < rows*cols; i++)
    {
       elements[i] = elementArray[i];
    }
}

template<class T>
matrix<T>::matrix(size_type rows, size_type cols, const std::vector<T> & elementVector)
  : rows(rows), cols(cols), bTranspose(false)
{
    if ( rows == 0 || cols == 0 )
    {
       throw std::range_error("attempt to create a degenerate matrix");
    }
    if (elementVector.size() != rows*cols)
    {
        throw std::range_error("Input element Vector is not the right size");
    }
    elements.assign(elementVector.begin(), elementVector.end());
}

template<class T>
matrix<T>::matrix(const matrix<T> & cp)
  : rows(cp.rows), cols(cp.cols), elements(cp.elements), bTranspose(cp.bTranspose)
{
}

template<class T>
matrix<T>::~matrix()
{
}

template<class T>
matrix<T>& matrix<T>::operator=( const matrix<T>& cp )
{
   if (cp.rows != rows || cp.cols != cols )
   {
       rows = cp.rows;
       cols = cp.cols;
       elements.resize(rows*cols);
   }
   for (size_type i = 0; i < rows*cols; i++)
   {
      elements[i] = cp.elements[i];
   }
   return *this;
}

template<class T>
bool matrix<T>::operator==(const matrix<T>& cp) const
{
    if (cp.rows != rows || cp.cols != cols)
    {
        return false;
    }
    for (size_type i = 0; i < rows*cols; i++)
    {
        if (elements[i] != cp.elements[i])
        {
            return false;
        }
    }
    return true;
}

template<class T>
std::vector<T> matrix<T>::getrow(size_type row) const
{
    std::vector<T> a = std::vector<T>(cols);
    for (size_type j = 0; j < cols; j++)
    {
        a[j] = elements[calcLocation(row, j)];
    }
    return a;
}

template<class T>
std::vector<T> matrix<T>::getrow_at(size_type row) const
{
    if (row >= rows)
    {
        std::ostringstream msg;
        msg << "row " << row << " was requested, but the matrix has " << rows << " rows";
        throw std::out_of_range(msg.str().c_str());
    }
    return getrow(row);
}

template<class T>
matrix<T> matrix<T>::getRowMatrix(size_type row) const
{
    // the simple method has an extra loop of assignment
    //std::vector<T> a = this->getrow(i);
    //return matrix<T>(1,cols,a);
    matrix<T> a(1,cols);
    for (size_type j = 0; j < cols; j++)
    {
        a(0,j) = elements[calcLocation(row, j)];
    }
    return a;
}

template<class T>
matrix<T> matrix<T>::getRowMatrix_at(size_type row) const
{
    if (row >= rows)
    {
        std::ostringstream msg;
        msg << "Row " << row << " was requested, but the matrix has " << rows << " rows";
        throw std::out_of_range(msg.str().c_str());
    }
    return getRowMatrix(row);
}

template<class T>
std::vector<T> matrix<T>::getcol(size_type col) const
{
    std::vector<T> a = std::vector<T>(rows);
    for (size_type i = 0; i < rows; i++)
    {
        a[i] = elements[calcLocation(i, col)];
    }
    return a;
}

template<class T>
std::vector<T> matrix<T>::getcol_at(size_type col) const
{
    if (col >= cols)
    {
        std::ostringstream msg;
        msg << "Column " << col << " was requested, but the matrix has " << cols << " columns";
        throw std::out_of_range(msg.str().c_str());
    }
    return getcol(col);
}

template<class T>
matrix<T> matrix<T>::getColumnMatrix(size_type col) const
{
    matrix<T> a(rows,1);
    for (size_type i = 0; i < rows; i++)
    {
        a(i,0) = elements[calcLocation(i, col)];
    }
    return a;
}

template<class T>
matrix<T> matrix<T>::getColumnMatrix_at(size_type col) const
{
    if (col >= cols)
    {
        std::ostringstream msg;
        msg << "Column " << col << " was requested, but the matrix has " << cols << " columns";
        throw std::out_of_range(msg.str().c_str());
    }
    return getColumnMatrix(col);
}

template<class T>
void matrix<T>::clear()
{
    elements.clear();
    rows = 0;
    cols = 0;
}

template<class T>
matrix<T>::matrix()
{
    rows = 0; 
    cols = 0; 
    elements = std::vector<T>();
}

template<class T>
const char* matrix<T>::toString()
{
    std::ostringstream msg;
    for (size_type irow = 0; irow < rows; irow++)
    {
        for (size_type jcol = 0; jcol < cols; jcol++)
        {
            msg << (*this).at(irow, jcol); 
            if (cols > 1 && jcol < cols - 1)
            {
                msg << ",";
            }
        }
        msg << "\n";
    }
    return msg.str().c_str();
}

template<class T>
void matrix<T>::transpose()
{
    // decide to not move data during transpose
    bTranspose = !bTranspose;
    size_type oldRows = rows;
    rows = cols;
    cols = oldRows;
}

} // end namespace

#endif	/* MATRIX_H */
