#include "Methods.h"
#include "B.h"

using namespace std;

/* 1. Alphanumeric/Space/Lowercase:
 * https://cplusplus.com/reference/cctype/
 * 2. Converting to string:
 * https://en.cppreference.com/w/cpp/string/basic_string/to_string
 * 3. fstream class:
 * https://cplusplus.com/reference/fstream/fstream/
 */

void formatString (string &format) {
    /* Takes in strings for artists and albums and formats them.
     * Removes punctuation, sets to lowercase, and removes "the"
     * to account for slightly incorrect user input.
     */
    stack<int> remove;
    int index = 0;
    for (char &currChar : format) {
        if (isalnum(currChar) || isspace(currChar))  // 1
            currChar = tolower(currChar);               // 1
        else
            remove.push(index);
        index++;
    }

    while (!remove.empty()){
        format.erase(remove.top(),1);
        remove.pop();
    }

    if (format.substr(0,4) == "the ")
        format = format.substr(4, format.size() - 4);
}

double findAvg(double currAvg, double currSize, double newVal) {
    /* Recalculating average after inserting new song to avoid traversing song list twice */
    return (currAvg*currSize + newVal) / (currSize+1);
}

string getDecade(int year) {
    /* Makes the years end in zero to signify decade */
    if(year >= 2010) return "2010";
    year = year - year % 10;
    string decade = to_string(year); // 2
    return decade;
}

void createDS(const string& filePath, map<string,pair<string, string>>& mapIDs, B& bTree) { // 3
    /* Loads in data to tree and map data structures */

    string index, id, name, albumName, albumID, artistName, artistID;
    string danceability, energy, speechiness, acousticness, instrumentalness, valence, tempo, year;

    ifstream songs(filePath); // Open file

    // Checks that file is properly loaded
    if (!songs.is_open()) {
        cout << "File not opened" << endl;
        return;
    }

    getline(songs, index,'\n'); // Gets rid of labels
    while (getline(songs, index, ',') && index.size() < 8) { // && index.size() < 8
        // Parsing csv for information
        getline(songs, id, ',');
        getline(songs, name, ',');
        getline(songs, albumName, ',');
        getline(songs, albumID, ',');
        getline(songs, artistName, ',');
        getline(songs, artistID, ',');

        getline(songs, danceability, ',');
        getline(songs, energy, ',');
        getline(songs, speechiness, ',');
        getline(songs, acousticness, ',');
        getline(songs, instrumentalness, ',');
        getline(songs, valence, ',');
        getline(songs, tempo, ',');
        getline(songs, year);

        // Storing original album name and artist name before formatting.
        if (mapIDs.count(albumID) == 0) {
            mapIDs[albumID] = make_pair(albumName, artistName);
        }

        formatString(albumName);
        formatString(artistName);
        Song* newSong = new Song{name, albumID, albumName, artistName,
                                 stod(danceability),
                                 stod(energy),
                                 stod(speechiness),
                                 stod(acousticness),
                                 stod(instrumentalness),
                                 stod(valence),
                                 stod(tempo),
                                 stoi(year)};

        bTree.insertSong(newSong);
        // cout << index << ": added to tree" << endl;
        // Insert into map
    }
    // Calculates averages for artists from album averages
    bTree.rebalanceTree();
}