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
    B bDS;
    // Map mapDS;
    User RankedRecords;
    string input;

    // Adrian's Path: "/Users/adrian/Documents/COP3530/Project3_43/csv/cleaned_tracks.csv"

    createDS("csv/cleaned_tracks.csv", mapIDs, bDS);

    while(true) {
        RankedRecords.mainMenu();
        getline(cin, input);

        if (input == "1") {
            bool year = false;
            bool pref = false;
            bool yn = false;
            string album;
            string artist;
            Album* treeAlbum;
            Album* mapAlbum;

            RankedRecords.surveyQs(1);
            while(!year) {
                getline(cin, input);
                year = true;

                if (input == "A") RankedRecords.setYear(1960);
                else if (input == "B") RankedRecords.setYear(1970);
                else if (input == "C") RankedRecords.setYear(1980);
                else if (input == "D") RankedRecords.setYear(1990);
                else if (input == "E") RankedRecords.setYear(2000);
                else if (input == "F") RankedRecords.setYear(2010);
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
                // Find album they inputted
                // RankedRecords.addPref(treeAlbum/mapAlbum)
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
            cout << "Survey complete! Finding album..." << endl;
            totalTime = double(clock()); // 1
            // Find album in tree
            treeTime = double(clock()) - totalTime;
            // Find album in map
            mapTime = double(clock()) - totalTime - treeTime;

            //RankedRecords.displayAlbum(treeAlbum/mapAlbum)
            cout << "Time to find in tree: " << treeTime << endl;
            cout << "Time to find in map: " << mapTime << endl;
        }

        if (input == "2") {
            // Return information on Spotify stats
        }

        if (input == "3") {
            return 0;
        }
    }
}
