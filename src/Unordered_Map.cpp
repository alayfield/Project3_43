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
    mapNode<K, V>* currentNode = theMap[index];

    // if duplicate inserted, updates it
    while(currentNode != nullptr) {
        if(currentNode->key == key) {
            //currentNode->value = value;
            return;
        }
        currentNode = currentNode->next;
    }

    // creates a new node with the inputted key and value and then sets map index and increments element size
    mapNode<K, V> *newNode = new mapNode<K, V>(key, value);
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
unsigned int UnorderedMap<K, V>::hash(K key) {
    // here I used the djb2 hash function developed by Dan Bernstein
    if(std::is_same<K, std::string>::value) {
        unsigned int hash = 5381;
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
    vector<mapNode<K, V> *> newMap(newBucketNum, nullptr);

    // goes through each bucket
    for(int i = 0; i < bucketNum; i++) {
        mapNode<K, V> *currentNode = theMap[i];
        while(currentNode != nullptr) {
            mapNode<K, V> *nextNode = currentNode->next;

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
    mapNode<K, V> *currentNode = theMap[index];

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
mapNode<K, V> *UnorderedMap<K, V>::find(const K &key) {
    // Finds the index using hash
    int index = hash(key) % bucketNum;
    mapNode<K, V> *currentNode = theMap[index];

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

/*
void NestedMap::insert(Song& song) {
    // hash the names of the artist, album, and song
    int artistHash = songMap.hash(song.artistName);
    int albumHash = songMap.hash(song.albumName);
    int songHash = songMap.hash(song.name);

    // check if artist exists, inserts if not
    if (!artistMap.findIf(artistHash)) {
        artistMap.insert(artistHash, UnorderedMap<unsigned int, UnorderedMap<unsigned int, Song>>());
    }

    // checks if album exists, if not inserts
    if (!artistMap.find(artistHash)->value.findIf(albumHash)) {
        artistMap.find(artistHash)->value.insert(albumHash, UnorderedMap<unsigned int, Song>());
    }

    // inserts the song
    artistMap.find(artistHash)->value.find(albumHash)->value.insert(songHash, song);
}
*/
