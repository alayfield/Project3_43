#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

#ifndef PROJECT3_METHODS_H
#define PROJECT3_METHODS_H

/* Includes structs to be used in both data structures
 * Will include algorithms (Euclidean distance)
 * I would recommend making separate files for the two data structures
 */

struct Song {
    double danceability;
    double energy;
    double speechiness;
    double acousticness;
    double instrumentalness;
    double valence;
    double tempo;
    int year;
};

struct Album {
    string name;
    string artistName;
    double danceability;
    double energy;
    double speechiness;
    double acousticness;
    double instrumentalness;
    double valence;
    double tempo;
    int year;

    vector<Song> songs;
};

struct Artist{
    string artistName;
    string artistID;
    double danceability;
    double energy;
    double speechiness;
    double acousticness;
    double instrumentalness;
    double valence;
    double tempo;

    vector<Album> albums;
};

#endif //PROJECT3_METHODS_H