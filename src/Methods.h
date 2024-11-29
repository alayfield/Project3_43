#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cctype>
#include <stack>
#include <queue>
#include <unordered_set>

using namespace std;

#ifndef PROJECT3_METHODS_H
#define PROJECT3_METHODS_H

/* Includes structs to be used in both data structures
 * Will include algorithms (Euclidean distance)
 * I would recommend making separate files for the two data structures
 */

struct Song {
    string name;
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
    string name;
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
    string artistID;
    double danceability = 0.0;
    double energy = 0.0;
    double speechiness = 0.0;
    double acousticness = 0.0;
    double instrumentalness = 0.0;
    double valence = 0.0;
    double tempo = 0.0;
};

void formatString(string &format);

string getDecade(int year);

#endif //PROJECT3_METHODS_H