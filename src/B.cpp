#include <queue>
#include "B.h"
#include "Methods.h"

using namespace std;

B::B() {
    root = new Node("root");
    root->children.push_back(new Node("1960"));
    root->children.push_back(new Node("1970"));
    root->children.push_back(new Node("1980"));
    root->children.push_back(new Node("1990"));
    root->children.push_back(new Node("2000"));
    root->children.push_back(new Node("2010"));
}

B::~B() {
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        Node* temp = q.front();
        q.pop();
        for(Node* curr : q.front()->children) {
            q.push(curr);
        }
        delete temp;
    }
}

void B::insertSong(Song* songNode) {
    string decade = getDecade(songNode->year);
    Node* subtree = nullptr;
    for(Node* curr : root->children) { //traverse to proper decade node and save as subtree
        if(curr->name == decade) {
            subtree = curr;
        }
    }
    if(!subtree) return; //if decade not found, exit function

    Node* artistNode = nullptr;
    for(Node* curr : subtree->children) { //traverse to find if node for artist already exists
        if(curr->name == songNode->artistName) {
            artistNode = curr;
        }
    }
    if(!artistNode) { //if no node for the artist exists, create a new artist structure and add node
        Artist* tempArtist = new Artist;
        tempArtist->artistName = songNode->artistName;
        artistNode = new Node(tempArtist->artistName, tempArtist);
        subtree->children.push_back(artistNode);
    }

    Node* albumNode = nullptr;
    for(Node* curr : artistNode->children) { //traverse to find if node for album already exists
        if(curr->name == songNode->albumName) {
            albumNode = curr;
        }
    }
    if(!albumNode) { //if no node for the album exists, create a new artist structure and add node
        Album* tempAlbum = new Album;
        tempAlbum->name = songNode->albumName;
        tempAlbum->artistName = songNode->artistName;
        tempAlbum->year = songNode->year;
        albumNode = new Node(tempAlbum->artistName, tempAlbum);
        subtree->children.push_back(albumNode);
    }
    
    albumNode->children.push_back(new Node(songNode->name, songNode)); //add the song to the album node's children

    rebalanceAlbum(albumNode, songNode); //update the average values of all songs in the album
    rebalanceArtist(artistNode, albumNode->album); //update the average values of all albums from the artist
}

void B::rebalanceAlbum(Node* albumNode, Song* song) {
    Album* newAlbum = new Album;
    Album* temp = albumNode->album;

    newAlbum->danceability = (temp->danceability*(albumNode->children.size()) + song->danceability) / albumNode->children.size()+1;
    newAlbum->energy = (temp->energy*(albumNode->children.size()) + song->energy) / albumNode->children.size()+1;
    newAlbum->speechiness = (temp->speechiness*(albumNode->children.size()) + song->speechiness) / albumNode->children.size()+1;
    newAlbum->acousticness = (temp->acousticness*(albumNode->children.size()) + song->acousticness) / albumNode->children.size()+1;
    newAlbum->instrumentalness = (temp->instrumentalness*(albumNode->children.size()) + song->instrumentalness) / albumNode->children.size()+1;
    newAlbum->valence = (temp->valence*(albumNode->children.size()) + song->valence) / albumNode->children.size()+1;
    newAlbum->tempo = (temp->tempo*(albumNode->children.size()) + song->tempo) / albumNode->children.size()+1;
    
    albumNode->album = newAlbum;
    delete temp;
}

void B::rebalanceArtist(Node* artistNode, Album* album) {
    Artist* newArtist = new Artist;
    Artist* temp = artistNode->artist;
    
    newArtist->danceability = (temp->danceability*(artistNode->children.size()) + album->danceability) / artistNode->children.size()+1;
    newArtist->energy = (temp->energy*(artistNode->children.size()) + album->energy) / artistNode->children.size()+1;
    newArtist->speechiness = (temp->speechiness*(artistNode->children.size()) + album->speechiness) / artistNode->children.size()+1;
    newArtist->acousticness = (temp->acousticness*(artistNode->children.size()) + album->acousticness) / artistNode->children.size()+1;
    newArtist->instrumentalness = (temp->instrumentalness*(artistNode->children.size()) + album->instrumentalness) / artistNode->children.size()+1;
    newArtist->valence = (temp->valence*(artistNode->children.size()) + album->valence) / artistNode->children.size()+1;
    newArtist->tempo = (temp->tempo*(artistNode->children.size()) + album->tempo) / artistNode->children.size()+1;
    
    artistNode->artist = newArtist;
    delete temp;
}