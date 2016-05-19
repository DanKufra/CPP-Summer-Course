/********************************************************************************
 * @file Matrix.hpp
 * @author  Dan Kufra
 * @version 1.0
 * @date 25.08.2015
 *
 * @brief The SLabCPP Standard Matrix header file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard Matrix header.
 *
 * This header provides a Matrix type with extra capabilities.
 *
 * The header provides the following features:
 *  - basic matrix operations
 *
 * Error handling
 * ~~~~~~~~~~~~~~
 * Throws exceptions when dimensions don't match desired action.
 ********************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <thread>
#include <exception>
#include "BadDimensionException.h"
#include "Complex.h"

/*
 * @def DEF_VALUE
 * @brief Macro represneting starting value of a cell.
 */
#define DEF_VALUE 0

/*
 * @def DEF_SIZE
 * @brief Macro representing starting size of new Matrix array.
 */
#define DEF_SIZE 1

/*
 * @def PAR_MACRO
 * @brief print of the change in Parallel mode
 */
#define PAR_MACRO(val) std :: cout << "Generic Matrix mode changed to " << val << \
" mode." << std :: endl;

/*
 * @def PRINT_TAB
 * @brief Macro representing a tab character
 */
#define PRINT_TAB "\t"

/*
 * @def PRINT_NEW_LINE
 * @brief Macro representing a new line character
 */
#define PRINT_NEW_LINE "\n"

/*
 * @def PARALLEL
 * @brief Macro representing the word parallel
 */
#define PARALLEL "parallel"

/*
 * @def NON_PARALLEL
 * @brief Macro representing the word non-parallel
 */
#define NON_PARALLEL "non-parallel"

/*
 * @def BAD_ALLOC_PRINT
 * @brief print message in case of a bad allocation
 */
#define BAD_ALLOC_PRINT std :: cout << "Bad allocation of Matrix" << std :: endl

/*
 * @def CONSTRUCTOR_MESSAGE
 * @brief print message for wrong dimensions when constructing a matrix
 */
#define CONSTRUCTOR_MESSAGE "Wrong dimensions in constructor."

/*
 * @def OP_MESSAGE
 * @brief print message for wrong dimensions when operating on a matrix
 */
#define OP_MESSAGE "Wrong dimensions for this operator."

#define ADD_WRONG_MESSAGE "cannot addition matrices of different sizes."

/*
 * @def OP_MESSAGE
 * @brief print message for wrong dimensions for trace calculation
 */
#define TRACE_MESSAGE "Matrix is not square, trace cannot be calculated."

/*
 * @def INDEX_MESSAGE
 * @brief print message for trying to reach an out of bound index in the matrix
 */
#define INDEX_MESSAGE "Index chosen is not in matrix bound."

/**
 * @def OFFSET
 * @brief an offset for when we loop through the matrix. Since () operator is 1 based, not zero.
 */
#define OFFSET 1

template <typename T>
class Matrix
{
	
	/**
	 * @brief Overrides << operator for Matrix to print a matrix.
	 * @param stream to write to
	 * @param IntMatrix we wish to print
	 * @return a stream with the matrix representation to print
	 */
	template<typename U>
	friend std::ostream& operator<< (std::ostream& os, const Matrix<U>& ourMatrix);
	
	/**
	 * @brief Deep copy swaps between two matrixes
	 * @param first matrix
	 * @param second matrix
	 */
	template <typename U>
	friend void swap(Matrix<U>& first, Matrix<U>& second);

private:
	

	unsigned int _rowNum; /**< Row Dimension of IntMatrix. */
	unsigned int _colNum; /**< Column Dimension of IntMatrix. */
	std :: vector<T> _matrix; /** vector of T which represents the matrix */
	static bool _parallel; /**<Static variable that holds whether we are running in parallel. */
	
	/**
	 * @brief Setter for the row dimension of IntMatrix
	 * @param new row dimension
	 */
	inline void _setRow(unsigned int rowAmnt)
	{
		_rowNum = rowAmnt;
	}
	
	/**
	 * @brief Setter for the column dimension of IntMatrix
	 * @param new column dimension
	 */
	inline void _setCol(unsigned int colAmnt)
	{
		_colNum = colAmnt;
	}
	
public:
	
