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

void User::addPref(Album* albumLike) {
    auto numLiked = double(userPref.size());

    danceability = findAvg(danceability, numLiked,albumLike->danceability);
    energy = findAvg(energy, numLiked,albumLike->energy);
    speechiness = findAvg(speechiness, numLiked,albumLike->speechiness);
    acousticness = findAvg(acousticness, numLiked,albumLike->acousticness);
    instrumentalness = findAvg(instrumentalness, numLiked,albumLike->instrumentalness);
    valence = findAvg(valence, numLiked,albumLike->valence);
    tempo = findAvg(tempo, numLiked,albumLike->tempo);

    userPref.emplace_back(albumLike);
}

int User::getPrefNum() {
    return int(userPref.size());
}

int User::getYear() {
    return year;
}

template<typename T>
double User::euclidDist(T *compare) {
    double x1 = (danceability - compare->danceability)^2;
    double x2 = (energy - compare->energy)^2;
    double x3 = (speechiness - compare->speechiness)^2;
    double x4 = (acousticness - compare->acousticness)^2;
    double x5 = (instrumentalness - compare->instrumentalness)^2;
    double x6 = (valence - compare->valence)^2;
    double x7 = (tempo - compare->tempo)^2;

    return sqrt(x1 + x2+ x3 + x4 + x5 + x6 + x7);
}
