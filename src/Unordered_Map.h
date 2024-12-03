
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

// What a generic node for an unordered map
template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node* next;

    Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
};

// Generic templates for the key and value
template <typename K, typename V>
class UnorderedMap {
    const float load_factor = .80;
    int elementSize;
    int bucketNum;
    std::vector<Node<K, V>*> theMap;
    int hash(const K& key);
    void rehash();

public:
    UnorderedMap(int bucketNum = 32);
    void insert(const K& key, const V& value);
    bool findIf(const K& key);
    Node<K, V>* find(const K& key);

};


struct NestedMap {
    // Artist Name -> Album -> Song
    UnorderedMap<std::string, UnorderedMap<std::string, UnorderedMap<std::string, Song>>> artistMap;

    void insert(const Song& song);
};

#endif //UNORDERED_MAP_H