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
    static void mainMenu(bool completed);
    static void surveyQs(int question);
    static void displayMethod();
    static void userPrompts(int prompt);
    void displayAlbum(Album* albumRec, const pair<string, string>& names) const;
    void setYear(int startRange);
    void addPref(Album* albumLike);
    int getPrefNum();
    int getYear();
    vector<double> getData();
};

#endif //PROJECT3_43_USER_H