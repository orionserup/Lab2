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
 * It Implements the following sorts as well as more to come \n \n
 *  
 * \ref RadixSort \n
 * \ref HeapSort \n
 * \ref InsertionSort \n
 * \ref SelectionSort \n
 * \ref QuickSort \n
 * \ref MergeSort \n
 * \n
 * 
 * The project also defines a way to log and benchmark sorts. It creates generalized sorts and provides structures for testing and timing. \n \n
 * 
 * \ref Sort   \n
 * \ref TimeSort \n
 * \ref BenchmarkSorts \n
 * \ref BenchmarkSort \n \n
 * It also Provides Common Utilities for Other Users and Use Cases \n \n
 * 
 * \ref SortUtils.h \n \n \n
 * 
 * \author Orion Serup (orionserup@gmail.com)
 *  
 */

#include "Sorts.h"
#include "SortBenchmark.h"

/// The Minimum Number of Elements to Test
#define MIN 100
/// The Maximum Number of Elements to Test
#define MAX 10000
/// How Far Apart Two Trials should be
#define STEP 100
/// How Big of an array is needed to store this data
#define SIZE (MAX - MIN) / STEP

/**
 * \brief The Entry Point of the Program
 * 
 * \return int: The Status Code
 */
int main() {

    Sort sorts[] = { RADIX_SORT, MERGE_SORT, SELECTION_SORT };
    const size_t numsorts = sizeof(sorts)/sizeof(Sort);

    Data n[SIZE];
    for(Data i = 0; i < SIZE; i++)
        n[i] = MIN + STEP * i;

    BenchmarkSorts(sorts, numsorts, n, SIZE, 10);

    return EXIT_SUCCESS;

}

