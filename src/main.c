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

/**
 * \brief The Entry Point of the Program
 * 
 * \return int The Status Code
 */
int main() {

    ///The Sorts to Test
    const Sort sorts[] = { SELECTION_SORT, INSERTION_SORT, RADIX_SORT };

    Data n[UINT16_MAX/16];

    for(Data i = 0; i < UINT16_MAX/16; i++)
        n[i] = i*16;

    Assert(Max(n, sizeof(n) / 8) < maxof(Data), "You cannot Test Best and Worse");

    BenchmarkSorts(sorts, 3, n, sizeof(n)/sizeof(n[0]));

}

