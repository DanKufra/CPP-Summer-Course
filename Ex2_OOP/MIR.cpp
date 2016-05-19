#include "Song.h"
#include "SongParser.h"
#include "ParameterParser.h"
#include "QueryParser.h"
#include "Parameter.h"
#include <cmath>
#include <cassert>

/**
 * @def LINE_SPLIT
 * @brief string that splits between query searches
 */
#define LINE_SPLIT "----------------------------------------"

/**
 * @def QUERY_WORD
 * @brief Message to be printed before our query
 */
#define QUERY_WORD "Query word: "

/**
 * @def TAB
 * @brief a tab
 */
#define TAB "\t"

/**
 * @def ARG_COUNT
 * @brief amount of arguments required
 */
#define ARG_COUNT 4

/**
 * @def SONG_FILE
 * @brief index of song file
 */
#define SONG_FILE 1

/**
 * @def PARAMETER_FILE
 * @brief index of parameter file
 */
#define PARAMETER_FILE 2

/**
 * @def QUERY_FILE
 * @brief index of query file
 */
#define QUERY_FILE 3

/**
 * @def DEFAULT_SCORE
 * @brief score that each song will start with
 */
#define DEFAULT_SCORE 0

#define POW_NOM_MULTIPLIER (-1)

#define POW_DENOM_MULTIPLIER 2

#define POWER 2

/**
 * @brief calculates the BPM weight of a song based on a the query's bpm average and bias
 * @param the songs BPM
 * @param a pair of doubles representing the query's average and bias bpm
 * @return a double representing the calculation of the BPM
 */
static double calculateBPM(double songBPM, std :: pair <double, double> paramPair)
{
    double powNom = POW_NOM_MULTIPLIER * pow(songBPM - paramPair.first, POWER);
    double powDeNom = POW_DENOM_MULTIPLIER * pow(paramPair.second, POWER);
    double bpmWeight = exp(powNom / powDeNom);
    return bpmWeight;
}

/**
 * @brief function searches a vector of Song pointers for a query and calculates the scores based
 * on a Parameter object given.
 * @param a string of a query we are searching for
 * @param a vector of pointers to Songs
 * @param a Parameter object we read from a file
 * @return a sorted multimap where the keys are scores and the values are pointers to Song objects.
 */
std :: multimap <int, Song*, std :: greater<int>> searchSongs (const std :: string& query,
                                    						   const std :: vector<Song*>& songs,
															   const Parameter& param)
{
    // create a new multimap to be filled and sorted
    std :: multimap <int, Song*, std :: greater<int>> songScoreMap;
    // go over each song in our Song pointer vector
    for (Song* song : songs)
    {
        int score = DEFAULT_SCORE;
        // calculate the score based on tag lyric and instrument match
        score += song -> checkForTag(query) * param.getTagMatchScore();
        score += song -> getLyricCount(query) * param.getLyricsMatchScore();
        score += song -> getInstrumentCount(query) * param.getInstrumentMatchScore();
        // if the query is a saved parameter word and the song is instrumental/has bpm ,calculate
        if(param.isWordSaved(query) && song -> getBPM() > DEFAULT_SCORE)
        {
            score += floor(calculateBPM(song -> getBPM(), param.getWordDetails(query)) *
                           param.getBPMScore());
        }
        // if the score calculated for the song is above 0 add it to our multimap
        if(score > DEFAULT_SCORE)
        {
            songScoreMap.insert(std::pair<int, Song*>(score, song));
        }
    }
    // return the map once we went over all the songs
    return songScoreMap;
}

/**
 * @brief function that prints a list of songs in the format required
 * @param a multimap of pointers to songs and their scores
 * @param a string we are searching fors
 */
static void printSongs(std :: multimap <int, Song*, std :: greater<int>> songs,
                       const std :: string& query)
{
    // print a line split and the word we are searching for
    std :: cout << LINE_SPLIT << std :: endl;
    std :: cout << QUERY_WORD << query << std :: endl;

    // for each song print a new line, the title and score and the artist
    for (std::multimap<int, Song*>::iterator it = songs.begin(); it != songs.end(); ++it)
    {
        std :: cout << std :: endl;
        std :: cout << (*it).second -> getTitle() << TAB << (*it).first;
        (*it).second ->printArtist();
    }
    std :: cout << std :: endl;
}


/**
 * @brief main function that receives 3 files as parameters and calls parsers to read them and
 *  calculates a songs score then prints them in order.
 * @param amount of arguments
 * @param list of arguments given from command line, should be 3 files names.
 * @return 0 when program is done running
 */
int main(int argc, const char * argv[])
{
    // make sure 3 parameters were entered
    assert (argc == ARG_COUNT);
    // parse all three files
    std :: vector<Song*> songList = SongParser :: readSongsFromFile(argv[SONG_FILE]);
    Parameter params = ParameterParser :: getParameters(argv[PARAMETER_FILE]);
	// open query file for parsing
    std::ifstream instream(argv[QUERY_FILE]);
    Parser :: checkIfOpen(instream, argv[QUERY_FILE]);
    // for each query search the songs, calculate score based on parameters and print in order
	while(instream.good())
	{
		std :: string query = QueryParser :: getQueries(instream);
        if(!instream.good())
        {
            break;
        }
        std :: multimap <int, Song*, std :: greater<int>> songScores = searchSongs(query, songList, params);
        printSongs(songScores, query);
    }
    
    // delete our dynamically allocated Song objects
    for(Song* song : songList)
    {
        delete song;
    }
    return 0;
}







