/********************************************************************************
 * @file Parser.cpp
 * @author  Dan Kufra
 * @version 1.0
 * @date 01.09.2015
 *
 * @brief The SLabCPP Standard Parser file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard Parser.
 *
 * This file provides a Parser type with extra capabilities.
 *
 * The file provides the following features:
 *  - basic file reading operations
 *
 ********************************************************************************/

#include "Parser.h"

/**
 * @def EMPTY_LINE
 * @brief an empty line
 */
#define EMPTY_LINE ""

#define FILE_ERROR "Error! Can't open file: "

#define PERIOD "."

/**
 * @brief Function that reads a line (skips over empty lines)
 * @param an ifstream to read from
 */
std :: string Parser :: readLine(std :: ifstream& stream)
{
    std :: string line = EMPTY_LINE;
    // skip over empty line
    while(line == EMPTY_LINE && stream.good())
    {
        getline(stream, line);
    }
    return line;
}

void Parser :: checkIfOpen(std :: ifstream& stream, const std :: string& songsFileName)
{
    /**
     * @brief Function that reads a line (skips over empty lines)
     * @param an ifstream to read from
     */
    if (!stream.is_open())
    {
        std::cerr << FILE_ERROR << songsFileName << PERIOD << std::endl;
    }
}