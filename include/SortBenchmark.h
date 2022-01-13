/**
 * \file SortBenchmark.h
 * \author Orion Serup (orionserup@gmail.com)
 * \brief Contains the Definition fo the Sort Benchmark and its helpers
 * \version 0.1
 * \date 07-01-2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef SORT_BENCHMARK
#define SORT_BENCHMARK

#include "SortUtils.h"

/**
 * \brief Custom Struct to Store the Data of the Sort
 * 
 */
typedef struct {

    double time_ms; ///< The Time The Sort Took
    size_t n;       ///< The Number of Elements in the Array

} SortData;

/**
 * \brief Times the Sort Given the Parameters 
 * 
 * \param Sort: Sort Function to Time 
 * \param array: Array to Feed the Sort
 * \param size: Size of the Array to Feed the Sorter
 * \return SortData: Time to sort in Seconds and the number of elements, n
 */
SortData TimeSort(Data* (*Sort)(Data* const array, const size_t size), Data* const array, const size_t size);

/** 
 * \brief Benchmarks Every Sort in an Array A Given Number of times 
 * 
 * Takes a Sort and runs it's Best, Worst, and Average Case for every n defined in trials
 * 
 * The Benchmark wil then generate CSV files with data for the Best, Worst, and Average Case. These will
 * be labelled as ${sort.name}[Best, Avg, Worst].csv. The Data can be graphed using the python utility script in the 
 * tools folder. It will generate a .png Graph for every .csv File and put it in the same directory 
 * 
 * \param sort: The Sort To Benchmark
 * \param trials: An Array of values of N to Test the sort with
 * \param numtrials: The Number of Times to Benchmark the Sort, Adds all of the Data to One File
 * \param numtimes: The Number of times to repeat the benchmark
 */
void BenchmarkSort(const Sort sort, const Data* const trials, const size_t numtrials, const size_t numtimes);

/**
 * \brief Benchmarks a Sort by Timing a Best, worst, and average case for all array sizes defined in trials
 * 
 * \param sorts: Array of Sorts to Bench
 * \param numsorts: The Number of Sorts
 * \param trials: The Array full of array size values for the benchmark
 * \param numtrials: The Number of elements in the trials array
 * \param numtimes: The Number of times to repeat the benchmark for each sort
 */
void BenchmarkSorts(const Sort* const sorts, const size_t numsorts, const Data* const trials, const size_t numtrials, const size_t numtimes);

/**
 * \brief  Times the Given Sort for When the Array is Already sorted
 * \note   Fills the array from 0 to n
 * \param  sort: The Sort to Test
 * \param  n: The Number of Elements to test it with
 * \retval SortData: How Long it Took and How many elements it proccessed
 */
Data* GenerateBestCase(Data* const array, const size_t n);

/**
 * \brief  Tests the Sort in the Worst Case (Reverse Order)
 * 
 * \param  sort: Sort to Test
 * \param  n: Number of elements to test it with
 * \retval SortData: The Time it tool and how many elements it procossed
 */
Data* GenerateWorstCase(Data* const array, const size_t n);

/**
 * \brief  Tests a Sort for the Average Case (Random Values)
 * \note   Fills an Array of size n with rand() generated numbers
 * \param  sort: The Sort to Test
 * \param  n: The Number of Elements to test
 * \retval SortData: How Long it took and how many elements were processed
 */
Data* GenerateAverageCase(Data* const array, const size_t n);

#endif
