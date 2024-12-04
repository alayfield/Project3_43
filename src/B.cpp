#include <queue>
#include "B.h"

using namespace std;

B::B() {
    /* Initializes each decade in tree */
    root = new treeNode("root");
    root->children.push_back(new treeNode("1960"));
    root->children.push_back(new treeNode("1970"));
    root->children.push_back(new treeNode("1980"));
    root->children.push_back(new treeNode("1990"));
    root->children.push_back(new treeNode("2000"));
    root->children.push_back(new treeNode("2010"));
}

B::~B() {
    /* Destructor, deletes all pointers */
    queue<treeNode*> q;
    q.push(root);
    while(!q.empty()) {
        treeNode* temp = q.front();
        q.pop();
        for(treeNode* curr : q.front()->children) {
            q.push(curr);
        }
        delete temp;
    }
}

void B::insertSong(Song* songNode) {
    /* Insert song under respective decade, artist, and album.
     * If artist or album does not exist, create new node.
     * Calculates new average values of album.
     */
    string decade = getDecade(songNode->year);
    treeNode* decadeNode = findChild(root, decade); // Find decade node if it exists
    if(!decadeNode) return;                                       // If decade not found, exit function

    treeNode* artistNode = findChild(decadeNode, songNode->artistName); // Find artist node if it exists

    // If no node for the artist exists, create a new artist structure and add node
    if(!artistNode) {
        Artist* tempArtist = new Artist;
        tempArtist->artistName = songNode->artistName;
        artistNode = new treeNode(tempArtist->artistName, tempArtist);
        decadeNode->children.push_back(artistNode);
        cout << "created artist " << tempArtist->artistName << endl;
    }

    treeNode* albumNode = findChild(artistNode, songNode->albumName); // Find album node if it exits

    //if no node for the album exists, create a new artist structure and add node
    if(!albumNode) {
        Album* tempAlbum = new Album;
        tempAlbum->albumID = songNode->albumID;
        tempAlbum->albumName = songNode->albumName;
        tempAlbum->artistName = songNode->artistName;
        tempAlbum->year = songNode->year;
        albumNode = new treeNode(tempAlbum->albumName, tempAlbum);
        artistNode->children.push_back(albumNode);
        cout << "created album " << tempAlbum->albumName << tempAlbum->year << endl;
    }
    
    albumNode->children.push_back(new treeNode(songNode->name, songNode)); // Add song to the album node's children
    rebalanceAlbum(albumNode, songNode);
}

void B::rebalanceTree() {
    /* Public function called to update averages for all artist nodes in tree */
    for (auto decade : root->children) {
        rebalanceDecade(decade);
    }
}

void B::rebalanceDecade(treeNode* decade) {
    /* Called to iterate through all artists of decade to rebalance */
    if(!decade) return;
    for (auto artist : decade->children) {
        rebalanceArtist(artist);
    }
}

void B::rebalanceArtist(treeNode* artistNode) {
    /* Iterates through all of artist's albums to calculate averages for artist's values */
    Artist* artistVal = artistNode->artist;
    auto size = double(artistNode->children.size());
    for(treeNode* child : artistNode->children) {
        artistVal->danceability += child->album->danceability;
        artistVal->energy += child->album->energy;
        artistVal->speechiness += child->album->speechiness;
        artistVal->acousticness += child->album->acousticness;
        artistVal->instrumentalness += child->album->instrumentalness;
        artistVal->valence += child->album->valence;
        artistVal->tempo += child->album->tempo;
    }
    artistVal->danceability /= size;
    artistVal->energy /= size;
    artistVal->speechiness /= size;
    artistVal->acousticness /= size;
    artistVal->instrumentalness /= size;
    artistVal->valence /= size;
    artistVal->tempo /= size;
}

void B::rebalanceAlbum(treeNode* albumNode, Song* song) {
    /* Updates average values of songs for album values; this is done when each song is added */
    Album* albumVal = albumNode->album;

    albumVal->danceability = findAvg(albumVal->danceability, double(albumNode->children.size()), song->danceability);
    albumVal->energy = findAvg(albumVal->energy, double(albumNode->children.size()), song->energy);
    albumVal->speechiness = findAvg(albumVal->speechiness, double(albumNode->children.size()), song->speechiness);
    albumVal->acousticness = findAvg(albumVal->acousticness, double(albumNode->children.size()), song->acousticness);
    albumVal->instrumentalness = findAvg(albumVal->instrumentalness, double(albumNode->children.size()), song->instrumentalness);
    albumVal->valence = findAvg(albumVal->valence, double(albumNode->children.size()), song->valence);
    albumVal->tempo = findAvg(albumVal->tempo, double(albumNode->children.size()), song->tempo);
}

Album* B::searchAlbum(string decade, string artistName, string albumName) {
    /* Searches tree for specified album (based on string) */
    treeNode* decadeNode = findChild(root, decade);    // Find decade node if it exists
    if(!decadeNode) return nullptr;                                 // If decade not found, exit function

    // Find artist node if it exists
    treeNode* artistNode = findChild(decadeNode, artistName);
    if(!artistNode) return nullptr; // If artist not found, exit function

    // Find album node, or nullptr if doesn't exist
    treeNode* albumNode = findChild(artistNode, albumName);
    return albumNode->album;
}

treeNode* B::findChild(treeNode* source, string name) {
    /* Searches through node's children to find specific child */
    for(treeNode* curr : source->children) {
        if (curr->name == name) {
            return curr;
        }
    }
    return nullptr; //return nullptr if child does not exist
}

Album* B::euclidDist(string decade, vector<double> userVals) {
    /* Traverses entire decade subtree to find similar album based on Euclidean distance.
     * First finds most similar artist to user preference, then most similar album of that artist.
     */
    double x1, x2, x3, x4, x5, x6, x7;
    double minED = 999999999;
    double currED = 0;
    treeNode *bestArtist = nullptr;
    Album *bestAlbum = nullptr;
    treeNode *decadeNode = findChild(root, decade);

    // Traversing through all artists under decade and calculates Euclidean distance
    for (auto artist: decadeNode->children) {
        x1 = pow(artist->artist->danceability - userVals[0], 2);
        x2 = pow(artist->artist->energy - userVals[1], 2);
        x3 = pow(artist->artist->speechiness - userVals[2], 2);
        x4 = pow(artist->artist->acousticness - userVals[3], 2);
        x5 = pow(artist->artist->instrumentalness - userVals[4], 2);
        x6 = pow(artist->artist->valence - userVals[5], 2);

        currED = sqrt(x1 + x2 + x3 + x4 + x5 + x6);
        if (currED < minED) {
            bestArtist = artist; // Artist with the smallest Euclidean distance saved
            minED = currED;
        }
    }

    minED = 999999999;
    currED = 0;

    // Traversing through all albums under most similar artists and calculates Euclidean distance
    for (auto album: bestArtist->children) {
        x1 = pow(album->album->danceability - userVals[0], 2);
        x2 = pow(album->album->energy - userVals[1], 2);
        x3 = pow(album->album->speechiness - userVals[2], 2);
        x4 = pow(album->album->acousticness - userVals[3], 2);
        x5 = pow(album->album->instrumentalness - userVals[4], 2);
        x6 = pow(album->album->valence - userVals[5], 2);

        currED = sqrt(x1 + x2 + x3 + x4 + x5 + x6);
        if (currED < minED) {
            bestAlbum = album->album; // Album with the smallest Euclidean distance saved and returned
            minED = currED;
        }
    }
    return bestAlbum;
}