    /**
     * @brief A default constructor which receives no values.
     */
	Matrix<T>(): _rowNum(DEF_SIZE), _colNum(DEF_SIZE)
	{
		try
		{
			// intiialize a matrix with default values
			_matrix.push_back(DEF_VALUE);
		}
		catch(std ::bad_alloc &e)
		{
			// The forum reply was inconclusive as to whether to print a message or just throw an exception so I did both
			BAD_ALLOC_PRINT;
			throw;
		}
	}
    
    /**
     * @brief A copy constructor which receives an IntMatrix object and deep copies it.
     * @param An Matrix object to be copied.
     */
	Matrix<T>(const Matrix<T> &copyMatrix) : Matrix<T> (copyMatrix.rows(), 
											 copyMatrix.cols(),
											 copyMatrix._matrix)
	{

	}
	

	/**
	 * @brief A copy constructor which receives an IntMatrix object and deep copies it.
	 * @param An Matrix object to be copied.
	 */
	Matrix<T>(const Matrix<T> && copyMatrix) : _rowNum(copyMatrix.rows()),
											  _colNum(copyMatrix.cols()),
											  _matrix(std :: move(copyMatrix._matrix))
	{
	}
	
    /**
     * @brief A constructor which receives the dimensions of the matrix and an array and creates a
     * new Matrix
     * @param row dimension
     * @param column dimension
     * @param array of ints
     */
	Matrix<T> (unsigned int row, unsigned int col, const std :: vector<T>& cells): _rowNum(row),
																				_colNum(col)
	{
		// if the size does not match the dimension throw an exception, otherwise set vector
		if(row * col != cells.size() || ((!rows())^(!cols())))
		{
			   throw BadDimensionException(CONSTRUCTOR_MESSAGE);
		}
		try 
		{
			// copy each object from the vector into our Matrix's vector
			for(unsigned int i = 0; i < cells.size(); ++i)
			{
				_matrix.push_back(cells[i]);
			}
		}
		catch (std :: bad_alloc &e)
		{
			// The forum reply was inconclusive as to whether to print a message or just throw an exception so I did both
			BAD_ALLOC_PRINT;
			throw;
		}

	}
	
    /**
     * @brief A constructor which receives the dimensions and creates a new empty Matrix
     * @param row dimension
     * @param column dimension
     */
	Matrix<T>(unsigned int rowAmnt, unsigned int colAmnt): _rowNum(rowAmnt), _colNum(colAmnt)
	{
		// if the size does not match the dimension throw an exception, otherwise set vector
		if((!rows())^(!cols()))
		{
			   throw BadDimensionException(CONSTRUCTOR_MESSAGE);
		}
		// set a new vector of proper size full of 0s
		for(unsigned int i = 0; i < rowAmnt; ++i)
		{
			for(unsigned int j = 0; j < colAmnt; ++j)
			{
				_matrix.push_back(T(DEF_VALUE));
			}
		}
	}
	
	
	static void setParallel(bool val)
	{
		// if the value should change
		if(val != _parallel)
		{
			// then change it and print appropriate message
			_parallel = val;
			if(val == true)
			{
				PAR_MACRO(PARALLEL);
			}
			else
			{
				PAR_MACRO(NON_PARALLEL);
			}
		}
	}
	
	/**
	 * @brief Getter for the row dimension of the IntMatrix.
	 * @return Int row dimension
	 */
	inline unsigned int rows() const
	{
		return _rowNum;
	}
	
	/**
	 * @brief Getter for the column dimension of the IntMatrix.
	 * @return Column dimension
	 */
	inline unsigned int cols() const
	{
		return _colNum;
	}
	
	
	/**
	 * @brief Getter for the array of Matrix
	 * @return pointer to the array of the IntMatrix
	 */
	inline std :: vector<T>& getArr() const 
	{
		return _matrix;
	}
	
    
	Matrix<T>& operator=(Matrix<T> other) 
	{
		// use our swap friend function to swap between the matrix values 
		swap(*this, other);
		return *this;
	}

	/**
	 * @brief Static function which receives pointers to three vectors and adds
	 * the rows together.
	 * @param vector of T's we wish to change
	 * @param first vector of T's we are adding together
	 * @param second vector of T's we are adding together
	 * @param length of the row we are adding
	 */
	static void addRows(T *changedArray, const T *firstArray , const T *secondArray, int lengthRow)
	{
		for(int j = 0; j < lengthRow; ++j)
		{
			changedArray[j] = firstArray[j] + secondArray[j];
		}
	}
	
