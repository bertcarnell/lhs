/**
 * @file matrix.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2022, Robert Carnell
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
#include <cstddef>

/**
 * @namespace bclib The bertcarnell template library namespace
 */
namespace bclib {

// forward declare the iterator
template <class T, bool ISROWWISE> class matrixIter;
template <class T, bool ISROWWISE> class matrixConstIter;
    
/**
 * Matrix Class
 * @tparam T a generic type of the kind that can be used in std::vector
 */
template<class T>
class matrix 
{
    friend class matrixIter<T, true>; /**< make the class a friend of the row-wise iterator */
    friend class matrixIter<T, false>; /**< make the class a friend of the column-wise iterator */
    friend class matrixConstIter<T, true>; /**< make the class a friend of the row-wise iterator */
    friend class matrixConstIter<T, false>; /**< make the class a friend of the column-wise iterator */
public:
    typedef typename std::vector<T>::size_type size_type; /**< define the size_type as std::vector */
    typedef typename std::vector<T>::iterator iterator; /**< define iterator from the std::vector internals */
    typedef typename std::vector<T>::const_iterator const_iterator; /**< define the const iterator from the std::vector */
    typedef matrixIter<T, true> rowwise_iterator; /**< an iterator that iterates across rows then down columns */
    typedef matrixIter<T, false> columnwise_iterator; /**< an iterator that iterates down columns then across rows */
    typedef matrixConstIter<T, true> const_rowwise_iterator; /**< a const row-wise iterator */
    typedef matrixConstIter<T, false> const_columnwise_iterator; /**< a const column-wise iterator */
    typedef ptrdiff_t difference_type; /**< define difference_type for consistency with stdlib */
    typedef T value_type; /**< define value_type for consistency with stdlib */
    typedef T * pointer; /**< define a pointer type for consistency with stdlib */
    typedef T & reference; /**< define a reference type for consistency with stdlib */
      
private:
      size_type rows;  /**< number of rows */
      size_type cols;  /**< number of columns */
      std::vector<T> elements; /**< array of elements */
      bool bTranspose; /**< is the matrix transposed from creation */

      /**
       * calculate tne location of the value in the vector holding the matrix values
       * @param row the row location
       * @param col the column location
       * @return the location of the value in the vector holding the matrix values
       */
      size_type calcLocation(const size_type row, const size_type col)
      {
          return (!bTranspose) ? (row*cols + col) : (col*rows + row);
      }
      
      /**
       * calculate tne location of the value in the vector holding the matrix values
       * @param row the row location
       * @param col the column location
       * @return the location fo the value in the vector holding the matrix values
       */
      size_type calcLocation(const size_type row, const size_type col) const
      {
          return (!bTranspose) ? (row*cols + col) : (col*rows + row);
      }
   public:
       /// The number of rows in the matrix
       size_type rowsize() const {return rows;};
       
       /// The number of columns in the matrix 
       size_type colsize() const {return cols;};
      
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
      
      /// a pointer to the internal data array
      T* data() {return elements.data();};
      
      /// get the internal data vector
      std::vector<T> getDataVector() const {return elements;};
      
      /// Default Constructor with zero rows and zero columns 
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
      
      /// Destructor
      ~matrix();

      /**
       * Matrix assignment
       * @param right hand side matrix
       * @return the left hand side matrix
       */
      matrix<T>& operator=( const matrix<T>& );

      /**
       * Equality comparison operator
       * @param rhs the right hand side matrix
       * @return true if the matrices are equivalent
       */
      bool operator==(const matrix<T> & rhs) const;
      
      /**
       * Inequality comparison operator
       * @param rhs the right hand side matrix
       * @return true if the matrices are not equivalent
       */
      bool operator!=(const matrix<T> & rhs) const;

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
      //void fill(const T x)
      //{
      //    elements.assign(rows*cols, x);
      //};
      
      /// Clear the matrix to zero rows and columns
      void clear();

      /// return true if the matrix is empty
      bool isEmpty() const {return elements.empty();};

      /// return a string representation of the matrix
      std::string toString() const;
      
      /// Transpose the matrix
      void transpose();
      
      /// return true if this matrix is operating as a transposed matrix from the original definition
      bool isTransposed() const {return bTranspose;};
      
      /********* Matrix Iterators *********/
      
      /// an iterator for the beginning of the internal vector
      iterator begin() {return elements.begin();};
      const_iterator begin() const {return elements.begin();};

      /// An iterator for one iteration past the end of the internal vector
      iterator end() {return elements.end();};
      const_iterator end() const {return elements.end();};

      /// An iterator that operates along the matrix rows 
      rowwise_iterator rowwisebegin() {return rowwise_iterator(*this, 0, 0);};
      const_rowwise_iterator rowwisebegin() const {return const_rowwise_iterator(*this, 0, 0);};
      
      /**
       * return a row wise iterator for the beginning of the ith row (0 based)
       * @param irow
       */
      rowwise_iterator rowwisebegin(size_type irow) {return rowwise_iterator(*this, irow, 0);};
      const_rowwise_iterator rowwisebegin(size_type irow) const {return const_rowwise_iterator(*this, irow, 0);};
      
