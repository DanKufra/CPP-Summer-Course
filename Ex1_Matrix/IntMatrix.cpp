/********************************************************************************
 * @file IntMatrix.cpp
 * @author  Dan Kufra
 * @version 1.0
 * @date 25.08.2015
 *
 * @brief The SLabCPP Standard IntMatrix library.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard IntMatrix implementation.
 *
 * This implementation provides a IntMatrix type with extra capabilities.
 *
 * The implementation provides the following features:
 *  - basic matrix operations
 *
 * Error handling
 * ~~~~~~~~~~~~~~
 * Most functions assume the user has given it a proper matrix. i.e correct dimensions and int
 * values.
 ********************************************************************************/
#include <cstdlib>
#include <iostream>
#include "IntMatrix.h"
#include <assert.h>

/*
 * @def SPACE
 * @brief Space character.
 */
#define  SPACE " "

/*
 * @def NEW_LINE
 * @brief New line character.
 */
#define NEW_LINE "\n"

/*
 * @def DEF_VALUE
 * @brief Macro represneting starting value of row and col dimensions.
 */
#define DEF_VALUE 0

/*
 * @def DEF_SIZEE
 * @brief Macro representing starting size of new IntMatrix int array.
 */
#define DEF_SIZE 1

/*Constructors
 ********************************************************************************/
/**
 * A default constructor which receives no values.
 * @see initMatrix();
 */

IntMatrix :: IntMatrix()
{
    _initMatrix();
}

/**
 * @brief A copy constructor which receives an IntMatrix object and deep copies it.
 * @param An IntMatrix object to be copied.
 */
IntMatrix :: IntMatrix(const IntMatrix &copyMatrix)
{
    _initMatrix();
    *this = copyMatrix;
}

/**
 * @brief A constructor which receives the dimensions of the matrix and an array and creates a
 * new IntMatrix
 * @param row dimension
 * @param column dimension
 * @param array of ints
 */
IntMatrix :: IntMatrix(int rowAmnt, int colAmnt, int arr[]) :   _rowNum(rowAmnt), 
                                                                _colNum(colAmnt)
{
    // sets the dimensions of rows and columns and initializes the array
    _matrix = new int[_rowNum * _colNum];
    std :: copy(arr, &arr[_rowNum * _colNum], _matrix);

}

/**
 * @brief A constructor which receives the dimensions and creates a new empty IntMatrix
 * @param row dimension
 * @param column dimension
 */
IntMatrix :: IntMatrix(int rowAmnt, int colAmnt) :  _rowNum(rowAmnt),
                                                    _colNum(colAmnt)
{
    // sets the dimensions of rows and columns and initializes a new empty array
    _matrix = new int[_rowNum * _colNum];
}

/**
 * @brief Destructor for IntMatrix
 */
IntMatrix :: ~IntMatrix()
{
    // deletes the dynamically allocated int array
    delete[] _matrix;
}

/**
 * @brief Overrides += operator for IntMatrix to add a matrix to current matrix.
 * @param IntMatrix we wish to add to the current matrix.
 * @return IntMatrix& reference to the IntMatrix we updated
 */
IntMatrix& IntMatrix :: operator+= (const IntMatrix& other)
{
	assert (getRow() == other.getRow() && getCol() == other.getCol());
    // goes over each element in the IntMatrix's matrix and adds to it
    for(int i = 0; i < _rowNum * _colNum ; i++)
    {
        _matrix[i] += other.getArr()[i];
    }
    return *this;
}

/**
 * @brief Overrides -= operator for IntMatrix to subtract a matrix to current matrix.
 * @param IntMatrix we wish to subtract to the current matrix.
 * @return IntMatrix& reference to the IntMatrix we updated
 */
IntMatrix& IntMatrix :: operator-= (const IntMatrix& other)
{
	assert (getRow() == other.getRow() && getCol() == other.getCol());
    // goes over each element in the IntMatrix's matrix and subtracts from it
    for(int i = 0; i < _rowNum * _colNum ; i++)
    {
        _matrix[i] -= other.getArr()[i];
    }
    return *this;
}

/**
 * @brief Calculates the dot product between a row and column of valid sizes
 * @param pointer to begining of the row
 * @param pointer to the begining of the column
 * @param length of the row
 * @param length of the column
 * @return the dot product
 */
static int dotProduct(int *firstArray, int *secondArray, int lengthRow, int lengthCol)
{
    int sum = 0;
    for(int i = 0; i < lengthRow; i++)
    {
        sum += firstArray[i] * secondArray[i * lengthCol];

    }
    return sum;
}

/**
 * @brief Overrides *= operator for IntMatrix to multiply a matrix with current matrix.
 * @param IntMatrix we wish to multiply the current matrix.
 * @return IntMatrix& reference to the IntMatrix we updated
 */
