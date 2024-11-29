#ifndef PROJECT3_43_B_H
#define PROJECT3_43_B_H

#include "Methods.h"

struct Node {
    string name;
    Song* song;
    Album* album;
    Artist* artist;
    vector<Node*> children;
    Node(const string &x) : name(x) {};
    Node(const string &x, Song* y) : name(x), song(y) {};
    Node(const string &x, Album* y) : name(x), album(y) {};
    Node(const string &x, Artist* y) : name(x), artist(y) {};
};

class B {
    private:
        Node* root;
    public:
        B();
        ~B();
        void insertSong(Song* song);
        void rebalanceAlbum(Node* albumNode, Song* song);
        void rebalanceArtist(Node* artistNode, Album* album);
};

#endif //PROJECT3_43_B_H