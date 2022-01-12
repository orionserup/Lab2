/**
 * \file SortBenchmark.c
 * \author Orion Serup (orionserup@gmail.com)
 * \brief Contains the Implementation of the Sort Bench and its helpers
 * \version 0.1
 * \date 07-01-2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#include "SortBenchmark.h"
#include <omp.h>

// Writes an Array of SortData to a File
static void WriteSortDataToFile(FILE* const file, const SortData* const times, const size_t size);

// Benchmarks all all of the sorts in an array a number of times 
void BenchmarkSorts(const Sort* const sorts, const size_t numsorts, const Data* const trials, const size_t numtrials) {

    #pragma omp parallel for    
    for(size_t sortnum = 0; sortnum < numsorts; sortnum++)
        BenchmarkSort(sorts[sortnum], trials, numtrials);

}

void BenchmarkSort(const Sort sort, const Data* const trials, const size_t numtrials) {

    Assert(sort.sort, "Invalid Sort Function in Sort Benchmark");
    Assert(trials, "Invalid Trials Array In Sort Benchmark");
    Assert(Max(trials, numtrials) <= maxof(Data), "Trials are beyond the size of the data in Sort Benchmark");

    SortData besttimes[numtrials];  // arrays to store the sorting results
    SortData worsttimes[numtrials];
    SortData avetimes[numtrials];

    char buffer[100];

    const char* const path = "../data/";
    size_t offset = strlen(path) + strlen(sort.name);

    strcpy(buffer, path); // copy the path to the buffer
    strcat(buffer, sort.name); // add the Sort Name to the Name       

    strcpy(buffer + offset, "Best.csv"); // Add Best for the Best Case Data
    FILE* best = fopen(buffer, "w"); // Open the Best Case Data File

    // repeat for Worst and Average Case
    strcpy(buffer + offset, "Worst.csv");
    FILE* worst = fopen(buffer, "w");

    strcpy(buffer + offset, "Avg.csv");
    FILE* ave = fopen(buffer, "w");

    #pragma omp parallel for
    for(size_t i = 0; i < numtrials; i++) {

        besttimes[i] = TestBestCase(&sort, trials[i]);
        worsttimes[i] = TestWorstCase(&sort, trials[i]);
        avetimes[i] = TestAverageCase(&sort, trials[i]);

    }

    WriteSortDataToFile(best, besttimes, numtrials);
    WriteSortDataToFile(worst, worsttimes, numtrials);
    WriteSortDataToFile(ave, avetimes, numtrials);

    fclose(best);
    fclose(worst);
    fclose(ave);

}

/// Times a Sort and Returns a Struct with the time and N
SortData TimeSort(Data* (*const Sort)(Data* const array, const size_t size), Data* const array, const size_t size) {

    Assert(Sort, "Invalid Sort Function in Time Sort"); // we need a valid array and sort to time it
    Assert(array, "Invalid Testing Array in Time Sort");

    clock_t begin = clock();  // start timer
    Sort(array, size);        // run the sort
    clock_t end = clock();    // end timer

    // If the Array is Sorted then return the real data otherwise return that the time was the maximum possible to indicate failure
    return IsSorted(array, size) ? 
        (SortData){ .time_ms = (double)(end - begin)*1000.0f/CLOCKS_PER_SEC, .n = size } :
        (SortData){ .time_ms = DBL_MAX, .n = size };

}

// Writes all of the Sort Data to the File
void WriteSortDataToFile(FILE* const file, const SortData* const times, const size_t size) {

    Assert(file, "Bad File Pointer in Write Time to File");
    Assert(times, "Bad Times Array in Write Sort Data to File");

    for(size_t i = 0; i < size; i++)  // For Every Data Point Follow CSV rules
        fprintf(file, "%lu,%lf\n", times[i].n, times[i].time_ms);

}

// Tests the Sort for the Best Case Scenario (Already Sorted)
SortData TestBestCase(const Sort* const sort, const size_t n) {

    Assert(sort, "Invalid Sort Pointer in Best Case Test");
    Assert(sort->sort, "Invalid Sort Function Pointer in Best Case Test");

    Data array[n + 1]; // Create your array big enough so there is no memory issue
    for(Data i = 0; i < (Data)n; i++) 
        array[i] = i;  // fill the array from 0 to n
    
    return TimeSort(sort->sort, array, n); // Time the Sort and return the results

}

// Tests the Sort for the Worst Case ( Reverse Ordered )
SortData TestWorstCase(const Sort* const sort, const size_t n) {

    Assert(sort, "Invalid Sort Pointer in Worst Case Test");
    Assert(sort->sort, "Invalid Sort Function Pointer in Worst Case Test");

    Data array[n + 1]; // create testing array
    for(Data i = 0; i < n; i++)
        array[i] = maxof(Data) - i; // fill the array from INT_MAX to INT_MAX - n
    
    return TimeSort(sort->sort, array, n); // return the Timing Result

}

// Tests the Sort for the Average Case ( Random Data)
SortData TestAverageCase(const Sort* const sort, const size_t n) {

    Assert(sort, "Invalid Sort Pointer in Average Case Test");
    Assert(sort->sort, "Invalid Sort Function Pointer in Average Case Test");
    
    srand(clock()); // seed the random generator 

    Data array[n + 1];
    for(size_t i = 0; i < n; i++)
        array[i] = rand() & maxof(Data);  // fill the array with n random numbers

    return TimeSort(sort->sort, array, n); // Time the Sort and Return the Result

}
