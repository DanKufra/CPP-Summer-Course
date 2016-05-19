/********************************************************************************
 * @file SongParser.cpp
 * @author  Dan Kufra
 * @version 1.0
 * @date 01.09.2015
 *
 * @brief The SLabCPP Standard SongParser implementation file.
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * The LabCPP Standard SongParser implementation.
 *
 * This implementation provides a SongParser type with extra capabilities.
 *
 * The implementation provides the following features:
 *  - basic file reading operations for a file of song parameters
 *
 ********************************************************************************/

#include <cassert>
#include "Instrumental.h"
#include "Lyrical.h"
#include "SongParser.h"

/**
 * @def POS_MODIFIER
 * @brief modifies position of the part of the string we are splitting by one
 */
#define POS_MODIFIER 1

/**
 * @def POS_MODIFIER_TWO
 * @brief modifies position of the part of the string we are splitting by one
 */
#define POS_MODIFIER_TWO 2

/**
 * @def EQUAL
 * @brief comparison is equal
 */
#define EQUAL 0

/**
 * @def LAST_SONG
 * @brief symbolizes we reached last song
 */
#define LAST_SONG 1

/**
 * @def NOT_LAST_SONG
 * @brief symbolizes we didn't reach last song
 */
#define NOT_LAST_SONG 0

// const strings of words that we need to compare our line to in the file
const std :: string SEPARATOR = "=";
const std :: string END_OF_SONGS = "***";
const std :: string TITLE = "title";
const std :: string TAGS = "tags";
const std :: string LYRICS = "lyrics";
const std :: string LYRICS_BY = "lyricsBy";
const std :: string INSTRUMENTS = "instruments";
const std :: string PERFORMED_BY = "performedBy";
const std :: string BPM = "bpm";
const std :: string EMPTY_LINE = "";
const std :: string OPEN_BRACKET  = "{";
const std :: string CLOSED_BRACKET  = "}";

/**
 * @brief function gets words from between { } in a line
 * @param the line we wish to separate
 * @return a string of just the words between { }
 */
std :: string SongParser :: _getWordList(const std :: string line)
{
    
    size_t pos1 = line.find(OPEN_BRACKET) + POS_MODIFIER;
    size_t pos2 = line.find(CLOSED_BRACKET);
    
    return line.substr(pos1 , pos2 - pos1);
}


/**
 * @brief function reads songs from a file, creates Song objects and returns a vector of them
 * @param the file name
 * @return a vector of pointers to Song objects we created
 */
 std :: vector<Song*> SongParser :: readSongsFromFile(const std :: string& songsFileName)
{
    
    // open a stream and check if it is open
    std::ifstream instream(songsFileName.c_str());
    Parser :: checkIfOpen(instream, songsFileName);
    
    // initalize an empty vector of pointers to song and empty string
    std :: vector<Song*> songList;
    std :: string line = EMPTY_LINE;
    
    int lastSong = NOT_LAST_SONG;
    
    while(instream.good() && !lastSong)
    {
        // check if we reached a new query
        if (line.compare(SEPARATOR) != EQUAL)
        {
            line = Parser :: readLine(instream);
            // Expect a line of "="
            if (END_OF_SONGS.compare(line) == EQUAL)
            {
                lastSong = LAST_SONG;
                break;
            }
        }
        // create a new song object
        Song *newSong;
        line = Parser :: readLine(instream);
        // Expect a line of "title: ..."
        size_t pos = TITLE.size() + POS_MODIFIER_TWO;
        std::string title = line.substr(pos);
        line = Parser :: readLine(instream);
        // Expect a line of "tags: {...}"
        std::string tags = _getWordList(line);
        std::string lyrics = EMPTY_LINE;
        std::string lyricsBy = EMPTY_LINE;
        std::string instruments = EMPTY_LINE;
        std::string performedBy = EMPTY_LINE;
        std::string bpmStr = EMPTY_LINE;
        
        line = Parser :: readLine(instream);
        // Expect either lyrics or instruments.
        if (line.substr(0, LYRICS.size()).compare(LYRICS) == EQUAL)
        {
            // Then we have a lyric song
            
            // Lets get the lyrics:
            lyrics = _getWordList(line);
            std :: multiset<std :: string> lyricSet;
            std::stringstream s(lyrics);
            while(!s.eof()) 
			{
                std :: string tmp;
                s >> tmp;
                lyricSet.insert(tmp);
            }
            // Lets get the lyricsBy:
            line = Parser :: readLine(instream);
            pos = LYRICS_BY.size() + POS_MODIFIER_TWO;
            lyricsBy = line.substr(pos);
            newSong = new Lyrical (title, tags, lyricSet, lyricsBy);
        }
        else
        {
            // Then we have an instrumental song
            
            // Lets get the instruments:
            instruments = _getWordList(line);
            std :: unordered_set<std :: string> instrumentSet(0);
            std::stringstream s(instruments);
            while(!s.eof()) 
			{
                std :: string tmp;
                s >> tmp;
                instrumentSet.insert(tmp);
            }
            // Lets get the performedBy:
            line = Parser :: readLine(instream);
            pos = PERFORMED_BY.size() + POS_MODIFIER_TWO;
            performedBy = line.substr(pos);
            newSong = new Instrumental(title, tags, instrumentSet, performedBy);
            // Lets see if we have bpm:
            if (!instream.good())
            {
                break;
            }
            line = Parser :: readLine(instream);
            if (END_OF_SONGS.compare(line) == EQUAL)
            {
                lastSong = LAST_SONG;
            }
            if (line.substr(0, BPM.size()).compare(BPM) == EQUAL)
            {
                
                pos = BPM.size() + POS_MODIFIER_TWO;
                bpmStr = line.substr(pos);
                double bpm = std :: stod(bpmStr);
                // set the bpm of the song
                newSong->setBPM(bpm);
            }
            else
            {
                assert ( (line.compare(SEPARATOR) == EQUAL) ||
                        (line.compare(END_OF_SONGS) == EQUAL));
            }
        }
        songList.push_back(newSong);
    }
    
    instream.close();
    return songList;
}

