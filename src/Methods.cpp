#include "Methods.h"
#include "B.h"

using namespace std;

/* 1. Alphanumeric/Space/Lowercase:
 * https://cplusplus.com/reference/cctype/
 */

void formatString (string &format) {
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
    return (currAvg*currSize + newVal) / (currSize+1);
}

string getDecade(int year) {
    if(year >= 2010) return "2010";
    year = year - year % 10;
    string decade = to_string(year);
    return decade;
}

void createDS(const string& filePath, map<string,pair<string, string>>& mapIDs, B& bTree) {
    string index, id, name, albumName, albumID, artistName, artistID;
    string danceability, energy, speechiness, acousticness, instrumentalness, valence, tempo, year;

    ifstream songs(filePath);
    getline(songs, index,'\n'); // Gets rid of labels
    while (getline(songs, index, ',') && index.size() < 8) { // && index.size() < 8
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
        cout << index << ": added to tree" << endl;
        // Insert into map
    }
    bTree.rebalanceTree();
}