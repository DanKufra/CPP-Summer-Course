
/********************************************************************************
 * @file Parameter.h
 * @author  Dan Kufra
 * @version 1.0
 * @date 01.09.2015
 *
 * @brief The SLabCPP Standard Parameter header file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard Parameter header.
 *
 * This header provides a Parameter type with extra capabilities.
 *
 * The header provides the following features:
 *  - basic Parameter object
 *
 ********************************************************************************/
#ifndef PARAMETER_H
#define PARAMETER_H
#include <map>
#include <string>

/**
 * @brief Parameter object class, holds the weights of the parameters we receive and a map of
 * key words for bpm score purposes
 */
class Parameter
{
public:
    
    /**
     * @brief Constructor for Parameter from 4 ints in the parameter file
     * @param score of a tag match
     * @param score of a lyric match
     * @param score of an instrument match
     * @param score of a bpm match
     */
    Parameter(int tagScore, int lyricScore, int instrumentScore, int bpmScore);
    
    /**
     * @brief getter for the tag match
     * @return the tag match
     */
    inline int getTagMatchScore() const
    {
        return _tagMatchScore;
    }

    /**
     * @brief getter for the lyric match
     * @return the lyrics match
     */
    inline int getLyricsMatchScore() const
    {
        return _lyricsMatchScore;
    }
    
    /**
     * @brief getter for the instrument match
     * @return the instrument match
     */
    inline int getInstrumentMatchScore() const
    {
        return _instrumentMatchScore;
    }
    
    /**
     * @brief getter for the bpm match
     * @return the bpm match
     */
    inline int getBPMScore() const
    {
        return _bpmLikelihoodWeight;
    }

    /**
     * @brief setter for the bpm match
     * @param the bpm match
     */
    inline void setBPMScore(int value)
    {
        _bpmLikelihoodWeight = value;
    }

    /**
     * @brief setter for the tag match
     * @param the tag match
     */
    inline void setTagMatchScore(int value)
    {
        _tagMatchScore = value;
    }
    
    /**
     * @brief setter for the lyric match
     * @param the lyric match
     */
    inline void setLyricMatchScore(int value)
    {
        _lyricsMatchScore = value;
    }
    
    /**
     * @brief setter for the instrument match
     * @param the instrument match
     */
    inline void setInstrumentMatchScore(int value)
    {
        _instrumentMatchScore = value;
    }
    
    /**
     * @brief function that adds words into the map of saved words
     * @param string the name of the word
     * @param the bpm average of the saved word
     * @param the bpm bias of the the saved word
     */
    void addToWords(const std :: string& name, double average, double bias);
    
    /**
     * @brief function returns the data of a saved word (pair of doubles)
     * @param name of the word we wish to find
     * @return a pair of two doubles which holds the bpm average and bias of a word
     */
    std :: pair <double, double> getWordDetails(const std :: string& name) const;
    
    /**
     * @brief Function checks whether a word is a saved word or not
     * @param name of the word we are searching for
     * @return boolean , true if word is saved false otherwise
     */
    inline bool isWordSaved(const std :: string& name) const
    {
        return _savedWords.find(name) != _savedWords.end();
    }

    
private:
    int _tagMatchScore;
    int _lyricsMatchScore;
    int _instrumentMatchScore;
    int _bpmLikelihoodWeight;
    std :: map < std :: string, std :: pair <double, double> > _savedWords ;
};

#endif

