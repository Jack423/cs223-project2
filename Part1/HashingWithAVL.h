//
// Created by Jack Butler on 4/10/18.
//

#ifndef CS223_PROJECT2_HASHINGWITHAVL_H
#define CS223_PROJECT2_HASHINGWITHAVL_H

#include "AVL.h"
#include "Hashing.h"

class HashingWithAVL: Hashing {

public:

    BalancedBST *hashTable;

    HashingWithAVL(int tableSize) :
            Hashing(tableSize) {
        hashTable = new BalancedBST[TABLE_SIZE];
    }

    bool search(int key) { // fill this method
    }

    bool insert(int val) { // fill this method
    }

    bool remove(int val) {// fill this method
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
