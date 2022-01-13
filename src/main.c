/**
 * \file main.c
 * \author Orion Serup (orionserup@gmail.com)
 * \brief Contains the main function
 * \version 0.1
 * \date 07-01-2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

/**
 * \mainpage EECS 114 Sorts and Benchmarking
 * 
 * This Project, as a part of EECS 114 at UCI tries to implement many common sorts in C. \n
 * It Implements Insertion, Radix, Heap, and Selection Sort, as well as more to come \n \n
 *  
 * \ref RadixSort \n
 * \ref HeapSort \n
 * \ref InsertionSort \n
 * \ref SelectionSort \n \n
 * 
 * The project also defines a way to log and benchmark sorts. It creates generalized sorts and provides structures for testing and timing. \n \n
 * 
 * \ref Sort   \n
 * \ref TimeSort \n
 * \ref BenchmarkSorts \n
 * \ref TestBestCase \n
 * \ref TestWorstCase \n
 * \ref TestAverageCase \n \n
 * 
 * It also Provides Common Utilities for Other Users and Use Cases \n \n
 * 
 * \ref SortUtils.h \n \n \n
 * 
 * \author Orion Serup (orionserup@gmail.com)
 *  
 */

#include "Sorts.h"
#include "SortBenchmark.h"

#define MIN 0
#define MAX 10
#define STEP 1
#define SIZE (MAX - MIN)/STEP

/**
 * \brief The Entry Point of the Program
 * 
 * \return int The Status Code
 */
int main() {

    Sort sorts[] = { INSERTION_SORT, RADIX_SORT, SELECTION_SORT };
    const size_t numsorts = sizeof(sorts)/sizeof(Sort);

    Data n[SIZE];

    for(Data i = 0; i < SIZE; i++)
        n[i] = MIN + STEP * i;

    BenchmarkSorts(sorts, numsorts, n, SIZE, 1);


}