      /// An iterator that operates along the matrix row
      rowwise_iterator rowwiseend() {return rowwise_iterator(*this, rows, 0);};
      const_rowwise_iterator rowwiseend() const {return const_rowwise_iterator(*this, rows, 0);};

      /**
       * return a row wise iterator for the end of the ith row (0 based)
       * @param irow
       */
      rowwise_iterator rowwiseend(size_type irow) {return rowwise_iterator(*this, irow+1, 0);};
      const_rowwise_iterator rowwiseend(size_type irow) const {return const_rowwise_iterator(*this, irow+1, 0);};
      
      /// An iterator that operates along the matrix columns
      columnwise_iterator columnwisebegin() {return columnwise_iterator(*this, 0, 0);};
      const_columnwise_iterator columnwisebegin() const {return const_columnwise_iterator(*this, 0, 0);};
      
      /**
       * return a column wise iterator for the beginning of the jth column (0 based)
       * @param irow
       */
      columnwise_iterator columnwisebegin(size_type jcol) {return columnwise_iterator(*this, 0, jcol);};
      const_columnwise_iterator columnwisebegin(size_type jcol) const {return const_columnwise_iterator(*this, 0, jcol);};

      /// An iterator that operates along the matrix columns
      columnwise_iterator columnwiseend() {return columnwise_iterator(*this, 0, cols);};
      const_columnwise_iterator columnwiseend() const {return const_columnwise_iterator(*this, 0, cols);};

      /**
       * return a column wise iterator for the end of the jth column (0 based)
       * @param irow
       */
      columnwise_iterator columnwiseend(size_type jcol) {return columnwise_iterator(*this, 0, jcol+1);};
      const_columnwise_iterator columnwiseend(size_type jcol) const {return const_columnwise_iterator(*this, 0, jcol+1);};
};

/******************************************************************************/

/**
 * An iterator class for the <code>matrix</code> class
 * @tparam T the type of object stored in the matrix
 * @tparam ISROWWISE a boolean to indicate if the matrix is iterated row-wise
 */
template <class T, bool ISROWWISE>
class matrixIter
{
    friend class matrixConstIter<T, ISROWWISE>;
private:
    matrix<T> & myMatrix; /**< The object that the iterator is referencing */
    typename matrix<T>::size_type rows; /**< the row being pointed to */
    typename matrix<T>::size_type cols; /**< the column being pointed to */
public:
	// required elements of an iterator class (inherited from std::iterator before it was deprecated)
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = T;
    using pointer = T*;
    using reference = T&;

    /**
     * Constructor
     * @param mat the matrix being indexed
     * @param r the row location of the iterator
     * @param c the column location of the iterator
     */
    matrixIter(matrix<T> & mat, typename matrix<T>::size_type r, 
            typename matrix<T>::size_type c)
        : myMatrix(mat), rows(r), cols(c) {}
    /// Equality operator
    bool operator==(const matrixIter<T, ISROWWISE> & other) const;
    /// Inequality operator
    bool operator!=(const matrixIter<T, ISROWWISE> & other) const
    {
        return !(*this == other);
    }
    /// pre-increment operator
    matrixIter<T, ISROWWISE> & operator++();
    /// post-increment operator
    matrixIter<T, ISROWWISE> operator++(int);
    /// assignment operator
    matrixIter<T, ISROWWISE> & operator=(const matrixIter<T, ISROWWISE> & rhs);
    /// de-reference operator
    T & operator*() 
    { 
        return myMatrix(rows, cols); 
    }
};

/**
 * An const_iterator class for the <code>matrix</code> class
 * @tparam T the type of object stored in the matrix
 * @tparam ISROWWISE a boolean to indicate if the matrix is iterated row-wise
 */
template <class T, bool ISROWWISE>
class matrixConstIter
{
    friend class matrixIter<T, ISROWWISE>;
private:
    const matrix<T> & myMatrix; /**< The object that the iterator is referencing */
    typename matrix<T>::size_type rows; /**< the row being pointed to */
    typename matrix<T>::size_type cols; /**< the column being pointed to */
public:
	// required elements of an iterator class (inherited from std::iterator before it was deprecated)
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = T;
    using pointer = T*;
    using reference = T&;

