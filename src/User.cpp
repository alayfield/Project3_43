#include "User.h"

/* 1. Spotify track values information:
 * https://rpubs.com/PeterDola/SpotifyTracks
 * 2. Set precision and trailing zeros:
 * https://stackoverflow.com/questions/17341870/correct-use-of-stdcout-precision-not-printing-trailing-zeros
 */
User::User() {
    danceability = 0;
    energy = 0;
    speechiness = 0;
    acousticness = 0;
    instrumentalness = 0;
    valence = 0;
    tempo = 0;
    cout << "Welcome to Ranked Records!" << endl;
}

void User::mainMenu(bool completed) {
    /* Prints main menu options */
    if (completed) {
        cout << "\n   --- Survey Complete ---\n"
                "2. Learn more about our method.\n"
                "3. Quit" << endl;
    }
    else {
        cout << "\n1. Take a survey and find an album.\n"
                "2. Learn more about our method.\n"
                "3. Quit" << endl;
    }
}

void User::surveyQs(int question) {
    /* Prints the 3 survey questions */
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
        cout << "\nWhat is your favorite album from this decade?" << endl;
    }
    if (question == 3) {
        cout << "\nWould you like to add another favorite? (Y/N)" << endl;
    }
}

void User::displayMethod() { // 1
    /* Prints information on the data and how we find with album recommendation */
    cout << "Our data base is comprised of 850,000+ songs making up over 68,000 albums released between 1960 and 2021.\n"
            "We classify albums as being 30 minutes in length or longer with the work not having more than one artist.\n"
            "\n"
            "In order to classify and compare albums, the year of release and 7 quantitative variables are considered;\n"
            "danceability, energy, speechless, acousticness, instrumentalness, valence, and tempo. Individual songs hold\n"
            "values unique to that track, album values are the averages of the track values, and artist values are the \n"
            "averages of the album values.\n"
            "\n"
            "When you are asked in the survey about your favorite albums, we are getting a sense of your taste and \n"
            "finding something similar. Specifically, we are using the Euclidean distance algorithm.\n"
            "\n"
            "Learn more about Euclidean distance:\n"
            "https://www.geeksforgeeks.org/euclidean-distance/\n"
            "\n"
            "Understanding Spotify track data:\n"
            "  -  Danceability: A number between 0 and 1 to indicate whether a song would be good for dancing. This is \n"
            "     based on tempo, rhythm stability, beat strength, and regularity.\n"
            "  -  Energy: This is a number between 0 and 1 that measures track intensity, with values closer to 1 \n"
            "     indicating the track is fast, loud, and noisy. \n"
            "  -  Speechiness: This detects speech on a track. This ranges between 0 and 1, but most songs will have a \n"
            "     score below 0.33. Rap music will likely have a score between 0.33 and 0.66.\n"
            "  -  Acousticness: A number between 0 and 1 to indicate whether a song is acoustic, with values closer to 1 \n"
            "     indicating high chance that  the track is acoustic.\n"
            "  -  Instrumentalness: A number between 0 and 1 to indicate if a track contains vocals. A value of 0.5 and \n"
            "     higher indicates the track likely does not have vocals.\n"
            "  -  Valence: This indicated the mood of the track. This is a number between 0 and 1 with a higher score \n"
            "     indicating that the track has a positive mood.\n"
            "  -  Tempo: This is the beats per minute (BPM). This is not used in the Euclidean distance calculation.\n"
            "\n"
            "Information from https://rpubs.com/PeterDola/SpotifyTracks" << endl;
}

void User::userPrompts(int prompt) {
    /* Misc. user prompts */
    if (prompt == 1) {
        cout << "Make sure you use the correct spelling" << endl;
    }
    if (prompt == 2) {
        cout << "Please add another album" << endl;
    }
    if (prompt == 3) {
        cout << "Invalid input, please try again" << endl;
    }
}

void User::displayAlbum(Album* albumRec, const pair<string, string>& names) const {
    /* Displays album information.
     * Compares album quantifiable data to user data from survey.
     * Links to album on Spotify.
     */
    cout << "Album Found!\n" << endl;
    cout << names.first << ", " << albumRec->year << endl;
    cout << "by " << names.second << endl;
    cout << "\n";

    cout << "Relevant Stats  | Album Stats    | User Preference" << endl; // 16 characters between "|"
    cout << "--------------------------------------------------" << endl;
    cout << fixed << setprecision(4); // 2
    cout << "danceability    | " << albumRec->danceability << "         | " << danceability << endl;
    cout << "energy          | " <<  albumRec->energy << "         | " << energy << endl;
    cout << "speechiness     | " <<  albumRec->speechiness << "         | " << speechiness << endl;
    cout << "acousticness    | " <<  albumRec->acousticness << "         | " << acousticness << endl;
    cout << "instrumentalness| " <<  albumRec->instrumentalness << "         | " << instrumentalness << endl;
    cout << "valence         | " <<  albumRec->valence << "         | " << valence << endl;
    cout << setprecision(2);
    cout << "tempo           | " <<  albumRec->tempo << "         | " << tempo << endl;

    cout << "\nSpotify link:" << endl;
    cout << "https://open.spotify.com/album/" << albumRec->albumID.substr(1, 22) << endl;
}

void User::setYear(int startRange) {
    /* Sets decade user prefers to listen to */
    year = startRange;
}

void User::addPref(Album* albumLike) {
    /* After finding album in data structure, updates average user preference.
     * Adds user preference to preference vector.
     */
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
    /* Returns how many valid albums user inputted */
    return int(userPref.size());
}

int User::getYear() {
    /* Returns decade preference */
    return year;
}

vector<double> User::getData() {
    /* Returns vector with average values of quantifiable album features. */
    return {danceability, energy, speechiness, acousticness, instrumentalness, valence, tempo};
}