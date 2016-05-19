/********************************************************************************
 * @file QueryParser.h
 * @author  Dan Kufra
 * @version 1.0
 * @date 01.09.2015
 *
 * @brief The SLabCPP Standard QueryParser header file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard QueryParser header.
 *
 * This header provides a QueryParser type with extra capabilities.
 *
 * The header provides the following features:
 *  - basic file reading operations for a file of queries
 *
 ********************************************************************************/
#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

#include "Parser.h"

/**
 * @brief a class which inherits from Parser and provides a method to get queries from a file
 */
class QueryParser : public Parser
{
public:
    
    /**
     * @brief receives a file stream and reads the queries from it.
     * @param the file stream
     * @return a query
     */
    static std:: string getQueries(std :: ifstream& instream);
        
};

#endif
