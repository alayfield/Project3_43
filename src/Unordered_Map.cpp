//
// Created by ashto on 11/27/2024.
//

#include "Unordered_Map.h"

// constructor
template<typename K, typename V>
UnorderedMap<K, V>::UnorderedMap(int bucketNum) : bucketNum(bucketNum), elementSize(0), theMap(bucketNum, nullptr) {
}


template<typename K, typename V>
void UnorderedMap<K, V>::insert(const K &key, const V &value) {
    int index = hash(key) % bucketNum;
    Node<K, V> *currentNode = theMap[index];

    // If duplicate inserted, updates it
    while(currentNode != nullptr) {
        if(currentNode->key == key) {
            //currentNode->value = value;
            return;
        }
        currentNode = currentNode->next;
    }

    // creates a new node with the inputted key and value and then sets map index and increments element size
    Node<K, V> *newNode = new Node<K, V>(key, value);
    newNode->next = theMap[index];
    theMap[index] = newNode;
    elementSize += 1;

    // initializes rehash if necessary
    if(elementSize * 1.0 / bucketNum > load_factor) {
        rehash();
    }
}

// I looked up what the is_same function was on c plus plus https://cplusplus.com/reference/type_traits/is_same/
template<typename K, typename V>
int UnorderedMap<K, V>::hash(const K& key) {
    // here I used the djb2 hash function developed by Dan Bernstein
    if(std::is_same<K, std::string>::value) {
        int hash = 5381;
        for(char c : key) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash;
    }
    else if(std::is_same<K, int>::value) {
        //return key;
    }
    else if(std::is_same<K, char>::value) {
        //return key;
    }
    else {
        // string not inputted
        return -1;
    }
}


template<typename K, typename V>
void UnorderedMap<K, V>::rehash() {
    int newBucketNum = bucketNum * 2;
    vector<Node<K, V> *> newMap(newBucketNum, nullptr);

    // goes through each bucket
    for(int i = 0; i < bucketNum; i++) {
        Node<K, V> *currentNode = theMap[i];
        while(currentNode != nullptr) {
            Node<K, V> *nextNode = currentNode->next;

            int newIndex = hash(currentNode->key) % newBucketNum;
            currentNode->next = newMap[newIndex];
            newMap[newIndex] = currentNode;

            currentNode = nextNode;
        }
    }

    theMap = newMap;
    bucketNum = newBucketNum;
}


template<typename K, typename V>
bool UnorderedMap<K, V>::findIf(const K &key) {
    // Finds the index using hash
    int index = hash(key) % bucketNum;
    Node<K, V> *currentNode = theMap[index];

    // iterates through the adjacency list if it exists and if it finds the key it returns true
    while(currentNode != nullptr) {
        if(currentNode->key == key) {
            return true;
        }
        currentNode = currentNode->next;
    }

    // if not found, returns false
    return false;
}

template<typename K, typename V>
Node<K, V> *UnorderedMap<K, V>::find(const K &key) {
    // Finds the index using hash
    int index = hash(key) % bucketNum;
    Node<K, V> *currentNode = theMap[index];

    // iterates through the adjacency list if it exists and if it finds the key, returns node
    while(currentNode != nullptr) {
        if(currentNode->key == key) {
            return currentNode;
        }
        currentNode = currentNode->next;
    }

    // if not found, returns a nullptr
    return nullptr;
}

void NestedMap::insert(const Song& song) {
    // checks if artist is inputted, if not inputs
    if (!artistMap.findIf(song.artistName)) {
        artistMap.insert(song.artistName, UnorderedMap<std::string, UnorderedMap<std::string, Song>>());
    }

    // gets album map
    auto& albumMap = artistMap.find(song.artistName)->value;

    // checks if album inputted, if not inputs
    if(!albumMap.findIf(song.albumName)) {
        albumMap.insert(song.albumName, UnorderedMap<std::string, Song>());
    }

    // gets song map
    auto& songMap = albumMap.find(song.albumName)->value;

    // inserts song
    songMap.insert(song.name, song);
}
