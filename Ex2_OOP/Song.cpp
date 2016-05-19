/********************************************************************************
 * @file Song.cpp
 * @author  Dan Kufra
 * @version 1.0
 * @date 01.09.2015
 *
 * @brief The SLabCPP Standard Song implementation file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard Song implementation.
 *
 * This implementation provides a Song type with extra capabilities.
 *
 * The implementation provides the following features:
 *  - Song defining parameters and functions
 *
 ********************************************************************************/
#include "Song.h"
#include <sstream>

#define TAG_NOT_FOUND 0

/**
 * @brief constructor from datamembers
 * @param string representing song title
 * @param string representing the tags ( not split yet)
 * @param string representing the artist
 */
Song :: Song(const std :: string& title, const std :: string& tagString,
             const std :: string& artist)
{
    setTitle(title);
    _createTagMap(tagString);
    setPerformer(artist);
}

/**
 * @brief builds our map of tags and their values
 * @param string holding all the tags and their values
 */
void Song :: _createTagMap(const std :: string& tagString)
{
    // goes over the string we reach and for each tag and value add to our map
    std::stringstream s(tagString);
    while(!s.eof()) 
	{
        std :: string tmpTag;
        s >> tmpTag;
        int tmpVal;
        s >> tmpVal;
        _addTag(tmpTag, tmpVal);
	}
}

/**
 * @brief checks whether a tag matches the song
 * @param word we are searching for
 * @return value of the tag or 0 if not found
 */
int Song :: checkForTag(std :: string query) const
{
    // if we didn't find it return 0 otherwise return the value
    std :: map<std :: string, int> :: iterator it;
    if(_tagMap.find(query) == _tagMap.end())
    {
        return TAG_NOT_FOUND;
    }
    else
    {
        return _tagMap.find(query) -> second;
    }
}

/**
 * @brief adds a tag to our tagMap
 * @param string of tag we wish to add
 * @param int of value of said tag
 */
void Song :: _addTag(std :: string tag, int value)
{
    _tagMap.insert(std :: pair <std :: string, int> (tag, value));
}


