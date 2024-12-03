#pragma once
#include "Methods.h"
#include "User.h"
#include "B.h"
#include <time.h>
#include <iostream>

/* 1. Timing document:
 * https://www.ibm.com/docs/en/rdfi/9.6.0?topic=functions-clock-determine-processor-time
 */

int main() {
    // Build data structures
    double totalTime, treeTime, mapTime;
    map<string, pair<string, string>> mapIDs;
    pair<string, string> foundNames;
    B bDS;
    // Map mapDS;
    User RankedRecords;
    string input;
    bool survey = false;

    // Adrian's Path: "/Users/adrian/Documents/COP3530/Project3_43/csv/cleaned_tracks.csv"

    createDS("csv/cleaned_tracks.csv", mapIDs, bDS);

    while(true) {
        RankedRecords.mainMenu(survey);
        getline(cin, input);

        if (input == "1" && !survey) {
            bool year = false;
            bool pref = false;
            bool yn = false;
            string album;
            string artist;
            Album* treeAlbum;
            Album* mapAlbum;
            Album* albumLike;

            RankedRecords.surveyQs(1);
            while(!year) {
                getline(cin, input);
                year = true;

                if (toupper(input[0]) == 'A') RankedRecords.setYear(1960);
                else if (toupper(input[0]) == 'B') RankedRecords.setYear(1970);
                else if (toupper(input[0]) == 'C') RankedRecords.setYear(1980);
                else if (toupper(input[0]) == 'D') RankedRecords.setYear(1990);
                else if (toupper(input[0]) == 'E') RankedRecords.setYear(2000);
                else if (toupper(input[0]) == 'F') RankedRecords.setYear(2010);
                else {
                    RankedRecords.userPrompts(3);
                    year = false;
                }
            }

            RankedRecords.surveyQs(2);
            RankedRecords.userPrompts(1);
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
                if (RankedRecords.getPrefNum() == 0) RankedRecords.userPrompts(4);
                else {
                    RankedRecords.surveyQs(3);
                    while (!yn) {
                        getline(cin, input);
                        if (input == "N" || input == "No" || input == "n" || input == "no") {
                            pref = true;
                            yn = true;
                        }
                        else if (input == "Y" || input == "Yes" || input == "y" || input == "yes") {
                            yn = true;
                        }
                        else RankedRecords.userPrompts(3);
                    }
                }
            }
            cout << "\nSurvey complete! Finding album..." << endl;
            totalTime = double(clock()); // 1
            treeAlbum = bDS.euclidDist(to_string(RankedRecords.getYear()),RankedRecords.getData());
            treeTime = double(clock()) - totalTime;
            // Find album in map
            mapTime = double(clock()) - totalTime - treeTime;

            foundNames = mapIDs[treeAlbum->albumID];
            RankedRecords.displayAlbum(treeAlbum, foundNames);
            cout << "\nTime to find in tree: " << treeTime << endl;
            cout << "Time to find in map: " << mapTime << endl;

            survey = true;
        }

        else if (input == "2") {
            RankedRecords.displayMethod();
        }

        else if (input == "3") {
            return 0;
        }

        else {
            RankedRecords.userPrompts(3);
        }
    }
}
