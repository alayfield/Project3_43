#pragma once
#include "Methods.h"
#include "User.h"
#include "B.h"
#include <time.h>
#include <iostream>

/* 1. Timing document:
 * https://www.ibm.com/docs/en/rdfi/9.6.0?topic=functions-clock-determine-processor-time
 * 2. Time in milliseconds:
 * https://stackoverflow.com/questions/361363/how-to-measure-time-in-milliseconds-using-ansi-c
 * 3. To upper:
 * https://cplusplus.com/reference/cctype/toupper/
 * 4. Clang-Tidy recommendation
 */

int main() {
    // Build data structure
    double totalTime, euclidTime, mahaTime;
    map<string, pair<string, string>> mapIDs;
    pair<string, string> foundNames1;
    pair<string, string> foundNames2;
    B bDS;
    User RankedRecords;
    string input;
    bool survey = false;

    createDS("../csv/cleaned_tracks.csv", mapIDs, bDS);
    vector<vector<double>> covMatrix = readCov("../csv/cov_matrix.csv");

    while(true) {
        User::mainMenu(survey); // 4
        getline(cin, input);

        if (input == "1") {
            if (survey) {
                RankedRecords.resetPref();
            }

            bool year = false;
            bool pref = false;
            bool yn;
            string album;
            string artist;
            Album* euclidAlbum;
            Album* mahaAlbum;
            Album* albumLike;

            User::surveyQs(1); // 4
            while(!year) {
                getline(cin, input);
                year = true;

                if (toupper(input[0]) == 'A') RankedRecords.setYear(1960);      // 3
                else if (toupper(input[0]) == 'B') RankedRecords.setYear(1970);
                else if (toupper(input[0]) == 'C') RankedRecords.setYear(1980);
                else if (toupper(input[0]) == 'D') RankedRecords.setYear(1990);
                else if (toupper(input[0]) == 'E') RankedRecords.setYear(2000);
                else if (toupper(input[0]) == 'F') RankedRecords.setYear(2010);
                else {
                    User::userPrompts(3); // 4
                    year = false;
                }
            }

            User::surveyQs(2);  // 4
            User::userPrompts(1);
            while(!pref) {
                cout << "Album name: ";
                getline(cin, album,'\n');
                formatString(album);

                cout << "Artist name: ";
                getline(cin, artist, '\n');
                formatString(artist);

                // Find album inputted
                albumLike = bDS.searchAlbum(to_string(RankedRecords.getYear()), artist, album);

                if (albumLike != nullptr) RankedRecords.addPref(albumLike);
                if (albumLike == nullptr) cout << "\nAlbum not found." << endl;
                if (RankedRecords.getPrefNum() == 0) User::userPrompts(2); // 4
                else {
                    User::surveyQs(3); // 4
                    yn = false;
                    while (!yn) {
                        getline(cin, input);
                        if (input == "N" || input == "No" || input == "n" || input == "no") {
                            pref = true;
                            yn = true;
                        }
                        else if (input == "Y" || input == "Yes" || input == "y" || input == "yes") {
                            yn = true;
                        }
                        else User::userPrompts(3); // 4
                    }
                }
            }
            cout << "\nSurvey complete! Finding album..." << endl;

            totalTime = double(clock()); // 1
            euclidAlbum = bDS.euclidDist(to_string(RankedRecords.getYear()),RankedRecords.getData());
            euclidTime = double(clock()) - totalTime;
            mahaAlbum = bDS.mahaDist(to_string(RankedRecords.getYear()),RankedRecords.getData(), covMatrix);
            mahaTime = double(clock()) - totalTime - euclidTime;

            foundNames1 = mapIDs[euclidAlbum->albumID];
            foundNames2 = mapIDs[mahaAlbum->albumID];
            RankedRecords.displayAlbum(euclidAlbum, mahaAlbum, foundNames1, foundNames2);
            cout << "\nTime to find Euclidean distance:   " << euclidTime * 1000 / (CLOCKS_PER_SEC) << " ms" << endl; // 3
            cout << "Time to find Mahalanobis distance: " << mahaTime * 1000 / (CLOCKS_PER_SEC) << " ms" << endl;
            RankedRecords.displayComparison(euclidAlbum, mahaAlbum);

            survey = true;
        }

        else if (input == "2") { // Display more information on what Ranked Records is doing
            User::displayMethod(); // 4
        }

        else if (input == "3") { // Exit
            return 0;
        }

        else { // Invalid entry, prompts to try again
            User::userPrompts(3); // 4
        }
    }
}
