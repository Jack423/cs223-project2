//
// Created by Jack Butler on 4/10/18.
//

#include <cstdlib>
#include <iostream>

#include "HashingWithAVL.h"
#include "HashingWithLL.h"
#include "PrimeGeneration.h"

using namespace std;

void testCorrectness() {
    srand(0);
    cout << "*** Test Hashing Correctness ***" << endl << endl;
    int TABLE_SIZE = 5;
    int U = 50;
    HashingWithLL hChain(TABLE_SIZE);
    HashingWithAVL hBST(TABLE_SIZE);

    int testArray[] = {11, 12, 15, 17, 12, 19, 4, 5, 19, 20, 32, 77, 65, 88,
                       99, 10, 8, 19, 15, 66};
    int arrayLen = 20;
    for (int i = 0; i < arrayLen; i++) {
        int val = testArray[i];
        bool inserted = hChain.insert(val);
        if (!hBST.insert(val) && inserted)
            throw "Something went wrong";
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "Separate Chaining " << i << ": ";
        hChain.hashTable[i].printList();
        cout << "BST " << i << ": ";
        hBST.hashTable[i].printBST();
        cout << endl << endl;
    }

    for (int i = 0; i < arrayLen; i++) {
        double randDouble = (double) rand() / RAND_MAX;
        int val = randDouble > 0.5 ? rand() % U : testArray[i];
        bool found = hChain.search(val);
        if (!hBST.search(val) && found)
            throw "Something went wrong with search!";
        else if (found)
            cout << "Found " << val << endl;
        else
            cout << "Did not find " << val << endl;
    }
    cout << endl;
    for (int i = 0; i < arrayLen; i++) {
        double randDouble = (double) rand() / RAND_MAX;
        int val = randDouble > 0.5 ? rand() % U : testArray[i];
        bool deleted = hChain.remove(val);
        if (!hBST.remove(val) && deleted)
            throw "Something went wrong with deletion!";
        else if (deleted)
            cout << "Deleted " << val << endl;
        else
            cout << val << " is not present" << endl;
    }
}

void testHashingTime() {
    srand(0);
    int TABLE_SIZE = PrimeGeneration::getLargestBoundedPrime(10000);
    int U = 1000000;
    HashingWithLL hChain(TABLE_SIZE);
    HashingWithAVL hBST(TABLE_SIZE);
    BalancedBST bst;

    long totalLLHashIns = 0, totalBSTHashIns = 0, totalBSTIns = 0;
    long totalLLHashSearch = 0, totalBSTHashSearch = 0, totalBSTSearch = 0;
    long totalLLHashDel = 0, totalBSTHashDel = 0, totalBSTDel = 0;

    int generatedNum[U];

    int numFailedInsertions = 0;

    for (int i = 0; i < U; i++) {
        int val = rand() % U;
        generatedNum[i] = val;
        long startTime = clock();
        bool inserted = hChain.insert(val);
        if (!inserted)
            numFailedInsertions++;
        totalLLHashIns += clock() - startTime;

        startTime = clock();
        if (hBST.insert(val) && !inserted)
            throw "Something went wrong with insertion!";
        totalBSTHashIns += clock() - startTime;

        startTime = clock();
        if (bst.insert(val) && !inserted)
            throw "Something went wrong with insertion!";
        totalBSTIns += clock() - startTime;
    }

    int numFailedSearches = 0;
    for (int i = 0; i < U; i++) {

        double randDouble = (double) rand() / RAND_MAX;
        int val = randDouble > 0.5 ? rand() % U : generatedNum[rand() % U];

        long startTime = clock();
        bool found = hChain.search(val);
        if (!found)
            numFailedSearches++;
        totalLLHashSearch += clock() - startTime;

        startTime = clock();
        if (hBST.search(val) && !found)
            throw "Something went wrong with search!";
        totalBSTHashSearch += clock() - startTime;

        startTime = clock();
        if (bst.search(val) && !found)
            throw "Something went wrong with search!";
        totalBSTSearch += clock() - startTime;
    }

    int numFailedDeletions = 0;
    for (int i = 0; i < U; i++) {
        double randDouble = (double) rand() / RAND_MAX;
        int val = randDouble > 0.5 ? rand() % U : generatedNum[rand() % U];

        long startTime = clock();
        bool deleted = hChain.remove(val);
        if (!deleted)
            numFailedDeletions++;
        totalLLHashDel += clock() - startTime;

        startTime = clock();
        if (hBST.remove(val) && !deleted)
            throw "Something went wrong with deletion!";
        totalBSTHashDel += clock() - startTime;

        startTime = clock();
        if (bst.remove(val) && !deleted)
            throw "Something went wrong with deletion!";
        totalBSTDel += clock() - startTime;
    }

    cout << "*** Time Test Hashing With Chaining ***" << endl << endl;
    hChain.printStatistics();
    cout << "Total time over " << U << " insertion attempts ("
         << numFailedInsertions << " failed): " << totalLLHashIns
         << " (may be different with each execution)" << endl;
    cout << "Total time over " << U << " search attempts (" << numFailedSearches
         << " failed): " << totalLLHashSearch
         << " (may be different with each execution)" << endl;
    cout << "Total time over " << U << " deletion attempts ("
         << numFailedDeletions << " failed): " << totalLLHashDel
         << " (may be different with each execution)" << endl;

    cout << endl << "*** Time Test Hashing With Balanced BST ***" << endl
         << endl;
    hBST.printStatistics();
    cout << "Total time over " << U << " insertion attempts ("
         << numFailedInsertions << " failed): " << totalBSTHashIns
         << " (may be different with each execution)" << endl;
    cout << "Total time over " << U << " search attempts (" << numFailedSearches
         << " failed): " << totalBSTHashSearch
         << " (may be different with each execution)" << endl;
    cout << "Total time over " << U << " deletion attempts ("
         << numFailedDeletions << " failed): " << totalBSTHashDel
         << " (may be different with each execution)" << endl;

    cout << endl << "*** Time Test With Balanced BST ***" << endl << endl;
    cout << "Height of BST = " << bst.getTreeHeight() << endl;
    cout << "Total time over " << U << " insertion attempts ("
         << numFailedInsertions << " failed): " << totalBSTIns
         << " (may be different with each execution)" << endl;
    cout << "Total time over " << U << " search attempts (" << numFailedSearches
         << " failed): " << totalBSTSearch
         << " (may be different with each execution)" << endl;
    cout << "Total time over " << U << " deletion attempts ("
         << numFailedDeletions << " failed): " << totalBSTDel
         << " (may be different with each execution)" << endl;
}

int main() {
    testCorrectness();
    cout << endl;
    testHashingTime();
    return 0;
}