    /**
     * @brief Overrides + operator for Matrix to add a matrix to current matrix.
     * @param Matrix we wish to add to the current matrix.
     * @return a new Matrix we created
     */
    const Matrix<T> operator+(const Matrix<T> &right) const
	{
		if(rows() != right.rows() || cols() != right.cols())
		{
			throw BadDimensionException(ADD_WRONG_MESSAGE);
		}
		// initialize a new Matrix<T> and an empty vector of threads
		Matrix<T> additionMatrix(rows(), cols());
		std :: vector<std :: thread> threadVector;
		// iterate over the matrix by row
		for(unsigned int i = 0; i < rows() ; ++i)
		{
			
			// if our parallel is set to true then open a thread for each row calulation
			if(_parallel)
			{
				// push the thread into a vector to join later
				threadVector.push_back(std :: thread (addRows, &additionMatrix._matrix[i * cols()],
											 &_matrix[i * cols()], &right._matrix[i * cols()] ,
											 cols()));
			}
			else
			{
				// if our parallel is not true then just calculate row by row without threads
				addRows(&additionMatrix._matrix[i * cols()],
						&_matrix[i * cols()], &right._matrix[i * cols()] , cols());

			}
		}

		// go over the threads and  join them when the function ends.
		for(unsigned int i = 0; i < threadVector.size(); ++i)
		{
			threadVector[i].join();
		}
		return additionMatrix;
	}
    
    /**
     * @brief Overrides - operator for Matrix to subtract a matrix from the current matrix.
     * @param Matrix we wish to subtract from the current matrix.
     * @return a new Matrix we created
     */
    const Matrix<T> operator-(const Matrix<T> &right) const
	{
		if(rows() != right.rows() || cols() != right.cols())
		{
			throw BadDimensionException(OP_MESSAGE);
		}
		// create a new matrix and subtract the values of two other vectors and add to ours
		Matrix<T> subtractionMatrix(rows(), cols());
		for(unsigned int i = 0; i < _matrix.size() ; ++i)
		{
			subtractionMatrix._matrix[i] = _matrix[i] + right._matrix[i];
		}
		return subtractionMatrix;
	}
	
	
	/**
	 * @brief Calculates the dot product between a row and column of valid sizes
	 * @param pointer to begining of the row
	 * @param pointer to the begining of the column
	 * @param length of the row
	 * @param length of the column
	 * @return the dot product
	 */
	static T dotProduct(const T *firstArray, const T *secondArray,
						unsigned int lengthRow, unsigned int lengthCol)
	{
		// create a new T object
		T sum = T();
		for(unsigned int i = 0; i < lengthRow; ++i)
		{
			// sum each row into that T object using it's operators
			sum += firstArray[i] * secondArray[i * lengthCol];
		}
		return sum;
	}
	
	
	/**
	 * @brief changes the value of each row in a inputted matrix by multiplying the row 
	 * and column of the other inputted matrices
	 * @param Matrix we wish to change
	 * @param first matrix we are multiplying
	 * @param second matrix we are multiplying
	 * @param the row number
	 */
	static void rowMulti(Matrix<T>& change, const Matrix<T>& first, const Matrix<T>& sec, 
						 unsigned int rowNum)
	{
		// go over all the indexes in the row and call dot product to change them
		for(unsigned int j = 0; j < change.cols(); ++j)
		{
			change._matrix[(rowNum * change.cols()) + j] = dotProduct(
																		 &first._matrix
																		 [rowNum * first.cols()],
																		 &sec._matrix[j],
																		 first.cols(),
																		 sec.cols());
		}
	}
	
    /**
     * @brief Overrides * operator for Matrix to multiply a matrix by current matrix.
     * @param Matrix we wish to multiply by the current matrix.
     * @return a new Matrix we created
     */
    const Matrix<T> operator*(const Matrix<T> &other) const
	{
		if(cols() != other.rows())
		{
			throw BadDimensionException(OP_MESSAGE);
		}
		// initialize and empty matrix of the proper size and a vector of threads
		Matrix<T> tmpMatrix(rows(), other.cols());
		std :: vector<std :: thread> threadVector;
		// initialize each index in that matrix to be the dot product between a row and column
		for (unsigned int i = 0; i < tmpMatrix.rows(); ++i)
		{
			// if it was parallel use seperate threads for each row and put them in our vector
			if (_parallel)
			{
				threadVector.push_back(std::thread(rowMulti, std::ref(tmpMatrix), std::ref (*this), 
									   std::ref (other), i));
			}
			else
			{
				// otherwise just calculate the rows one by one
				rowMulti(tmpMatrix, *this, other, i);
			}
		}
		
		// join all our threads before ending the function
		for(unsigned int i = 0; i < threadVector.size(); ++i)
		{
			threadVector[i].join();
		}
		
		return tmpMatrix;
	}
	
