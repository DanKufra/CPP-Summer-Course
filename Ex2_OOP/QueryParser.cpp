/********************************************************************************
 * @file QueryParser.cpp
 * @author  Dan Kufra
 * @version 1.0
 * @date 01.09.2015
 *
 * @brief The SLabCPP Standard QueryParser implementation file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard QueryParser implementation.
 *
 * This implementation provides a QueryParser type with extra capabilities.
 *
 * The implementation provides the following features:
 *  - basic file reading operations for a file of queries
 *
 ********************************************************************************/

#include "QueryParser.h"

/**
 * @brief receives a file stream and reads the queries from it.
 * @param the file stream
 * @return a query
 */
 std:: string QueryParser :: getQueries(std :: ifstream& instream)
{
	return readLine(instream);
}
