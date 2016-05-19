/********************************************************************************
 * @file Instrumental.cpp
 * @author  Dan Kufra
 * @version 1.0
 * @date 30.08.2015
 *
 * @brief The SLabCPP Standard Instrumental implementation file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard Instrumental implementation.
 *
 * This implementation provides a Instrumental type with extra capabilities.
 *
 * The implementation provides the following features:
 *  - Instrumental defining parameters and functions
 *
 ********************************************************************************/
#include "Instrumental.h"

/**
 * @def ARTIST_PRINT
 * @brief string printed before artist
 */
#define ARTIST_PRINT "\tperformed by: "

/**
 * @def INSTRUMENT_FOUND
 * @brief Amount of instruments if it is in list
 */
#define INSTRUMENT_FOUND 1

/**
 * @def INSTRUMENT_NOT_FOUND
 * @brief Amount of instruments if it is not in list
 */
#define INSTRUMENT_NOT_FOUND 0

/**
 * @brief constructor from datamembers
 * @param string representing song title
 * @param string representing the tags ( not split yet)
 * @param unordered_set of strings representing the instruments
 * @param string representing the artist
 */
Instrumental :: Instrumental(const std :: string&title, const std :: string&tags,
                             const std :: unordered_set<std :: string>& instruments,
                             const std :: string& performedBy) : Song(title, tags, performedBy)
{
    _instrumentSet = instruments;
	_bpm = 0;
}

/**
 * @brief getter for instrument if it appears in song. Overrides virtual function in Song
 * @return if not overriden in derived class returns 0
 */
int Instrumental :: getInstrumentCount(const std :: string& query) const
{
    if(_instrumentSet.find(query) == _instrumentSet.end())
    {
        return INSTRUMENT_NOT_FOUND;
    }
    return INSTRUMENT_FOUND;
}

/**
 * @brief A function that prints the artist as required. Overrides virtual function
 */
void Instrumental :: printArtist()
{
    std :: cout << ARTIST_PRINT << getPerformer();
}