	/**
	 * @brief Overrides == operator for Matrix to check whether a matrix is equal to another
	 * @param Matrix we wish to check equality of
	 * @return true if they are equal, false otherwise
	 */
	bool operator==(const Matrix<T> &right) const
	{
		if(rows() != right.rows() || cols() != right.cols())
		{
			return false;
		}
		// check that each value in the Matrix equals the one in the inputted matrix
		for(unsigned int i = 0; i < _matrix.size() ; ++i)
		{
			if(	_matrix[i] != right._matrix[i])
			{
				return false;
			}

		}
		return true;
	}

	/**
	 * @brief Overrides != operator for Matrix to check whether a matrix is unequal to another
	 * @param Matrix we wish to check equality of
	 * @return true if they are equal, false otherwise
	 */
	bool operator!=(const Matrix<T> &right) const
	{
		// return the negation of our == operator
		return !this == right;
	}
	
	/**
	 * @brief Overrides () operator to get the value in the [row,col] cell for const Matrix
	 * @param row number
	 * @param col number
	 * @return value in the cell
	 */
	T operator()(unsigned int rowPos, unsigned int colPos) const
	{
		if(rows() < rowPos || cols() < colPos)
		{
			throw std :: out_of_range(INDEX_MESSAGE);
		}
		return _matrix[(rowPos - OFFSET) * cols() + colPos - OFFSET];
	}

	/**
	 * @brief Overrides () operator to get the value in the [row,col] cell
	 * @param row number
	 * @param col number
	 * @return value in the cell
	 */
	T& operator()(unsigned int rowPos, unsigned int colPos)
	{
		if(rows() < rowPos || cols() < colPos)
		{
			throw std :: out_of_range(INDEX_MESSAGE);
		}
		return _matrix[(rowPos - OFFSET) * cols() + colPos - OFFSET];
	}
	
	
	/**
	 * @brief Figures out whether a matrixs is square
	 * @returnƒ true if square, false otherwise
	 */
	bool isSquareMatrix() const
	{
		return rows() == cols();
	}
	
    /**
     * @brief Calculates the trace of a matrix and returns it. Assumes it is given a square matrix
     * @return The trace of the matrix.
     */
    
    T trace() const
	{
		if(!isSquareMatrix())
		{
			throw BadDimensionException(TRACE_MESSAGE);
		}
		// go index by index and when the row num equals the col num add that value to the sum
		T sum = T();
		for (unsigned int i = 1; i <= rows(); ++i) 
		{
			for(unsigned int j = 1; j <= cols(); ++j)
			{
				if (j == i)
				{
					sum += (*this)(i, j);
				}
			}
		}
		return sum;
	
	}
	
	
    /**
     * @brief Calculates the transpose of a matrix and returns it.
     * @return The transposed Matrix.
     */
    Matrix<T> trans() const
	{
		// create a copy of our matrix and switch indexes so that it is transposed
		Matrix<T> transMatrix(*this);
		for (unsigned int i = 0; i < rows(); ++i)
		{
			for(unsigned int j = 0; j < cols(); ++j)
			{
				transMatrix._matrix[(j * rows()) + i] = (*this)(i + OFFSET, j + OFFSET);
			}
		}

		// change column and row values
		transMatrix._setRow(cols());
		transMatrix._setCol(rows());
		return transMatrix;
	}
	

    /**
     * @brief Destructor for Matrix
     */
    ~Matrix()
	{
	}
	
	/**
	 * @brief Matrix<T> iterator class which is basically a wrapper for a vector<T> iterator
	 *
	 */
	class const_iterator
	{
	public:

		/**
		 * @brief Default constructor that sets our vector to nullptr
		 */
		const_iterator(): _pointer(nullptr)
		{
		}

