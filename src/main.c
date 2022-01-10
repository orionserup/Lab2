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

#include "SelectionSort.h"
#include "InsertionSort.h"
#include "RadixSort.h"
#include "HeapSort.h"
#include "QuickSort.h"
#include "SortBenchmark.h"

/**
 * \brief The Entry Point of the Program
 * 
 * \return int The Status Code
 */
int main() {

    Sort Selection = { .sort = SelectionSort, .name = "SelectionSort"};
    Sort Insertion = { .sort = InsertionSort, .name = "InsertionSort"};
    Sort Heap = { .sort = HeapSort, .name = "HeapSort"}; 
    Sort Radix = { .sort = RadixSort, .name = "RadixSort"};
    Sort Quick = { .sort = QuickSort, .name = "QuickSort"};

    const Sort sorts[] = { Radix, Insertion, Selection, Quick, Heap };
    const size_t numsorts = sizeof(sorts)/sizeof(sorts[0]);

    BenchmarkSorts(sorts, numsorts, 1);

}
