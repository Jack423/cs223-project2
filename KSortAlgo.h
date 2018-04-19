//
// Created by Jack Butler on 4/14/18.
//

#ifndef CS223_PROJECT2_KSORTALGO_H
#define CS223_PROJECT2_KSORTALGO_H

#include "Heap.h"

class KSortAlgo {

public:
    void sort(int kSortedArray[], int arrayLen, int k) { // fill this method
        int *heapArray = new int[k + 1];
        for (int i = 0; i <= k && i < arrayLen; i++)
            heapArray[i] = kSortedArray[i];
        Heap hp(k + 1);

        for (int i = k + 1, ti = 0; ti < arrayLen; i++, ti++) {
            kSortedArray[ti] = hp.deleteMinimum();
        }
    }
};

#endif //CS223_PROJECT2_KSORTALGO_H
