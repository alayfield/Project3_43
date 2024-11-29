#include "User.h"

User::User() {
    danceability = 0;
    energy = 0;
    speechiness = 0;
    acousticness = 0;
    instrumentalness = 0;
    valence = 0;
    tempo = 0;
}

void User::mainMenu() {
    cout << "Welcome to Ranked Records!\n" << endl;
    cout << "1. Take a survey and find an album.\n"
            "2. Learn more about our method.\n"
            "3. Quit" << endl;
}

void User::surveyQs(int question) {
    if (question == 1) {
        cout << "What decade do you prefer to listen to?\n" << endl;
        cout << "A. 1960s: 1960-1969\n"
                "B. 1970s: 1970-1979\n"
                "C. 1980s: 1980-1989\n"
                "D. 1990s: 1990-1999\n"
                "E. 2000s: 2000-2009\n"
                "F. 2010s: 2010-Present\n" << endl;
        cout << "Please input the associated letter (A-F)" << endl;
    }
    if (question == 2) {
        cout << "What is your favorite album from this decade?" << endl;
    }
    if (question == 3) {
        cout << "Would you like to add another favorite? (Y/N)\n" << endl;
    }
}

void User::userPrompts(int prompt) {
    if (prompt == 1) {
        cout << "Make sure you use the correct spelling" << endl;
    }
    if (prompt == 2) {
        cout << "Please input the associated number (1-3)" << endl;
    }
    if (prompt == 3) {
        cout << "Invalid input, please try again" << endl;
    }
    if (prompt == 4) {
        cout << "Please add another album" << endl;
    }
}

void User::displayAlbum(const Album& albumRec) const {
    cout << "Album Found!\n" << endl;
    cout << albumRec.name << ", " << albumRec.year;
    cout << "by " << albumRec.artistName << endl;
    cout << "\n";

    cout << "Relevant Stats  | Album Stats    | User Preference" << endl; // 16 characters between "|"
    cout << "--------------------------------------------------" << endl;
    cout << setprecision(4);
    cout << "danceability    | " << albumRec.danceability << "         | " << danceability << endl;
    cout << "energy          | " <<  albumRec.energy << "         | " << energy << endl;
    cout << "speechiness     | " <<  albumRec.speechiness << "         | " << speechiness << endl;
    cout << "acousticness    | " <<  albumRec.acousticness << "         | " << acousticness << endl;
    cout << "instumentalness | " <<  albumRec.instrumentalness << "         | " << instrumentalness << endl;
    cout << "valence         | " <<  albumRec.valence << "         | " << valence << endl;
    cout << "tempo           | " <<  albumRec.tempo << "         | " << tempo << endl;
}

void User::setYear(int startRange) {
    year = startRange;
}

void User::addPref(const Album& albumLike) {
    userPref.emplace_back(albumLike);
    auto numLiked = double(userPref.size());

    danceability = (danceability*(numLiked - 1) + albumLike.danceability) / numLiked;
    energy = (energy*(numLiked - 1) + albumLike.energy) / numLiked;
    speechiness = (speechiness*(numLiked - 1) + albumLike.speechiness) / numLiked;
    acousticness = (acousticness*(numLiked - 1) + albumLike.acousticness) / numLiked;
    instrumentalness = (instrumentalness*(numLiked - 1) + albumLike.instrumentalness) / numLiked;
    valence = (valence*(numLiked - 1) + albumLike.valence) / numLiked;
    tempo = (tempo*(numLiked - 1) + albumLike.tempo) / numLiked;
}

int User::getPrefNum() {
    return int(userPref.size());
}