    /**
     * Constructor
     * @param mat the matrix being indexed
     * @param r the row location of the iterator
     * @param c the column location of the iterator
     */
    matrixConstIter(const matrix<T> & mat, typename matrix<T>::size_type r, 
            typename matrix<T>::size_type c)
        : myMatrix(mat), rows(r), cols(c) {}
    /**
     * Copy constructor from non-const to const
     * @param mi the matrix being copied
     */
    matrixConstIter(const matrixIter<T, ISROWWISE> & mi)
        : myMatrix(mi.myMatrix), rows(mi.rows), cols(mi.cols){}
    /// Equality operator
    bool operator==(const matrixConstIter<T, ISROWWISE> & other) const;
    /// Inequality operator
    bool operator!=(const matrixConstIter<T, ISROWWISE> & other) const
    {
        return !(*this == other);
    }
    /// pre-increment operator
    matrixConstIter<T, ISROWWISE> & operator++();
    /// post-increment operator
    matrixConstIter<T, ISROWWISE> operator++(int);
    /// Assignment operator
    /** @TODO:  does an assignment operator make sense for a const iterator? */
    matrixConstIter<T, ISROWWISE> & operator=(const matrixConstIter<T, ISROWWISE> & rhs);
    /// de-reference operator
    const T & operator*() 
    { 
        return myMatrix(rows, cols); 
    }
};

// heavily influenced by:  http://www.sj-vs.net/c-implementing-const_iterator-and-non-const-iterator-without-code-duplication/

/******************************************************************************/

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
   }
   elements = cp.elements;
   bTranspose = cp.bTranspose;
   return *this;
}

template<class T>
bool matrix<T>::operator==(const matrix<T>& cp) const
{
    if (cp.rows != rows || cp.cols != cols)
    {
        return false;
    }
    return std::equal(elements.begin(), elements.end(), cp.elements.begin());
}

template<class T>
bool matrix<T>::operator!=(const matrix<T> & cp) const
{
    if (*this == cp)
    {
        return false;
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
    bTranspose = false;
}

template<class T>
matrix<T>::matrix()
{
    rows = 0; 
    cols = 0; 
    elements = std::vector<T>();
    bTranspose = false;
}

template<class T>
std::string matrix<T>::toString() const
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
    return msg.str();
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

/******************************************************************************/

template<class T, bool ISROWWISE>
bool matrixIter<T, ISROWWISE>::operator==(const matrixIter<T, ISROWWISE> & other) const
{
    if (this->myMatrix == other.myMatrix &&
            this->rows == other.rows &&
            this->cols == other.cols)
    {
        return true;
    }
    return false;
}

template<class T, bool ISROWWISE>
matrixIter<T, ISROWWISE> & matrixIter<T, ISROWWISE>::operator++() 
{
    if (ISROWWISE)
    {
        if (cols < myMatrix.cols - 1)
        {
            cols++;
            return *this;
        }
        else
        {
            cols = 0;
            rows++;
            return *this;
        }
    }
    else // ISROWWISE = false
    {
        if (rows < myMatrix.rows - 1)
        {
            rows++;
            return *this;
        }
        else
        {
            rows = 0;
            cols++;
            return *this;
        }
    }
}

template<class T, bool ISROWWISE>
matrixIter<T, ISROWWISE> & matrixIter<T, ISROWWISE>::operator=(const matrixIter<T, ISROWWISE> & rhs)
{
    // Check for self-assignment
    if (this == &rhs)
    {
        return *this;
    }
    else
    {
        this->myMatrix = rhs.myMatrix;
        this->rows = rhs.rows;
        this->cols = rhs.cols;
        return *this;
    }
}

template<class T, bool ISROWWISE>
matrixIter<T, ISROWWISE> matrixIter<T, ISROWWISE>::operator++(int) 
{
    const matrixIter<T, ISROWWISE> clone( *this );
    ++(*this);
    return clone;
}

/******************************************************************************/

template<class T, bool ISROWWISE>
bool matrixConstIter<T, ISROWWISE>::operator==(const matrixConstIter<T, ISROWWISE> & other) const
{
    if (this->myMatrix == other.myMatrix &&
            this->rows == other.rows &&
            this->cols == other.cols)
    {
        return true;
    }
    return false;
}

template<class T, bool ISROWWISE>
matrixConstIter<T, ISROWWISE> & matrixConstIter<T, ISROWWISE>::operator++() 
{
    if (ISROWWISE)
    {
        if (cols < myMatrix.cols - 1)
        {
            cols++;
            return *this;
        }
        else
        {
            cols = 0;
            rows++;
            return *this;
        }
    }
    else // ISROWWISE = false
    {
        if (rows < myMatrix.rows - 1)
        {
            rows++;
            return *this;
        }
        else
        {
            rows = 0;
            cols++;
            return *this;
        }
    }
}

template<class T, bool ISROWWISE>
matrixConstIter<T, ISROWWISE> & matrixConstIter<T, ISROWWISE>::operator=(const matrixConstIter<T, ISROWWISE> & rhs)
{
    // Check for self-assignment
    if (this == &rhs)
    {
        return *this;
    }
    else
    {
        this->myMatrix = rhs.myMatrix;
        this->rows = rhs.rows;
        this->cols = rhs.cols;
        return *this;
    }
}

template<class T, bool ISROWWISE>
matrixConstIter<T, ISROWWISE> matrixConstIter<T, ISROWWISE>::operator++(int) 
{
    const matrixConstIter<T, ISROWWISE> clone( *this );
    ++(*this);
    return clone;
}

} // end namespace

#endif	/* MATRIX_H */
