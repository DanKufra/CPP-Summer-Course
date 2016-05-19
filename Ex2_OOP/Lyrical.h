/********************************************************************************
 * @file Lyrical.h
 * @author  Dan Kufra
 * @version 1.0
 * @date 30.08.2015
 *
 * @brief The SLabCPP Standard Lyrical header file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard Lyrical header.
 *
 * This header provides a Lyrical type with extra capabilities.
 *
 * The header provides the following features:
 *  - Lyrical defining parameters and functions
 *
 ********************************************************************************/
#ifndef LYRICAL_H
#define LYRICAL_H

#include "Song.h"
#include <set>

/**
 * @brief Class which holds a Lyrical object, its methods and data members. Is derived from Song.
 */
class Lyrical : public Song
{
public:
    
    /**
     * @brief default constructor
     */
    Lyrical();
    
    /**
     * @brief constructor from datamembers
     * @param string representing song title
     * @param string representing the tags ( not split yet)
     * @param multiset of strings representing the lyrics
     * @param string representing the artist
     */
    Lyrical(const std :: string&title, const std :: string&tags,
            const std :: multiset<std :: string>& lyrics, const std :: string&lyricsBy);
    
    /**
     * @brief finds the amount of time a query is in a Lyrical's lyrics. Overrides virtual function
     * @param the query we are searching for
     * @return the amount of times a query shows up in the lyrics
     */
    int getLyricCount(const std :: string& query) const override;
    
    /**
     * @brief A function that prints the artist as required. Overrides virtual function
     */
    void printArtist() override;
    
    /**
     * @brief destructor for Lyrical object
     */
    ~Lyrical()
    {
        
    }

    
private:
    
    std :: multiset<std :: string> _lyricSet;
};

#endif

