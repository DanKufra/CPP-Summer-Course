/********************************************************************************
 * @file Instrumental.h
 * @author  Dan Kufra
 * @version 1.0
 * @date 30.08.2015
 *
 * @brief The SLabCPP Standard Instrumental header file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard Instrumental header.
 *
 * This header provides a Instrumental type with extra capabilities.
 *
 * The header provides the following features:
 *  - Instrumental defining parameters and functions
 *
 ********************************************************************************/
#ifndef INSTRUMENTAL_H
#define INSTRUMENTAL_H

#include "Song.h"
#include <unordered_set>

/**
 * @brief Class which holds a Instrumental object, its methods and data members. Is derived from Song.
 */
class Instrumental : public Song
{
public:
    
    /**
     * @brief default constructor
     */
    Instrumental();
    
    /**
     * @brief constructor from datamembers
     * @param string representing song title
     * @param string representing the tags ( not split yet)
     * @param unordered_set of strings representing the instruments
     * @param string representing the artist
     */
    Instrumental(const std :: string&title, const std :: string&tags,
                 const std :: unordered_set<std :: string>& instruments,
                 const std :: string&performedBy);
    
    /**
     * @brief checks whether an instrument is included in instrument list
     * @param string representing the instrument
     * @return true if found, false otherwise
     */
    bool isInstrument(std :: string instrument) const;
    
    /**
     * @brief getter for song bpm. Overrides virtual function in song
     * @return song bpm
     */
    double getBPM() override
    {
        return _bpm;
    }
    
    /**
     * @brief setter for song bpm. Overrides virtual function in Song
     */
    void setBPM(double value) override
    {
        _bpm = value;
    }
    
    /**
     * @brief getter for instrument if it appears in song. Overrides virtual function in Song
     * @return if not overriden in derived class returns 0
     */
    int getInstrumentCount(const std :: string& query) const override;
    
    /**
     * @brief A function that prints the artist as required. Overrides virtual function
     */
    void printArtist() override;

    /**
     * @brief destructor for Lyrical object
     */
    ~Instrumental()
    {
        
    }

private:
    
    std :: unordered_set<std :: string> _instrumentSet;
    double _bpm;
};

#endif
