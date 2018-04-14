cmake_minimum_required(VERSION 3.10)
project(cs223_project2)

set(CMAKE_CXX_STANDARD 11)

add_executable(part1 Part1/LinkedList.h Part1/HashingWithLL.h Part1/HashingWithAVL.h Part1/AVL.h Part1/Hashing.h Part1/PrimeGeneration.h Part1/TestHashing.cpp)
add_executable(part2-3 Part2-3/Heap.h Part2-3/KSortAlgo.h Part2-3/TestHead.cpp)
