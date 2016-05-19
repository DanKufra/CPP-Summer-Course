/********************************************************************************
 * @file ParameterParser.cpp
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
 * The LabCPP Standard ParameterParser implementation.
 *
 * This implementation provides a ParameterParser type with extra capabilities.
 *
 * The implementation provides the following features:
 *  - basic file reading operations for a file of search parameters
 *
 ********************************************************************************/

#include "ParameterParser.h"

/**
 * @def EMPTY_LINE
 * @brief An empty line
 */
#define EMPTY_LINE ""
/**
 * @brief functions reads a file and creates a parameter object which it returns
 * @return Parameter object we wish to return
 */
Parameter ParameterParser :: getParameters(const std :: string& fileName)
{
    // open a stream and check if it is open
    std::ifstream instream(fileName.c_str());
    Parser :: checkIfOpen(instream, fileName);
    std::string line = EMPTY_LINE;
    // read each line and put the value we get from getVal in the proper field
    line = readLine(instream);
    int tagMatchScore = (int) _getVal(line);
    line = readLine(instream);
    int lyricsMatchScore = (int) _getVal(line);
    line = readLine(instream);
    int instrumentMatchScore = (int) _getVal(line);
    line = readLine(instream);
    int bpmWeight = (int) _getVal(line);
    // create a new Parameter object with the values we received
    Parameter newParameter(tagMatchScore, lyricsMatchScore, instrumentMatchScore, bpmWeight);
    // while the file is still good read the saved words and their average and bias
    while(instream.good())
    {
        line = readLine(instream);
        if(!instream.good())
        {
            break;
        }
        std :: string tmpStr = EMPTY_LINE;
        double average;
        double bias;
        std :: string comma = EMPTY_LINE;
        std :: stringstream strStream(line);
        strStream >> tmpStr;
        // get the string from the start until 1 before end
        tmpStr = tmpStr.substr(0, tmpStr.length() - 1);
        strStream >> average;
        strStream >> comma;
        strStream >> bias;
        // use Parameters method addToWords to add the saved word to its map
        newParameter.addToWords(tmpStr, average, bias);
    }
    return newParameter;
}

/**
 * @brief gets the value of each member of a parameter from a file
 * @return value of a line from the file
 */
double ParameterParser :: _getVal(const std :: string& line)
{
    
    double tmpVal;
    std :: string tmpStr = EMPTY_LINE;
    std :: stringstream strStream(line);
    strStream >> tmpStr >> tmpVal;
    return tmpVal;
}
