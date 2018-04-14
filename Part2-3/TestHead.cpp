//
// Created by jack on 4/14/18.
//

#include <cstdlib>
#include "Heap.h"
#include <iostream>

#include "KSortAlgo.h"

using namespace std;

int binarySearch(int *array, int arrayLen, int key) {

    int low = 0, high = arrayLen - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (array[mid] == key) {
            return mid;
        } else if (array[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

void heapSort(int *array, int arrayLen) {
    Heap heap(arrayLen);
    for (int i = 0; i < arrayLen; i++) {
        heap.insert(array[i]);
    }
    for (int i = 0; i < arrayLen; i++) {
        array[i] = heap.deleteMinimum();
    }
}

bool isKSortedArray(int *array, int arrayLen, int k) {
    int *aux = new int[arrayLen];
    for (int i = 0; i < arrayLen; i++)
        aux[i] = array[i];
    heapSort(aux, arrayLen);
    for (int i = 0; i < arrayLen; i++) {
        int j = binarySearch(aux, arrayLen, array[i]);
        if (abs(i - j) >= k)
            return false;
    }
    return true;
}

int *generateKSorted(int arrayLen, int k) {
    int *array = new int[arrayLen];
    for (int i = 0; i < arrayLen; i++)
        array[i] = i + rand() % k;

    if (isKSortedArray(array, arrayLen, k))
        return array;
    else
        throw "Oops! Wrong code for k sorted generation";
}

bool isSorted(int array[], int arrayLen) {
    for (int i = 0; i < arrayLen - 1; i++)
        if (array[i] > array[i + 1])
            return false;
    return true;
}

void printArray(int *A, int len) {
    if (0 == len) {
        cout << "[]";
        return;
    }
    cout << "[";
    for (int i = 0; i < len - 1; i++) {
        cout << A[i] << ", ";
    }
    cout << A[len - 1] << "]";
}

void testHeap() {
    cout << "*** Heap Test ***" << endl << endl;
    int array[] = {1, 3, 17, 2, 100, 26, 7, 19};
    int arrayLen = 8;
    Heap heap(arrayLen);
    for (int i = 0; i < arrayLen; i++) {
        heap.insert(array[i]);
        cout << "Inserting " << array[i] << ": ";
        printArray(heap.heapArray, arrayLen);
        cout << ", Size = " << heap.getSize() << endl;
    }
    cout << endl;
    for (int i = 0; i < arrayLen; i++) {
        cout << "Deleting " << heap.deleteMinimum() << ": ";
        printArray(heap.heapArray, arrayLen);
        cout << ", Size = " << heap.getSize();
        cout << endl;
    }
}

void testKSortedCorrectness() {
    cout << "\n*** k-Sorted Correctness Test ***\n" << endl;
    int arrayLen = 20, k = 5;
    int *randomKSortedArray = generateKSorted(arrayLen, k);
    printf("Random %d-sorted Array of length %d (before sorting): ", k,
           arrayLen);
    printArray(randomKSortedArray, arrayLen);
    cout << endl;
    KSortAlgo ksortalg;
    ksortalg.sort(randomKSortedArray, arrayLen, k);
    printf("Random %d-sorted Array of length %d (after sorting):  ", k,
           arrayLen);
    printArray(randomKSortedArray, arrayLen);
    cout << endl;
    if (!isSorted(randomKSortedArray, arrayLen))
        throw "Oops! Wrong code for k sorting";
}

void testKSortedTime() {

    int length = 1000000;
    int k = 100;
    printf("\n*** k-Sorted Time Test (length = %d, k = %d)  ***\n\n", length,
           k);

    int *randomKSortedArray = generateKSorted(length, k);
    int randomKSortedArrayCopy[length];
    for (int i = 0; i < length; i++)
        randomKSortedArrayCopy[i] = randomKSortedArray[i];

    clock_t startTime;

    startTime = clock();
    heapSort(randomKSortedArrayCopy, length);
    if (!isSorted(randomKSortedArrayCopy, length))
        throw "Oops! Wrong code for k sorting";
    printf(
            "Time taken using heapsort algorithm = %lu (may vary with each execution)\n",
            (clock() - startTime));

    startTime = clock();
    KSortAlgo ksortalg;
    ksortalg.sort(randomKSortedArray, length, k);
    if (!isSorted(randomKSortedArray, length))
        throw "Oops! Wrong code for k sorting";
    printf(
            "Time taken using k-sorted algorithm = %lu (may vary with each execution)\n",
            clock() - startTime);

}

int main() {

    testHeap();
    testKSortedCorrectness();
    testKSortedTime();
    return 0;
}

