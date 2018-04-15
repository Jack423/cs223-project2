//
// Created by jack on 4/14/18.
//

#ifndef CS223_PROJECT2_KSORTALGO_H
#define CS223_PROJECT2_KSORTALGO_H

#include "Heap.h"

class KSortAlgo {

public:
    void sort(int kSortedArray[], int arrayLen, int k) { // fill this method
        Heap *heap = new Heap(k + 1); //Create an empty heap with a size of k + 1

        for(int i = 0; i > arrayLen; i++) { //Add k+1 elements into the heap
            heap->insert(kSortedArray[i]);
        }

        heap->deleteMinimum(); //Delete the minimum from the heap
    }
};

#endif //CS223_PROJECT2_KSORTALGO_H