IntMatrix& IntMatrix :: operator*= (const IntMatrix &other)
{
	assert (getCol() == other.getRow());
    // initialize and empty matrix of the proper size
    IntMatrix tempMatrix(getRow(), other.getCol());
    // initialize each index in that matrix to be the dot product between a row and column
    for (int i = 0; i < tempMatrix.getRow(); i++)
    {
        for (int j = 0; j < tempMatrix.getCol(); j++)
        {
            tempMatrix.getArr()[(i * tempMatrix.getCol()) + j] = dotProduct(&getArr()[i * _colNum],
                                                      &other.getArr()[j], _colNum, other.getCol());
        }
    }
    // set our matrix to equal this matrix and return its reference
    *this = tempMatrix;
    return *this;
}

/**
 * @brief Overrides = operator for IntMatrix to set a matrix to current matrix.
 * @param IntMatrix we wish to set to the current matrix.
 * @return IntMatrix& reference to the IntMatrix we updated
 */
IntMatrix& IntMatrix :: operator=(const IntMatrix &other)
{
    // check that our matrix doesn't already equal the new one
    if (this == &other)
    {
        return *this;
    }
    else
    {
        // delete the old array it held, and reset it's values to proper size. Then copy values
        delete [] _matrix;
        _colNum = other.getCol();
        _rowNum = other.getRow();
        _matrix = new int[_rowNum * _colNum];
        std :: copy(other.getArr(), other.getArr() + _rowNum * _colNum, _matrix);
    }
    return *this;
}

/**
 * @brief Overrides + operator for IntMatrix to add a matrix to current matrix.
 * @param IntMatrix we wish to add to the current matrix.
 * @return a new IntMatrix we created
 */
const IntMatrix IntMatrix :: operator+(const IntMatrix &other) const
{
    // copy our matrix, use += to add other to it, then return it
    IntMatrix additionMatrix(*this);
    additionMatrix += other;
    return additionMatrix;
}

/**
 * @brief Overrides - operator for IntMatrix to subtract a matrix from the current matrix.
 * @param IntMatrix we wish to subtract from the current matrix.
 * @return a new IntMatrix we created
 */
const IntMatrix IntMatrix :: operator-(const IntMatrix &other) const
{
    // copy our matrix, use -= to subtract other from it, then return it
    IntMatrix subMatrix(*this);
    subMatrix -= other;
    return subMatrix;
}

/**
 * @brief Overrides * operator for IntMatrix to multiply a matrix by current matrix.
 * @param IntMatrix we wish to multiply by the current matrix.
 * @return a new IntMatrix we created
 */
const IntMatrix IntMatrix :: operator*(const IntMatrix &other) const
{
    // copy our matrix, use *= to multiply it by other, then return it
    IntMatrix mulMatrix(*this);
    mulMatrix *= other;
    return mulMatrix;
}


/**
 * @brief Calculates the transpose of a matrix and returns it.
 * @return The transposed IntMatrix.
 */
const IntMatrix IntMatrix :: trans() const
{

    // create a copy of our matrix and switch indexes so that it is transposed
    IntMatrix transMatrix(*this);
    for (int i = 0; i < _rowNum; i++)
    {
        for( int j = 0; j < _colNum; j++)
        {
            transMatrix.getArr()[(j * _rowNum) + i] = _matrix[(i * _colNum) + j];
        }
    }
    // change column and row values
    transMatrix.setRow(_colNum);
    transMatrix.setCol(_rowNum);
    return transMatrix;
}

/**
 * @brief Calculates the trace of a matrix and returns it. Assumes it is given a square matrix
 * @return The trace of the matrix.
 */
int IntMatrix :: trace() const
{
	assert (getRow() == getCol());
    // go index by index and when the row num equals the col num add that value to the sum
    int sum = 0;
    for (int i = 0; i < getRow(); i++) 
	{
        for(int j = 0; j < getCol(); j++)
        {
            if (j == i)
            {
                sum += getArr()[(i * getCol()) + j];
            }
        }
	}
    return sum;
}

/**
 * @brief Overrides << operator for IntMatrix to print a matrix.
 * @param stream to write to
 * @param IntMatrix we wish to print
 * @return a stream with the matrix representation to print
 */
std::ostream& operator<< (std::ostream& os, const IntMatrix &ourMatrix)
{
    if(ourMatrix.getRow() == DEF_VALUE || ourMatrix.getArr() == DEF_VALUE )
    {
        os << (NEW_LINE);
    }
    // for each row and column go index by index and add to our stream with proper spacing
    for (int i = 0; i < ourMatrix.getRow(); i++)
    {
        for(int j = 0; j < ourMatrix.getCol(); j++)
        {
			os << ourMatrix.getArr()[i * ourMatrix.getCol() + j];
            if (j != ourMatrix.getCol() - 1)
            {
                os << (SPACE);
            }
        }
        os << (NEW_LINE);
    }
    // return the stream to be printed
    return os;
}

/**
 * @brief Initializes an empty IntMatrix
 * @param new row dimension
 */
void IntMatrix :: _initMatrix()
{
    // intiialize a matrix with default values
    _matrix = new int[DEF_SIZE];
    _rowNum = DEF_VALUE;
    _colNum = DEF_VALUE;
}

