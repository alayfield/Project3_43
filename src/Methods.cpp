
#include "Methods.h"

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
        format.erase(remove.top());
        remove.pop();
    }

    if (format.substr(0,4) == "the ")
        format = format.substr(4, format.size() - 4);
}

string getDecade(int year) {
    if(year >= 2010) return "2010";
    string decade = to_string(year);
    decade[4] = '0';
    return decade;
}

void createDS(const string& filePath, map<string,pair<string, string>>& mapIDs, B& bTree) {
    string id, name, albumName, albumID, artistName, artistID;
    string danceability, energy, speechiness, acousticness, instrumentalness, valence, tempo, year;

    ifstream songs(filePath);
    while (getline(songs, id, ',')) {

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

        /*
        newSong->danceability = stod(danceability);
        newSong->energy = stod(energy);
        newSong->speechiness = stod(speechiness);
        newSong->acousticness = stod(acousticness);
        newSong->instrumentalness = stod(instrumentalness);
        newSong->valence = stod(valence);
        newSong->tempo = stod(tempo);
        newSong->year = stoi(year);
         */



        if (mapIDs.count(albumID) == 0) {
            mapIDs[albumID] = make_pair(albumName, artistName);
        }

        formatString(albumName);
        formatString(artistName);

        Song* newSong = new Song{name = name,
                                 albumName= albumName,
                                 artistName = artistName,
                                 stod(danceability),
                                 stod(energy),
                                 stod(speechiness),
                                 stod(acousticness),
                                 stod(instrumentalness),
                                 stod(valence),
                                 stod(tempo),
                                 stoi(year)};

        bTree.insertSong(newSong);
    }
}