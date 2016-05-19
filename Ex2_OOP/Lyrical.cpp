/********************************************************************************
 * @file Lyrical.cpp
 * @author  Dan Kufra
 * @version 1.0
 * @date 30.08.2015
 *
 * @brief The SLabCPP Standard Lyrical implementation file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard Lyrical implementation.
 *
 * This implementation provides a Lyrical type with extra capabilities.
 *
 * The implementation provides the following features:
 *  - Lyrical defining parameters and functions
 *
 ********************************************************************************/
#include "Lyrical.h"

/**
 * @def ARIST_PRINT
 * @brief string printed before artist
 */
#define ARTIST_PRINT "\tlyrics by: "
/**
 * @brief constructor from datamembers
 * @param string representing song title
 * @param string representing the tags ( not split yet)
 * @param multiset of strings representing the lyrics
 * @param string representing the artist
 */
Lyrical :: Lyrical(const std :: string&title, const std :: string&tags,
                   const std :: multiset<std :: string>& lyrics,
                   const std :: string&lyricsBy) : Song(title, tags, lyricsBy)
{
    _lyricSet = lyrics;
}

/**
 * @brief finds the amount of time a query is in a Lyrical's lyrics. Overrides virtual function
 * @param the query we are searching for
 * @return the amount of times a query shows up in the lyrics
 */
int Lyrical :: getLyricCount(const std :: string& query) const
{
    return (int) _lyricSet.count(query);
}

/**
 * @brief A function that prints the artist as required. Overrides virtual function
 */
void Lyrical :: printArtist()
{
    std :: cout << ARTIST_PRINT << getPerformer();
}

