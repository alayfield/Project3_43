#ifndef PROJECT3_METHODS_H
#define PROJECT3_METHODS_H

#include <stack>
#include <fstream>
#include <map>
#include <iostream>

using namespace std;

/* Includes structs to be used in both data structures
 * Will include algorithms (Euclidean distance)
 * I would recommend making separate files for the two data structures
 */

class B;

struct Song {
    string name;
    string albumID;
    string albumName;
    string artistName;
    double danceability = 0.0;
    double energy = 0.0;
    double speechiness = 0.0;
    double acousticness = 0.0;
    double instrumentalness = 0.0;
    double valence = 0.0;
    double tempo = 0.0;
    int year = 0;
};

struct Album {
    string albumID;
    string albumName;
    string artistName;
    double danceability = 0.0;
    double energy = 0.0;
    double speechiness = 0.0;
    double acousticness = 0.0;
    double instrumentalness = 0.0;
    double valence = 0.0;
    double tempo = 0.0;
    int year = 0;
};

struct Artist{
    string artistName;
    double danceability = 0.0;
    double energy = 0.0;
    double speechiness = 0.0;
    double acousticness = 0.0;
    double instrumentalness = 0.0;
    double valence = 0.0;
    double tempo = 0.0;
};

void formatString(string &format);

double findAvg(double currAvg, double currSize, double newVal);

string getDecade(int year);

void createDS(const string& filePath, map<string,pair<string, string>>& mapIDs, B& bTree);

#endif //PROJECT3_METHODS_H