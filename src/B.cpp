#include <queue>
#include "B.h"
#include "Methods.h"

using namespace std;

B::B() {
    root = new treeNode("root");
    root->children.push_back(new treeNode("1960"));
    root->children.push_back(new treeNode("1970"));
    root->children.push_back(new treeNode("1980"));
    root->children.push_back(new treeNode("1990"));
    root->children.push_back(new treeNode("2000"));
    root->children.push_back(new treeNode("2010"));
}

B::~B() {
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
    string decade = getDecade(songNode->year);
    treeNode* decadeNode = findChild(root, decade); //find decade node if already exists
    if(!decadeNode) return; //if decade not found, exit function

    treeNode* artistNode = findChild(decadeNode, songNode->artistName); //find artist node if already exists
    if(!artistNode) { //if no node for the artist exists, create a new artist structure and add node
        Artist* tempArtist = new Artist;
        tempArtist->artistName = songNode->artistName;
        artistNode = new treeNode(tempArtist->artistName, tempArtist);
        decadeNode->children.push_back(artistNode);
        cout << "created artist " << tempArtist->artistName << endl;
    }

    treeNode* albumNode = findChild(artistNode, songNode->albumName); //find album node if already exits
    if(!albumNode) { //if no node for the album exists, create a new artist structure and add node
        Album* tempAlbum = new Album;
        tempAlbum->albumID = songNode->albumID;
        tempAlbum->albumName = songNode->albumName;
        tempAlbum->artistName = songNode->artistName;
        tempAlbum->year = songNode->year;
        albumNode = new treeNode(tempAlbum->albumName, tempAlbum);
        artistNode->children.push_back(albumNode);
        cout << "created album " << tempAlbum->albumName << endl;
    }
    
    albumNode->children.push_back(new treeNode(songNode->name, songNode)); //add the song to the album node's children
    rebalanceAlbum(albumNode, songNode);
}

void B::rebalanceTree() {
    for (auto decade : root->children) {
        rebalanceDecade(decade);
    }
}

void B::rebalanceDecade(treeNode* decade) {
    if(!decade) return; //if node doesnt exist, exit to avoid segfault
    for (auto artist : decade->children) {
        rebalanceArtist(artist);
    }
}

void B::rebalanceAlbum(treeNode* albumNode, Song* song) {
    Album* albumVal = albumNode->album;

    albumVal->danceability = findAvg(albumVal->danceability, double(albumNode->children.size()), song->danceability);
    albumVal->energy = findAvg(albumVal->energy, double(albumNode->children.size()), song->energy);
    albumVal->speechiness = findAvg(albumVal->speechiness, double(albumNode->children.size()), song->speechiness);
    albumVal->acousticness = findAvg(albumVal->acousticness, double(albumNode->children.size()), song->acousticness);
    albumVal->instrumentalness = findAvg(albumVal->instrumentalness, double(albumNode->children.size()), song->instrumentalness);
    albumVal->valence = findAvg(albumVal->valence, double(albumNode->children.size()), song->valence);
    albumVal->tempo = findAvg(albumVal->tempo, double(albumNode->children.size()), song->tempo);
}

void B::rebalanceArtist(treeNode* artistNode) {
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

Album* B::searchAlbum(string decade, string artistName, string albumName) {
    treeNode* decadeNode = findChild(root, decade); //find decade node if already exists
    if(!decadeNode) {
        cout << "decade not found" << endl;
        return nullptr; //if decade not found, exit function
    }

    treeNode* artistNode = findChild(decadeNode, artistName); //find artist node if already exists
    if(!artistNode) {
        cout << "artist not found" << endl;
        return nullptr; //if no node for the artist exists, exit function
    }

    treeNode* albumNode = findChild(artistNode, albumName); //find album node, or nullptr if doesnt exist
    return albumNode->album;
}

treeNode* B::findChild(treeNode* source, string name) {
    for(treeNode* curr : source->children) { //traverse to if child exists and return if found
        if (curr->name == name) {
            return curr;
        }
    }
    return nullptr; //return nullptr if child does not exist in tree
}

Album* B::euclidDist(string decade, vector<double> userVals) {
    double x1, x2, x3, x4, x5, x6, x7;
    double minED = 999999999;
    double currED = 0;
    treeNode* bestArtist = nullptr;
    Album* bestAlbum = nullptr;
    treeNode* decadeNode = findChild(root, decade);

    for (auto artist : decadeNode->children) {
        x1 = pow(artist->artist->danceability - userVals[0], 2);
        x2 = pow(artist->artist->energy - userVals[1], 2);
        x3 = pow(artist->artist->speechiness - userVals[2], 2);
        x4 = pow(artist->artist->acousticness - userVals[3], 2);
        x5 = pow(artist->artist->instrumentalness - userVals[4], 2);
        x6 = pow(artist->artist->valence - userVals[5], 2);
        //x7 = pow(artist->artist->tempo - userVals[6], 2);

        currED = sqrt(x1 + x2+ x3 + x4 + x5 + x6);
        if (currED < minED) bestArtist = artist;
    }

    for (auto album : bestArtist->children) {
        x1 = pow(album->album->danceability - userVals[0], 2);
        x2 = pow(album->album->energy - userVals[1], 2);
        x3 = pow(album->album->speechiness - userVals[2], 2);
        x4 = pow(album->album->acousticness - userVals[3], 2);
        x5 = pow(album->album->instrumentalness - userVals[4], 2);
        x6 = pow(album->album->valence - userVals[5], 2);
        //x7 = pow(album->album->tempo - userVals[6], 2);

        currED = sqrt(x1 + x2+ x3 + x4 + x5 + x6);
        if (currED < minED) bestAlbum = album->album;
    }
    return bestAlbum;
};