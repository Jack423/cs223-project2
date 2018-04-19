//
// Created by Jack Butler on 4/14/18.
//

#ifndef CS223_PROJECT2_KSORTALGO_H
#define CS223_PROJECT2_KSORTALGO_H

#include "Heap.h"

class KSortAlgo {

public:
    void sort(int kSortedArray[], int arrayLen, int k) { // fill this method
        Heap heap(k + 1);
        int ti = 0;
        for (int i = 0; i <= k; i++)
            heap.insert(kSortedArray[i]);

        for (int i = k + 1; ti < arrayLen; i++) {
            heap.insert(kSortedArray[i]);
            kSortedArray[ti] = heap.deleteMinimum();
            ti++;
        }
        for (int i = 0; i < k; i++) {
            kSortedArray[ti] = heap.deleteMinimum();
            ti++;
        }
    }

};

#endif //CS223_PROJECT2_KSORTALGO_H
