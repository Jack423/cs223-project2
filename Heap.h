//
// Created by jack on 4/14/18.
//

#ifndef CS223_PROJECT2_HEAP_H
#define CS223_PROJECT2_HEAP_H

class Heap {

private:
    int currentSize;

public:
    int *heapArray;

    Heap(int heapSize) {
        currentSize = 0;
        heapArray = new int[heapSize];
        for (int i = 0; i < heapSize; i++)
            heapArray[i] = 0;
    }

    int getSize() {
        return currentSize;
    }

    int deleteMinimum() {// fill this method
    }

    void insert(int value) {// fill this method
    }

private:
    void swap(int index1, int index2) {

        int temp = heapArray[index1];
        heapArray[index1] = heapArray[index2];
        heapArray[index2] = temp;
    }

    int getParentIndex(int index) {
        return (index - 1) / 2;
    }
};

#endif //CS223_PROJECT2_HEAP_H
