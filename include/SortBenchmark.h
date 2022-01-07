/**
 * @file SortTimer.h
 * @author Orion Seurp (orionserup@gmail.com)
 * @brief 
 * @version 0.1
 * @date 07-01-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SORT_BENCHMARK
#define SORT_BENCHMARK

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Custom Struct to Store the Data of the Sort
 * 
 */
typedef struct {

    double time_ms; ///< The Time The Sort Took
    size_t n;       ///< The Number of Elements in the Array

} SortData;

/**
 * @brief 
 * 
 */
typedef struct {

    int* (*Sort)(int* const array, const size_t size); ///< Function Pointer To the Actual SOrt
    const char* name;   ///< The name of the Sort

} Sort;

/**
 * @brief Times the Sort Given the Parameters 
 * 
 * @param Sort: Sort Function to Time 
 * @param array: Array to Feed the Sort
 * @param size: Size of the Array to Feed the Sorter
 * @return SortData: Time to sort in Seconds and the number of elements, n
 */
SortData TimeSort(int* (*Sort)(int* const array, const size_t size), int* const array, const size_t size);

/**
 * @brief 
 * 
 * @param Sort 
 * @param file 
 */
void BenchmarkSorts(const Sort* const sorts, const size_t numsorts);

SortData TestBestCase(const Sort* const sort, const size_t n);
SortData TestWorstCase(const Sort* const sort, const size_t n);
SortData TestAverageCase(const Sort* const sort, const size_t n);


#endif