/********************************************************************************
 * @file ParameterParser.h
 * @author  Dan Kufra
 * @version 1.0
 * @date 01.09.2015
 *
 * @brief The SLabCPP Standard ParameterParser header file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard ParameterParser header.
 *
 * This header provides a ParameterParser type with extra capabilities.
 *
 * The header provides the following features:
 *  - basic file reading operations for a file of search parameters
 *
 ********************************************************************************/

#ifndef PARAMATER_PARSER_H
#define PARAMATER_PARSER_H
#include "Parser.h"
#include "Parameter.h"

/**
 * @brief a class which inherits from Parser and provides a method to get parameters from a file
 */
class ParameterParser : public Parser
{

public:

    /**
     * @brief functions reads a file and creates a parameter object which it returns
     * @return Parameter object we wish to return
     */
    static Parameter getParameters(const std :: string& fileName);
    
private:
    
    /**
     * @brief gets the value of each member of a parameter from a file
     * @return value of a line from the file
     */
    static double _getVal(const std :: string& line);
};

#endif
