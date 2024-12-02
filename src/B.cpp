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
}

void B::rebalanceTree() {
    rebalanceTree(root);
}

void B::rebalanceTree(Node* node) {
    if(!node) return; //if node doesnt exist, exit to avoid segfault
    if(node->album) { //if node is an album node, rebalance it and dont push children, as song nodes dont need to be rebalanced
        rebalanceAlbum(node);
    }
    else if(node->children.size() != 0) { //otherwise, push all children to function
        for(Node* child : node->children) {
            rebalanceTree(child);
        }
    }

    if(node->artist) { //if node is an artist node, rebalance the artist. Its children should still be pushed as albums mustbe rebalanced
        rebalanceArtist(node); //artist node should be rebalanced at the end, as it should be rebalanced after albums are rebalanced
    }
}

void B::rebalanceAlbum(Node* albumNode) {
    double danceability, energy, speechiness, acousticness, instrumentalness, valence, tempo;
    int size = albumNode->children.size();
    for(Node* child : albumNode->children) {
        danceability += child->song->danceability;
        energy += child->song->energy;
        speechiness += child->song->speechiness;
        acousticness += child->song->acousticness;
        instrumentalness += child->song->instrumentalness;
        valence += child->song->valence;
        tempo += child->song->tempo;
    }
    albumNode->album->danceability = danceability/size;
    albumNode->album->energy = energy/size;
    albumNode->album->speechiness = speechiness/size;
    albumNode->album->acousticness = acousticness/size;
    albumNode->album->instrumentalness = instrumentalness/size;
    albumNode->album->valence = valence/size;
    albumNode->album->tempo = tempo/size;
}

void B::rebalanceArtist(Node* artistNode) {
    double danceability, energy, speechiness, acousticness, instrumentalness, valence, tempo;
    int size = artistNode->children.size();
    for(Node* child : artistNode->children) {
        danceability += child->album->danceability;
        energy += child->album->energy;
        speechiness += child->album->speechiness;
        acousticness += child->album->acousticness;
        instrumentalness += child->album->instrumentalness;
        valence += child->album->valence;
        tempo += child->album->tempo;
    }
    artistNode->artist->danceability = danceability/size;
    artistNode->artist->energy = energy/size;
    artistNode->artist->speechiness = speechiness/size;
    artistNode->artist->acousticness = acousticness/size;
    artistNode->artist->instrumentalness = instrumentalness/size;
    artistNode->artist->valence = valence/size;
    artistNode->artist->tempo = tempo/size;
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