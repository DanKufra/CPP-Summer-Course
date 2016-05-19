/********************************************************************************
 * @file IntMatrix.h
 * @author  Dan Kufra
 * @version 1.0
 * @date 25.08.2015
 *
 * @brief The SLabCPP Standard IntMatrix header file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard IntMatrix header.
 *
 * This header provides a IntMatrix type with extra capabilities.
 *
 * The header provides the following features:
 *  - basic matrix operations
 *
 * Error handling
 * ~~~~~~~~~~~~~~
 * Most functions assume the user has given it a proper matrix. i.e correct dimensions and int
 * values.
 ********************************************************************************/
#ifndef INTMATRIX_H
#define INTMATRIX_H

/**
 *  @brief Class that represents a matrix of Integers and includes some simply calculations. 
 *  that can be done to a matrix such as add/subtract/multiply/transpose/trace.
 */
class IntMatrix
{
public:
    
    /**
     * A default constructor which receives no values.
     * @see initMatrix();
     */
    IntMatrix();
    
    /**
     * @brief A copy constructor which receives an IntMatrix object and deep copies it.
     * @param An IntMatrix object to be copied.
     */
    IntMatrix(const IntMatrix &copyMatrix);
    
    /**
     * @brief A constructor which receives the dimensions of the matrix and an array and creates a
     * new IntMatrix
     * @param row dimension
     * @param column dimension
     * @param array of ints
     */
    IntMatrix(int rowAmnt, int colAmnt, int arr[]);
    
    /**
     * @brief A constructor which receives the dimensions and creates a new empty IntMatrix
     * @param row dimension
     * @param column dimension
     */
    IntMatrix(int rowAmnt, int colAmnt);
    
    /**
     * @brief Overrides += operator for IntMatrix to add a matrix to current matrix.
     * @param IntMatrix we wish to add to the current matrix.
     * @return IntMatrix& reference to the IntMatrix we updated
     */
    IntMatrix& operator+=(const IntMatrix &other);
    
    /**
     * @brief Overrides -= operator for IntMatrix to subtract a matrix to current matrix.
     * @param IntMatrix we wish to subtract to the current matrix.
     * @return IntMatrix& reference to the IntMatrix we updated
     */
    IntMatrix& operator-=(const IntMatrix &other);
    
    /**
     * @brief Overrides *= operator for IntMatrix to multiply a matrix with current matrix.
     * @param IntMatrix we wish to multiply the current matrix.
     * @return IntMatrix& reference to the IntMatrix we updated
     */
    IntMatrix& operator*=(const IntMatrix &other);
    
    /**
     * @brief Overrides = operator for IntMatrix to set a matrix to current matrix.
     * @param IntMatrix we wish to set to the current matrix.
     * @return IntMatrix& reference to the IntMatrix we updated
     */
    IntMatrix& operator=(const IntMatrix &other);
    
    /**
     * @brief Overrides + operator for IntMatrix to add a matrix to current matrix.
     * @param IntMatrix we wish to add to the current matrix.
     * @return a new IntMatrix we created
     */
    const IntMatrix operator+(const IntMatrix &right) const;

    /**
     * @brief Overrides - operator for IntMatrix to subtract a matrix from the current matrix.
     * @param IntMatrix we wish to subtract from the current matrix.
     * @return a new IntMatrix we created
     */
    const IntMatrix operator-(const IntMatrix &right) const;
    
    /**
     * @brief Overrides * operator for IntMatrix to multiply a matrix by current matrix.
     * @param IntMatrix we wish to multiply by the current matrix.
     * @return a new IntMatrix we created
     */
    const IntMatrix operator*(const IntMatrix &right) const;
    
    /**
     * @brief Calculates the trace of a matrix and returns it. Assumes it is given a square matrix
     * @return The trace of the matrix.
     */
    
    int trace() const;
    /**
     * @brief Calculates the transpose of a matrix and returns it.
     * @return The transposed IntMatrix.
     */
    const IntMatrix trans() const;
    
    /**
     * @brief Overrides << operator for IntMatrix to print a matrix.
     * @param stream to write to
     * @param IntMatrix we wish to print
     * @return a stream with the matrix representation to print
     */
    friend std::ostream& operator<< (std::ostream& os, const IntMatrix& ourMatrix);
    
    /**
     * @brief Getter for the row dimension of the IntMatrix.
     * @return Int row dimension
     */
    inline int getRow() const
    {
        return _rowNum;
    }
    
    /**
     * @brief Getter for the column dimension of the IntMatrix.
     * @return Column dimension
     */
    inline int getCol() const
    {
        return _colNum;
    }
    
    /**
     * @brief Getter for the array of IntMatrix
     * @return pointer to the int array of the IntMatrix
     */
    inline int* getArr() const
    {
        return _matrix;
    }
    
    /**
     * @brief Setter for the row dimension of IntMatrix
     * @param new row dimension
     */
    inline void setRow(int rowAmnt)
    {
        _rowNum = rowAmnt;
    }
    
    /**
     * @brief Setter for the column dimension of IntMatrix
     * @param new column dimension
     */
    inline void setCol(int colAmnt)
    {
        _colNum = colAmnt;
    }

    /**
     * @brief Destructor for IntMatrix
     */
    ~IntMatrix();
    
private:
    /**
     * @brief Initializes an empty IntMatrix
     * @param new row dimension
     */
    void _initMatrix();
    
    int *_matrix; /**< Pointer to the array of ints that IntMatrix has. */
    int _rowNum; /**< Row Dimension of IntMatrix. */
    int _colNum; /**< Column Dimension of IntMatrix. */

};

#endif
