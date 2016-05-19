/********************************************************************************
 * @file SongParser.h
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
#ifndef SONG_PARSER_H
#define SONG_PARSER_H

#include "Parser.h"

/**
 * @brief a class which inherits from Parser and provides a method to get songs from a file
 */
class SongParser : public Parser
{
public:
    
    /**
     * @brief function reads songs from a file, creates Song objects and returns a vector of them
     * @param the file name
     * @return a vector of pointers to Song objects we created
     */
    static std :: vector<Song*> readSongsFromFile(const std::string& songsFileName);
    
private:
    
    /**
     * @brief function gets words from between { } in a line
     * @param the line we wish to separate
     * @return a string of just the words between { }
     */
    static std::string _getWordList(const std::string line);
};
#endif
