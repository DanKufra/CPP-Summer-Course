/********************************************************************************
 * @file Song.h
 * @author  Dan Kufra
 * @version 1.0
 * @date 30.08.2015
 *
 * @brief The SLabCPP Standard Song header file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard Song header.
 *
 * This header provides a Song type with extra capabilities.
 *
 * The header provides the following features:
 *  - Song defining parameters and functions
 *
 ********************************************************************************/

#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <map>

#define DEFAULT_VALUE 0

/**
 * @brief Class which holds a Song object, its methods and data members
 */
class Song
{
public:
    
    /**
     * @brief default constructor
     */
    Song();
    
    /**
     * @brief constructor from datamembers
     * @param string representing song title
     * @param string representing the tags ( not split yet)
     * @param string representing the artist
     */
    Song(const std :: string& title, const std :: string& tagString, const std :: string& artist);
    
    /**
     * @brief checks whether a tag matches the song
     * @param word we are searching for
     * @return value of the tag
     */
    int checkForTag(std :: string query) const;
    
    /**
     * @brief getter for song title
     * @return song title
     */
    inline std :: string getTitle()
    {
        return _title;
    }

    /**
     * @brief getter for song performer
     * @return song performer
     */
    inline std :: string getPerformer()
    {
        return _performer;
    }
    
    /**
     * @brief setter for song title
     * @param name of song title
     */
    inline void setTitle(std :: string name)
    {
        _title = name;
    }

    /**
     * @brief setter for song performer
     * @param name of song performer
     */
    inline void setPerformer(std :: string name)
    {
        _performer = name;
    }

    /**
     * @brief virtual setter for song bpm
     */
    virtual void setBPM(double bpm)
    {
        (void) bpm;
    }
    
    /**
     * @brief virtual getter for song bpm
     * @return song bpm, if not overriden in derived class returns 0
     */
    virtual double getBPM()
    {
        return DEFAULT_VALUE;
    }
    
    /**
     * @brief virtual getter for amount of time a lyric appears in song
     * @return if not overriden in derived class returns 0
     */
    virtual int getLyricCount(const std :: string& query) const
    {
        (void) query;
        return DEFAULT_VALUE;
    }
    
    /**
     * @brief virtual getter for if instrument appears in song
     * @return if not overriden in derived class returns 0
     */
    virtual int getInstrumentCount(const std :: string& query) const
    {
        (void) query;
        return DEFAULT_VALUE;
    }
    
    /**
     * @brief pure virtual function that prints the artist of the song
     */
    virtual void printArtist() = 0;

    /**
     * @brief virtual destructor
     */
    virtual ~Song()
    {
    }
    
    
    
private:
    
    /**
     * @brief builds our map of tags and their values
     * @param string holding all the tags and their values
     */
    void _createTagMap(const std :: string& tagString);
    
    /**
     * @brief adds a tag to our tagMap
     * @param string of tag we wish to add
     * @param int of value of said tag
     */
    void _addTag(std :: string tag, int value);
    // data members of a Song
    std :: string _title;
    std :: map<std :: string, int> _tagMap;
    std :: string _performer;
    
};
#endif
