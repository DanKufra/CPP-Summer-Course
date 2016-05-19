/********************************************************************************
 * @file Parser.h
 * @author  Dan Kufra
 * @version 1.0
 * @date 01.09.2015
 *
 * @brief The SLabCPP Standard Parser header file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard Parser header.
 *
 * This header provides a Parser type with extra capabilities.
 *
 * The header provides the following features:
 *  - basic file reading operations
 *
 ********************************************************************************/

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

/**
 * @brief Parser object that has functions to read a line and check that a file is open
 *
 */
class Parser
{
public:
    
    /**
     * @brief Function that reads a line (skips over empty lines)
     * @param an ifstream to read from
     */
    static std :: string readLine(std :: ifstream& stream);

    /**
     * @brief Function that reads a line (skips over empty lines)
     * @param an ifstream to read from
     */
    static void checkIfOpen(std :: ifstream& stream, const std :: string& songsFileName);
};

#endif
