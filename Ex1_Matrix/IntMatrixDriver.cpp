/********************************************************************************
 * @file IntMatrixDriver.cpp
 * @author  Dan Kufra
 * @version 1.0
 * @date 25.08.2015
 *
 * @brief Driver for the IntMatrix.cpp file
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * Driver that receives input of matrices and operator  from user and calculates value 
 * of matrices with that operator
 *
 * Error handling
 * ~~~~~~~~~~~~~~
 * Driver assumes valid input of matrices as IntMatrix with only ints seperated by commas
 * Driver checks for valid input of operator.
 * Driver checks that matrices fit the given operator inputted.
 ********************************************************************************/

#include <iostream>
#include <sstream>
#include "IntMatrix.h"

/*
 * @def LEGAL_LOWER_BOUND
 * @brief Lower bound of int input for operand type.
 */
#define LEGAL_LOWER_BOUND 1

/*
 * @def LEGAL_UPPER_BOUND
 * @brief Upper bound of int input for operand type.
 */
#define LEGAL_UPPER_BOUND 5

/*
 * @def DELIMITER
 * @brief char that seprates inputs of int
 */
#define DELIMITER ","

/*
 * @def ONE_MATRIX
 * @brief number representing operand for one matrix
 */
#define ONE_MATRIX 1

/*
 * @def TWO_MATRICES
 * @brief number representing operand for two matrices
 */
#define TWO_MATRICES 2

/*
 * @def OP_PRINT_PROMPT
 * @brief Prints prompt for operands
 */
#define OP_PRINT_PROMPT "Choose operation:\n1. add\n2. sub\n3. mul\n4. trans\n5. trace"

/*
 * @def ERROR
 * @brief prints error for mul/sub/add errors
 * @param receves a string representing operator
 */
#define ERROR(op) std::cout << "Error: " << op << " failed - different dimensions.\n"

/*
 * @def TRACE_ERROR
 * @brief prints error for trace errors
 */
#define TRACE_ERROR "Error: trace failed - The matrix isn't square."

#define TRACE_MESSAGE "The matrix is square and its trace is "

/*
 * @def MATRIX_PROMPT
 * @brief Prints prompt for matrices
 * @param operator to print
 * @param number of matrices
 */
#define MATRIX_PROMPT(op, num) std::cout << "Operation " << op << " requires " << num << " operand"

/*
 * @def GOT_MATRIX
 * @brief Prints message when matrices are received.
 * @param number of matrices
 */
#define GOT_MATRIX(num) std :: cout << "--------\nGot " << num << " matrix:\n" << std :: endl

/*
 * @def GOT_SINGLE_MATRIX
 * @brief Prints message when matrix is received.
 */
#define GOT_SINGLE_MATRIX std :: cout << "--------\ngot matrix:\n" << std :: endl
/*
 * @def RESULT_MATRIX
 * @brief message before the final result print
 */
#define RESULT_MATRIX std :: cout << "==========\nResulted matrix:\n" << std :: endl

/*
 * @def MATRIX_PRINT
 * @brief string of one matrix for matrix prompt
 */
#define MATRIX_PRINT " matrix."

/*
 * @def TWO_MATRIX_PRINT
 * @brief string of two matrices for matrix prompt
 */
#define TWO_MATRIX_PRINT " matrices."

/*
 * @def INSERT_MATRIX
 * @brief prompts insertion of matrix
 */
#define INSERT_MATRIX(num) std :: cout << "Insert " << num << " matrix:" << std :: endl

/*
 * @def NUM_ROWS
 * @brief prompt for number of rows
 */
#define NUM_ROWS "number of rows:"

/*
 * @def NUM_COLS
 * @brief prompt for number of columns
 */
#define NUM_COLS "number of columns:"

/*
 * @def EXPLAIN
 * @brief Explains how to input the matrix
 */
#define EXPLAIN "Now insert the values of the matrix, row by row.\n\
After each cell add the char ',' (including after the last cell of a row).\n\
Each row should be in a separate line."

/*
 * @def FIRST
 * @brief first matrix
 */
#define FIRST "first"

/*
 * @def SECOND
 * @brief second matrix
 */
