#ifndef PROJECT3_43_USER_H
#define PROJECT3_43_USER_H

#include <iostream>
#include <iomanip>
#include <string>
#include "Methods.h"

// For each session. This stores user preferences and contains prompts/the menu
class User {
private:
    double danceability;
    double energy;
    double speechiness;
    double acousticness;
    double instrumentalness;
    double valence;
    double tempo;
    int year;
    vector<Album*> userPref;

public:
    User();
    static void mainMenu();
    static void surveyQs(int question);
    static void userPrompts(int prompt);
    void displayAlbum(const Album& albumRec) const;
    void setYear(int startRange);
    void addPref(Album* albumLike);
    int getPrefNum();
    int getYear();

    template <typename T>
    double euclidDist(T* compared);
};

#endif //PROJECT3_43_USER_H