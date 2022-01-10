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

// Writes an Array of SortData to a File
static void WriteSortDataToFile(FILE* const file, const SortData* const times, const size_t size);

/**
 * \brief All of The Test Cases for the Benchmark
 * 
 */
static const size_t n[] = {

    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 20, 30, 40, 50, 60, 70, 80, 90, 
    100, 200, 300, 400, 500, 600, 700, 800, 900,
    1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000

};
/// The Number of Cases we will be running
static const size_t num_trials = sizeof(n)/sizeof(n[0]);

// Benchmarks all all of the sorts in an array a number of times 
void BenchmarkSorts(const Sort* const sorts, const size_t numsorts, const size_t numtimes) {

    SortData besttimes[num_trials];  // arrays to store the sorting results
    SortData worsttimes[num_trials];
    SortData avetimes[num_trials];

    char buffer[100];  // Buffer for creating the file name

    for(size_t sortnum = 0; sortnum < numsorts; sortnum++) {

        Sort sort = sorts[sortnum];  // Get the nth Sort

        char* prefix = "../data/";
        size_t offset = strlen(prefix) + strlen(sort.name);

        strcpy(buffer, prefix); // copy the path to the buffer
        strcat(buffer, sort.name); // add the Sort Name to the Name       

        strcpy(buffer + offset, "Best.csv"); // Add Best for the Best Case Data
        FILE* best = fopen(buffer, "w"); // Open the Best Case Data File

        // repeat for Worst and Average Case
        strcpy(buffer + offset, "Worst.csv");
        FILE* worst = fopen(buffer, "w");

        strcpy(buffer + offset, "Ave.csv");
        FILE* ave = fopen(buffer, "w");

        // Repeat numtimes times
        for(size_t times = 1; times <= numtimes; times++) {

            // for every value in n we get the best, worst and average case time
            for(size_t i = 0; i < num_trials; i++) {

                worsttimes[i] = TestWorstCase(&sort, n[i]);
                besttimes[i] = TestBestCase(&sort, n[i]);
                avetimes[i] = TestAverageCase(&sort, n[i]);

            }

            // Write All of the Data to their respective files
            WriteSortDataToFile(best, besttimes, num_trials);
            WriteSortDataToFile(worst, worsttimes, num_trials);
            WriteSortDataToFile(ave, avetimes, num_trials);
        
        }
        
        // Close all of the Files
        fclose(ave);
        fclose(best);
        fclose(worst);

   }
}

/// Times a Sort and Returns a Struct with the time and N
SortData TimeSort(int* (*Sort)(int* const array, const size_t size), int* const array, const size_t size) {

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

    int array[n + 1]; // Create your array big enough so there is no memory issue
    for(int i = 0; i < (int)n; i++) 
        array[i] = i;  // fill the array from 0 to n
    
    return TimeSort(sort->sort, array, n); // Time the Sort and return the results

}

// Tests the Sort for the Worst Case ( Reverse Ordered )
SortData TestWorstCase(const Sort* const sort, const size_t n) {

    Assert(sort, "Invalid Sort Pointer in Worst Case Test");
    Assert(sort->sort, "Invalid Sort Function Pointer in Worst Case Test");

    int array[n + 1]; // create testing array
    for(int i = 0; i < (int)n; i++)
        array[i] = INT32_MAX - i; // fill the array from INT_MAX to INT_MAX - n
    
    return TimeSort(sort->sort, array, n); // return the Timing Result

}

// Tests the Sort for the Average Case ( Random Data)
SortData TestAverageCase(const Sort* const sort, const size_t n) {

    Assert(sort, "Invalid Sort Pointer in Average Case Test");
    Assert(sort->sort, "Invalid Sort Function Pointer in Average Case Test");
    
    srand(clock()); // seed the random generator 

    int array[n + 1];
    for(size_t i = 0; i < n; i++)
        array[i] = rand();  // fill the array with n random numbers

    return TimeSort(sort->sort, array, n); // Time the Sort and Return the Result

}