#define SECOND "second"

/*
 * @def ADD
 * @brief name of + operator
 */
#define ADD "add"

/*
 * @def SUB
 * @brief name of - operator
 */
#define SUB "sub"

/*
 * @def MUL
 * @brief name of * operator
 */
#define MUL "mul"

/*
 * @def TRANS
 * @brief name of trans operator
 */
#define TRANS "trans"

/*
 * @def TRACE
 * @brief name of trace operator
 */
#define TRACE "trace"

/*
 * @def TRACE_NUM
 * @brief number representing trace operator
 */
#define TRACE_NUM 5

/*
 * @def MULL_NUM
 * @brief number representing * operator
 */
#define MUL_NUM 3

/*
 * @def ADD_NUM
 * @brief number representing + operator
 */
#define ADD_NUM 1

/**
 * @brief Checks whether the input of operand number was legal
 * @param int input to check
 * @return true if legal, false if not
 */
static bool inputCheck(int input)
{
    if(input < LEGAL_LOWER_BOUND || input > LEGAL_UPPER_BOUND)
    {
        return false;
    }
    return true;
}

/**
 * @brief Checks whether trace can be calculated for IntMatrix
 * @param IntMatrix to check
 * @return true if legal, false if not
 */
static bool traceCheck(const IntMatrix &matrix)
{
    // trace can only be calculated if matrix is a square matrix
    if(matrix.getRow() != matrix.getCol())
    {
        return false;
    }
    return true;
}

/**
 * @brief Checks whether two matrices can be added or subtracted
 * @param IntMatrix to check
 * @param IntMatrix to check
 * @return true if can be added, false otherwise
 */
static bool addSubCheck(const IntMatrix &first, const IntMatrix &second)
{
    // addition/subtraction can only be calculated if matrix dimensions match
    if(first.getRow() != second.getRow() || first.getCol() != second.getCol())
    {
        return false;
    }
    return true;
}

/**
 * @brief Checks whether two matrices can be multiplied
 * @param IntMatrix to check
 * @param IntMatrix to check
 * @return true if can be multiplied, false otherwise
 */
bool mulCheck(const IntMatrix &first, const IntMatrix &second)
{
    // multiplication can only be calculated if first matrix col dimension match second matrix row
    if(first.getCol() != second.getRow())
    {
        return false;
    }
    return true;
}

/**
 * @brief Prints matrix input prompt
 * @param int number of matrixes
 * @param string operand name
 */
static void printMatrixMessage(int num, std::string op)
{
    MATRIX_PROMPT(op, num);
    if (num == ONE_MATRIX)
    {
        std :: cout << MATRIX_PRINT << std :: endl;
    }
    else
    {
        std :: cout << TWO_MATRIX_PRINT << std :: endl;
    }
}

/**
 * @brief Matches int input to an operand and prints the prompt
 * @param int input to match
 * @return int representing number of matrices needed
 */
int matrixInputPrompt(int input)
{
    
    std :: string operand;
    int numMatrices =  TWO_MATRICES;
    //set the operand name and the number of matrices depending on operator inputted
    switch (input)
    {
        case 1 :
            operand = ADD;
            break;
        case 2 :
            operand = SUB;
            break;
        case 3 :
            operand = MUL;
            break;
        case 4 :
            operand = TRANS;
            numMatrices = ONE_MATRIX;
            break;
        case 5 :
            operand = TRACE;
            numMatrices = ONE_MATRIX;
            break;
    }
    // print appropriate message depending on amount of matrices
    printMatrixMessage(numMatrices, operand);
    return numMatrices;
}

/**
 * @brief Receives matrix input from user
 * @return new IntMatrix object
 */
