
//
// Created by ashto on 11/27/2024.
//

#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <vector>
#include <iostream>
#include <functional>
#include <string>

#include "User.h"
#include "Methods.h"

// What a generic node for an unordered map
template <typename K,typename V>
struct mapNode {
    K key;
    V value;
    mapNode* next;

    mapNode(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
};

// Generic templates for the key and value
template <typename K, typename V>
class UnorderedMap {
    const float load_factor = .80;
    int elementSize;
    int bucketNum;
    std::vector<mapNode<K, V>*> theMap;
    void rehash();

    public:
      UnorderedMap(int bucketNum = 32);
      void insert(const K& key, const V& value);
      bool findIf(const K& key);
      mapNode<K, V>* find(const K& key);
      unsigned int hash(K key);

};


struct NestedMap {
    // Artist Name -> Album -> Song
    UnorderedMap<string, UnorderedMap<string, UnorderedMap<string, Song>>> artistMap;
    UnorderedMap<string, Song> songMap;

    void insert(Song& song);
};

#endif //UNORDERED_MAP_H
