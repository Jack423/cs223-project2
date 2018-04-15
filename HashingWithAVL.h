//
// Created by Jack Butler on 4/10/18.
//

#ifndef CS223_PROJECT2_HASHINGWITHAVL_H
#define CS223_PROJECT2_HASHINGWITHAVL_H

#include "AVL.h"
#include "Hashing.h"
#include <cstdio>

class HashingWithAVL: Hashing {

public:

    BalancedBST *hashTable;

    HashingWithAVL(int tableSize) :
            Hashing(tableSize) {
        hashTable = new BalancedBST[TABLE_SIZE];
    }

    bool search(int key) { // fill this method
        int hashVal = getHashValue(key);
        if (hashTable[hashVal].search(key) < 0){
            return false;
        }
        else{
            return true;
        }
    }

    bool insert(int val) { // fill this method

        int hashVal = getHashValue(val);
        if (search(val)) {
            hashTable[hashVal].insert(val);
            return true;
        } else {
            return false;
        }

    }

    bool remove(int val) {// fill this method
        int hashVal = getHashValue(val);
        if (search(val)){
            hashTable[hashVal].remove(val);
            return true;
        }
        else{
            return false;
        }
    }

    void printStatistics() {
        int maxHeight = hashTable[0].getTreeHeight();
        int minHeight = maxHeight, total = maxHeight;
        for (int i = 1; i < TABLE_SIZE; i++) {
            int height = hashTable[i].getTreeHeight();
            if (height > maxHeight)
                maxHeight = height;
            else if (height < minHeight)
                minHeight = height;
            total += height;
        }
        printf(
                "Max height of a BST = %d\nMin height of a BST = %d\nAvg height of a BST = %d\n",
                maxHeight, minHeight, total / TABLE_SIZE);
    }
};

#endif //CS223_PROJECT2_HASHINGWITHAVL_H
