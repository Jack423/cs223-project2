//
// Created by Jack Butler on 4/14/18.
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
        int minChildVal;
        int minChildIndex;
        int leftChildIndex;
        int minValue = heapArray[0];
        heapArray[0] = heapArray[currentSize-1];
        currentSize--;
        int currentNode = 0;
        int leftChild = 1, rightChild = 2;
        while(leftChild < currentSize){
            int leftChildVal = heapArray[leftChild];
            if(rightChild < currentSize){
                int rightChildVal = heapArray[rightChild];
                if(leftChildVal < rightChildVal){
                    int minChildVal = leftChildVal;
                    int minChildIndex = leftChild;
                } else{
                    minChildVal = rightChildVal;
                    minChildIndex = rightChild;
                }
                if(heapArray[currentNode] > minChildVal){
                    swap(heapArray[currentNode], heapArray[minChildIndex]);
                    currentNode = minChildIndex;
                } else {
                    break;
                }
            } else {
                if(heapArray[currentNode] > leftChildVal){
                    swap(heapArray[currentNode], heapArray[leftChildIndex]);
                    currentNode = leftChildIndex;
                } else{
                    break;
                }
                leftChild = 2*currentNode+1;
                rightChild = 2*currentNode+2;
            }
        }
        return minValue;
    }

    void insert(int value) {// fill this method
        heapArray[currentSize] = value;
        int currentNode = currentSize++;
        while(currentNode > 0 && heapArray[getParentIndex(currentNode)] > heapArray[currentNode]){
            swap(heapArray[getParentIndex(currentNode)], heapArray[currentNode]);
            currentNode = getParentIndex(currentNode);
        }
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
