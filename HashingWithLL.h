//
// Created by Jack Butler on 4/10/18.
//

#ifndef CS223_PROJECT2_HASHINGWITHLL_H_
#define CS223_PROJECT2_HASHINGWITHLL_H_

#include "Hashing.h"
#include "LinkedList.h"
#include <stdio.h>

class HashingWithLL : Hashing {

public:

    LinkedList *hashTable;

    HashingWithLL(int tableSize) :
            Hashing(tableSize) {
            hashTable = new LinkedList[TABLE_SIZE];
    }

    bool search(int key) {
        int hashVal = getHashValue(key);
        if (hashTable[hashVal].search(key) < 0)
            return false;
        else
            return true;
    }

    bool insert(int val) { // fill this method

        int hashVal = getHashValue(val);
        if (!search(val)){
            hashTable[hashVal].insertAtEnd(val);
            return true;
        }
        else{
            return false;
        }

    }

    bool remove(int val) { // fill this method
        int hashVal = getHashValue(val);
        if (search(val)){
            hashTable[hashVal].removeFirst(val);
            return true;
        }
        else{
            return false;
        }
    }

    void printStatistics() {
        int maxSize = hashTable[0].size;
        int minSize = maxSize, total = maxSize;
        for (int i = 1; i < TABLE_SIZE; i++) {
            int size = hashTable[i].size;
            if (size > maxSize)
                maxSize = size;
            else if (size < minSize)
                minSize = size;
            total += size;
        }
        printf(
                "Max length of a chain = %d\nMin length of a chain = %d\nAvg length of chains = %d\n",
                maxSize, minSize, total / TABLE_SIZE);
    }
};

#endif
