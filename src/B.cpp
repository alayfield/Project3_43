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
    Node* decadeNode = findChild(root, decade); //find decade node if already exists
    if(!decadeNode) return; //if decade not found, exit function

    Node* artistNode = findChild(decadeNode, songNode->artistName); //find artist node if already exists
    if(!artistNode) { //if no node for the artist exists, create a new artist structure and add node
        Artist* tempArtist = new Artist;
        tempArtist->artistName = songNode->artistName;
        artistNode = new Node(tempArtist->artistName, tempArtist);
        decadeNode->children.push_back(artistNode);
    }

    Node* albumNode = findChild(artistNode, songNode->albumName); //find album node if already exits
    if(!albumNode) { //if no node for the album exists, create a new artist structure and add node
        Album* tempAlbum = new Album;
        tempAlbum->name = songNode->albumName;
        tempAlbum->artistName = songNode->artistName;
        tempAlbum->year = songNode->year;
        albumNode = new Node(tempAlbum->artistName, tempAlbum);
        artistNode->children.push_back(albumNode);
    }
    
    albumNode->children.push_back(new Node(songNode->name, songNode)); //add the song to the album node's children

    rebalanceAlbum(albumNode, songNode); //update the average values of all songs in the album
    rebalanceArtist(artistNode, albumNode->album); //update the average values of all albums from the artist
}

void B::rebalanceAlbum(Node* albumNode, Song* song) {
    Album* albumVal = albumNode->album;

    albumVal->danceability = findAvg(albumVal->danceability, double(albumNode->children.size()), song->danceability);
    albumVal->energy = findAvg(albumVal->energy, double(albumNode->children.size()), song->energy);
    albumVal->speechiness = findAvg(albumVal->speechiness, double(albumNode->children.size()), song->speechiness);
    albumVal->acousticness = findAvg(albumVal->acousticness, double(albumNode->children.size()), song->acousticness);
    albumVal->instrumentalness = findAvg(albumVal->instrumentalness, double(albumNode->children.size()), song->instrumentalness);
    albumVal->valence = findAvg(albumVal->valence, double(albumNode->children.size()), song->valence);
    albumVal->tempo = findAvg(albumVal->tempo, double(albumNode->children.size()), song->tempo);

    /*
    Album* newAlbum = new Album;
    Album* temp = albumNode->album;

    newAlbum->danceability = (temp->danceability*(double(albumNode->children.size())) + song->danceability) / double(albumNode->children.size())+1;
    newAlbum->energy = (temp->energy*(double(albumNode->children.size())) + song->energy) / double(albumNode->children.size())+1;
    newAlbum->speechiness = (temp->speechiness*(double(albumNode->children.size())) + song->speechiness) / double(albumNode->children.size())+1;
    newAlbum->acousticness = (temp->acousticness*(double(albumNode->children.size())) + song->acousticness) / double(albumNode->children.size())+1;
    newAlbum->instrumentalness = (temp->instrumentalness*(double(albumNode->children.size())) + song->instrumentalness) / double(albumNode->children.size())+1;
    newAlbum->valence = (temp->valence*(double(albumNode->children.size())) + song->valence) / double(albumNode->children.size())+1;
    newAlbum->tempo = (temp->tempo*(int(albumNode->children.size())) + song->tempo) / double(albumNode->children.size())+1;
    
    albumNode->album = newAlbum;
    delete temp;
    */
}

void B::rebalanceArtist(Node* artistNode, Album* album) {
    Album* artistVal = artistNode->album;

    artistVal->danceability = findAvg(artistVal->danceability, double(artistNode->children.size()), album->danceability);
    artistVal->energy = findAvg(artistVal->energy, double(artistNode->children.size()), album->energy);
    artistVal->speechiness = findAvg(artistVal->speechiness, double(artistNode->children.size()), album->speechiness);
    artistVal->acousticness = findAvg(artistVal->acousticness, double(artistNode->children.size()), album->acousticness);
    artistVal->instrumentalness = findAvg(artistVal->instrumentalness, double(artistNode->children.size()), album->instrumentalness);
    artistVal->valence = findAvg(artistVal->valence, double(artistNode->children.size()), album->valence);
    artistVal->tempo = findAvg(artistVal->tempo, double(artistNode->children.size()), album->tempo);
    /*
    Artist* newArtist = new Artist;
    Artist* temp = artistNode->artist;
    
    newArtist->danceability = (temp->danceability*(double(artistNode->children.size())) + album->danceability) / double(artistNode->children.size())+1;
    newArtist->energy = (temp->energy*(double(artistNode->children.size())) + album->energy) / double(artistNode->children.size())+1;
    newArtist->speechiness = (temp->speechiness*(double(artistNode->children.size())) + album->speechiness) / double(artistNode->children.size())+1;
    newArtist->acousticness = (temp->acousticness*(double(artistNode->children.size())) + album->acousticness) / double(artistNode->children.size())+1;
    newArtist->instrumentalness = (temp->instrumentalness*(double(artistNode->children.size())) + album->instrumentalness) / double(artistNode->children.size())+1;
    newArtist->valence = (temp->valence*(double(artistNode->children.size())) + album->valence) / double(artistNode->children.size())+1;
    newArtist->tempo = (temp->tempo*(double(artistNode->children.size())) + album->tempo) / double(artistNode->children.size())+1;
    
    artistNode->artist = newArtist;
    delete temp;
     */
}

Album* B::searchAlbum(string decade, string artistName, string albumName) {
    Node* decadeNode = findChild(root, decade); //find decade node if already exists
    if(!decadeNode) return nullptr; //if decade not found, exit function

    Node* artistNode = findChild(decadeNode, artistName); //find artist node if already exists
    if(!artistNode) return nullptr; //if no node for the artist exists, exit function

    Node* albumNode = findChild(decadeNode, albumName); //find album node, or nullptr if doesnt exist
    return albumNode->album;
}

Node* B::findChild(Node* source, string name) {
    for(Node* curr : source->children) { //traverse to if child exists and return if found
        if (curr->name == name) {
            return curr;
        }
    }
    return nullptr; //return nullptr if child does not exist in tree
}