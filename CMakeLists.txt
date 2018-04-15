cmake_minimum_required(VERSION 3.9.6)
project(cs223_project2)

set(CMAKE_CXX_STANDARD 11)


add_executable(part1 TestHashing.cpp AVL.h Hashing.h HashingWithAVL.h HashingWithLL.h LinkedList.h PrimeGeneration.h)
add_executable(part2-3 TestHeap.cpp Heap.h KSortAlgo.h)
