#ifndef PROJECT3_43_USER_H
#define PROJECT3_43_USER_H

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
    vector<Album> userPref;

public:
    User();
    void mainMenu();
    void surveyQs(int question);
    void userPrompts(int prompt);
    void displayAlbum(Album albumRec);
    void setYear(int startRange);
    void addPref(const Album& albumLike);
};

#endif //PROJECT3_43_USER_H