		/**
		 * @brief Constructor that sets recieves an iterator on a vector and sets it
		 * @param vector<T> iterator
		 */
		const_iterator(typename std :: vector<T> :: const_iterator def)
		{
			
			_pointer = def;
		}
		
		/**
		 * @brief * operator that derefrences and iterator on our Matrix
		 * @return the T in the iterator at that location
		 */
		const T& operator*() const
		{
			return *_pointer;
		}
		
		/**
		 * @brief [] operator that returns the i element of an iterator
		 * @param int index of our iterator
		 * @return the T in the iterator at that location
		 */
		const T operator[](unsigned int i) const
		{
			return _pointer[i];
		}
		
		/**
		 * @brief ++ operator that moves our iterator forward
		 * @return our iterator
		 */
		const_iterator& operator++()
		{
			_pointer = ++_pointer;
			return *this;
		}
		
		/**
		 * @brief -- operator that moves our iterator backwards
		 * @return our iterator
		 */
		const_iterator& operator--()
		{
			_pointer = --_pointer;
			return *this;
		}
		
		/**
		 * @brief == operator that checks whether our iterator is equal to another
		 * @param an iterator on a matrix
		 * @return our iterator
		 */
		bool operator==(const const_iterator& right) const
		{
			return _pointer == right.getPointer();
		}
		
		/**
		 * @brief != operator that checks whether our iterator is unequal to another
		 * @param an iterator on a matrix
		 * @return our iterator
		 */
		bool operator!=(const const_iterator& right) const
		{
			return !(*this == right);
		}
		

		/**
		 * @brief = operator that initalizes an iterator
		 * @param an iterator on a matrix
		 * @return our iterator
		 */
		const_iterator& operator=(const const_iterator& right)
		{
			_pointer = right.getPointer();
			return *this;
		}
		
		/**
		 * @brief getter for the vector iterator variable we have
		 * @return our iterator
		 */
		typename std :: vector<T> :: const_iterator getPointer() const
		{
			return _pointer;
		}
		
	private:
		
		typename std :: vector<T> :: const_iterator _pointer; /** iterator of vector<T> which represents the matrix */
	};
	
	/**
	 * @brief gets the begining of our iterator
	 * @return our iterator
	 */	
	const_iterator begin() const
	{
		return const_iterator(_matrix.begin());
	}
	
	/**
	 * @brief gets the end of our iterator
	 * @return our iterator
	 */
	const_iterator end() const
	{
		return const_iterator(_matrix.end());
	}
	
};

// initialize our static parallel variable
template<typename U>
bool Matrix<U> :: _parallel = false;


/**
 * @brief Overrides << operator for Matrix to print a matrix.
 * @param stream to write to
 * @param IntMatrix we wish to print
 * @return a stream with the matrix representation to print
 */
template<typename U>
std :: ostream& operator<< (std :: ostream& os, const Matrix<U>& ourMatrix)
{
	// for each row and column go index by index and add to our stream with proper spacing
	for (unsigned int i = 1; i <= ourMatrix.rows(); ++i)
	{
		for(unsigned int j = 1; j <= ourMatrix.cols(); ++j)
		{
			os << ourMatrix(i, j) << (PRINT_TAB);
		}
		os << (PRINT_NEW_LINE);
	}
	// return the stream to be printed
	return os;
}

/**
 * @brief Deep copy swaps between two matrixes
 * @param first matrix
 * @param second matrix
 */
template <typename U>
void swap(Matrix<U>& first, Matrix<U>& second)
{
	// swap all the values between two matrices
	std :: swap(first._colNum, second._colNum);
	std :: swap(first._rowNum, second._rowNum);
	std :: swap(first._matrix, second._matrix);
}


/**
 * @brief Specialized template function trans which returns the conjugate transpose for complex
 * number Matrices
 * @return a conjugate transposed matrix of Complex Numbers
 */
template<>
Matrix<Complex> Matrix<Complex> :: trans() const
{
	// create a copy of our matrix and switch indexes so that it is transposed
	Matrix<Complex> transMatrix(*this);
	for (unsigned int i = 1; i <= rows(); ++i)
	{
		for(unsigned int j = 1; j <= cols(); ++j)
		{
			transMatrix._matrix[((j -OFFSET) * rows()) + i - OFFSET] = (*this)(i, j).conj();
		}
	}
	// change column and row values
	transMatrix._setRow(cols());
	transMatrix._setCol(rows());
	return transMatrix;
}
#endif
