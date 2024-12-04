#ifndef PROJECT3_43_B_H
#define PROJECT3_43_B_H

#include <vector>
using namespace std;

struct Song;
struct Album;
struct Artist;

struct treeNode {
    string name;
    Song* song = nullptr;
    Album* album = nullptr;
    Artist* artist = nullptr;
    vector<treeNode*> children;
    treeNode(const string &x) : name(x) {};
    treeNode(const string &x, Song* y) : name(x), song(y) {};
    treeNode(const string &x, Album* y) : name(x), album(y) {};
    treeNode(const string &x, Artist* y) : name(x), artist(y) {};
};

class B {
    private:
        treeNode* root;
    public:
        B();
        ~B();
        void insertSong(Song* songNode);
        void rebalanceTree();
        void rebalanceDecade(treeNode* node);
        void rebalanceArtist(treeNode* artistNode);
        void rebalanceAlbum(treeNode* albumNode, Song* song);
        Album* searchAlbum(string decade, string artistName, string albumName);
        treeNode* findChild(treeNode* source, string name);

        Album* euclidDist(string decade, vector<double> userVals);
};

#endif //PROJECT3_43_B_H