//
// Created by Adrian Layfield on 11/13/24.
//
#include <string>

using namespace std;

#ifndef PROJECT3_METHODS_H
#define PROJECT3_METHODS_H

struct Song {
    string id;
    double danceability;
    double energy;
    double loudness;
    double speechiness;
    double acousticness;
    double instrumentalness;
    double liveness;
    double valence;
    double tempo;
    int year;
};

struct Album {
    string name;
    string id;
    double danceability;
    double energy;
    double loudness;
    double speechiness;
    double acousticness;
    double instrumentalness;
    double liveness;
    double valence;
    double tempo;
    int year;

    vector<Song> songs;
};

struct Artist{
    string name;
    string id;
    double danceability;
    double energy;
    double loudness;
    double speechiness;
    double acousticness;
    double instrumentalness;
    double liveness;
    double valence;
    double tempo;

    vector<Album> albums;
};
#endif //PROJECT3_METHODS_H
