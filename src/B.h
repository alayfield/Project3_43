#ifndef PROJECT3_43_B_H
#define PROJECT3_43_B_H

#include <utility>
#include <vector>
#include "Methods.h"
using namespace std;

struct treeNode {
    string name;
    Song* song = nullptr;
    Album* album = nullptr;
    Artist* artist = nullptr;
    vector<treeNode*> children;
    explicit treeNode(string x) : name(std::move(x)) {};
    treeNode(string x, Song* y) : name(std::move(x)), song(y) {};
    treeNode(string x, Album* y) : name(std::move(x)), album(y) {};
    treeNode(string x, Artist* y) : name(std::move(x)), artist(y) {};
};

class B {
    private:
        treeNode* root;
        void rebalanceDecade(treeNode* node);
        void rebalanceArtist(treeNode* artistNode);
        void rebalanceAlbum(treeNode* albumNode, Song* song);

    public:
        B();
        ~B();
        void insertSong(Song* songNode);
        void rebalanceTree();
        Album* searchAlbum(const string& decade, string artistName, string albumName);
        treeNode* findChild(treeNode* source, const string& name);
        Album* euclidDist(const string& decade, vector<double> userVals);
        Album* mahaDist(const string& decade, vector<double> userVals, vector<vector<double> > covMatrix);
};

#endif //PROJECT3_43_B_H