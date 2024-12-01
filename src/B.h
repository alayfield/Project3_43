#ifndef PROJECT3_43_B_H
#define PROJECT3_43_B_H

#include <vector>
using namespace std;

struct Song;
struct Album;
struct Artist;

struct Node {
    string name;
    Song* song = nullptr;
    Album* album = nullptr;
    Artist* artist = nullptr;
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
        void insertSong(Song* songNode);
        void rebalanceAlbum(Node* albumNode, Song* songNode);
        void rebalanceArtist(Node* artistNode, Album* albumNode);
        Album* searchAlbum(string decade, string artistName, string albumName);
        Node* findChild(Node* source, string name);
};

#endif //PROJECT3_43_B_H