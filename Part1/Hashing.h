//
// Created by Jack Butler on 4/10/18.
//

#ifndef CS223_PROJECT2_HASHING_H
#define CS223_PROJECT2_HASHING_H


class Hashing {

protected:

    int TABLE_SIZE;

    Hashing(int tableSize) {
        TABLE_SIZE = tableSize;
    }

    int getHashValue(int val) {
        return val % TABLE_SIZE;
    }
};

#endif //CS223_PROJECT2_HASHING_H
