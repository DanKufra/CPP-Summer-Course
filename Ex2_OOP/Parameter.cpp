
/********************************************************************************
 * @file Parameter.h
 * @author  Dan Kufra
 * @version 1.0
 * @date 01.09.2015
 *
 * @brief The SLabCPP Standard Parameter implementation file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard Parameter implementation.
 *
 * This implementation provides a Parameter type with extra capabilities.
 *
 * The implementation provides the following features:
 *  - basic Parameter object
 *
 ********************************************************************************/
#include "Parameter.h"

/**
 * @brief Constructor for Parameter from 4 ints in the parameter file
 * @param score of a tag match
 * @param score of a lyric match
 * @param score of an instrument match
 * @param score of a bpm match
 */
Parameter :: Parameter(int tagScore, int lyricScore, int instrumentScore, int bpmScore)
{
    _tagMatchScore = tagScore;
    _lyricsMatchScore = lyricScore;
    _instrumentMatchScore = instrumentScore;
    _bpmLikelihoodWeight = bpmScore;
}

/**
 * @brief function returns the data of a saved word (pair of doubles)
 * @param name of the word we wish to find
 * @return a pair of two doubles which holds the bpm average and bias of a word
 */
std :: pair <double, double> Parameter :: getWordDetails(const std :: string& name) const
{
    return _savedWords.find(name) -> second;
}

/**
 * @brief function that adds words into the map of saved words
 * @param string the name of the word
 * @param the bpm average of the saved word
 * @param the bpm bias of the the saved word
 */
void Parameter :: addToWords(const std :: string& name, double average, double bias)
{
    std :: pair < double, double> specs(average, bias);
    _savedWords.insert(std :: pair <std :: string, std :: pair <double, double>>(name, specs));
}