IntMatrix getMatrixInput()
{
    // get the row and col dimensions from the user
    int rowNum, colNum;
    std :: cout << NUM_ROWS;
    std :: cin >> rowNum;
    std :: cout << NUM_COLS;
    std :: cin >> colNum;
    // initialize an array of that size
    int *matrix = new int[rowNum * colNum];
    // receive the values to put in that array from the user
    std :: cout << EXPLAIN << std :: endl;
    for(int i = 0; i < rowNum; i++)
    {
        std :: string currentLine;
        std :: string token;
        // receive a line, then use find and substr to get each int from that line
        std :: cin >> currentLine;
        size_t position = 0;
        for (int j = 0; j < colNum; j++)
        {
            position = currentLine.find(DELIMITER);
            token = currentLine.substr(0, position);
            currentLine.erase(0, position + 1);
            // insert the int value into the proper index in the array
            std :: stringstream currentStream(token);
            int current = 0;
            currentStream >> current;
            matrix[(i * colNum) + j] = current;
        }
    }
    // use our constructor from an array and row/col dimensions to create a new object
    IntMatrix intMatrix(rowNum, colNum, matrix);
    delete[] matrix;
    return intMatrix;
}

/**
 * @brief Receives matrix and operator and calculates the result
 */
void calculateOneMatrix(int op, IntMatrix &intMatrix)
{
    // if the operator was trace, check it's legality and either print error or calculate
    if (op == TRACE_NUM)
    {
        if(traceCheck(intMatrix) == false)
        {
            std :: cout << TRACE_ERROR << std :: endl;
        }
        else
        {
            std :: cout << TRACE_MESSAGE << intMatrix.trace() << std :: endl;
        }
    }
    else
    {
        // if the operator was trans, calculate
        IntMatrix tempMatrix = intMatrix.trans();
        RESULT_MATRIX;
        std :: cout << tempMatrix << std :: endl;
    }
}

/**
 * @brief Receives two matrices and operator and calculates the result
 */
void calculateTwoMatrices(int op, IntMatrix &first, IntMatrix &second)
{
    IntMatrix tempMatrix;
    bool error = false;
    // if the operator was mul, check legality and calculate or print error
    if (op == MUL_NUM)
    {
        if(mulCheck(first, second) == false)
        {
            ERROR(MUL);
            error = true;
        }
        else
        {
            tempMatrix = first * second;
        }
    }
    // if the operator was add, check legality and calculate or print error
    else if (op == ADD_NUM)
    {
        if(addSubCheck(first, second) == false)
        {
            ERROR(ADD);
            error = true;
        }
        else
        {
            tempMatrix = first + second;
        }
    }
    else
    {
        // if the operator was sub, check legality and calculate or print error
        if(addSubCheck(first, second) == false)
        {
            ERROR(SUB);
            error = true;
        }
        else
        {
            tempMatrix = first - second;
        }
    }
    if(!error)
    {// print the matrix we calculated
        RESULT_MATRIX;
        std :: cout << tempMatrix << std :: endl;
    }
}

/**
 * @brief print helper method that prints a message for received matrixes.
 * @param matrix number
 * @param matrix to print
 */
void printInputtedMatrix(std :: string num, const IntMatrix& matrix) 
{
    GOT_MATRIX(num);
    std :: cout << matrix << std :: endl;
}
/**
 * @brief Main that deals with management of program, calls all functions
 */
int main()
{
    int operandChoice;
    // print the prompt and get the user's input for the operand
    do
    {
        std :: cout << OP_PRINT_PROMPT << std :: endl;
        std :: cin >> operandChoice;
    }while(!inputCheck(operandChoice));
    // print the matrix prompt
    int numMatrix = matrixInputPrompt(operandChoice);
    // if needed get two matrices and calculate the result
    if (numMatrix == TWO_MATRICES)
    {
        // get the first matrix from user
        INSERT_MATRIX(FIRST);
        IntMatrix firstMatrix = getMatrixInput();
        INSERT_MATRIX(SECOND);
        IntMatrix secondMatrix = getMatrixInput();
        printInputtedMatrix(FIRST, firstMatrix);
        printInputtedMatrix(SECOND, secondMatrix);
        calculateTwoMatrices(operandChoice, firstMatrix, secondMatrix);
    }
    // otherwise calculate just the first matrix
    else
    {
        IntMatrix firstMatrix = getMatrixInput();
        GOT_SINGLE_MATRIX;
        std :: cout << firstMatrix << std :: endl;
        calculateOneMatrix(operandChoice, firstMatrix);
    }
    return 0;
}
