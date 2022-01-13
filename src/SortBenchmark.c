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
void BenchmarkSorts(const Sort* const sorts, const size_t numsorts, const Data* const trials, const size_t numtrials, const size_t numtimes) {

    // #pragma omp parallel for
    for(size_t sortnum = 0; sortnum < numsorts; sortnum++)
        BenchmarkSort(sorts[sortnum], trials, numtrials, numtimes);

}

void BenchmarkSort(const Sort sort, const Data* const trials, const size_t numtrials, const size_t numtimes) {

    Assert(sort.sort, "Invalid Sort Function in Sort Benchmark");
    Assert(trials, "Invalid Trials Array In Sort Benchmark");
    Assert(Max(trials, numtrials) <= maxof(Data), "Trials are beyond the size of the data in Sort Benchmark");

    if(numtrials == 0) return;

    char buffer[100];

    #ifdef _MSC_VER // If using the Visual Studio Compiler 
    const char* const path = "..\\..\\data\\";
    #else
    const char* const path = "../data/";
    #endif

    size_t offset = strlen(path) + strlen(sort.name);

    strcpy_s(buffer, sizeof(buffer), path); // copy the path to the buffer
    strcat_s(buffer, sizeof(buffer), sort.name); // add the Sort Name to the Name       

    strcpy_s(buffer + offset, sizeof(buffer) - offset, "Best.csv"); // Add Best for the Best Case Data
    FILE* best;
    if(fopen_s(&best, buffer, "w"))
        printf("Could Not Open File %s For Writing", buffer); // Open the Best Case Data File and catch errors
    
    // repeat for Worst and Average Case
    strcpy_s(buffer + offset, sizeof(buffer) - offset, "Worst.csv");
    FILE* worst;
    if(fopen_s(&worst, buffer, "w"))
        printf("Could Not Open File %s For Writing", buffer);

    strcpy_s(buffer + offset, sizeof(buffer) - offset, "Avg.csv");
    FILE* ave;
    if(fopen_s(&ave, buffer, "w"))
        printf("Could Not Open File %s For Writing", buffer);

    SortData* besttimes = malloc(numtrials * sizeof(SortData));  // arrays to store the sorting results
    SortData* worsttimes = malloc(numtrials * sizeof(SortData));
    SortData* avetimes = malloc(numtrials * sizeof(SortData));

    Data* array = malloc(Max(trials, numtrials) * sizeof(Data));

    for(size_t times = 0; times < numtimes; times++) {

        for(size_t i = 0; i < numtrials; i++) {

            GenerateWorstCase(array, trials[i]);
            worsttimes[i] = TimeSort(sort.sort, array, trials[i]);
        
            GenerateAverageCase(array, trials[i]);
            avetimes[i] = TimeSort(sort.sort, array, trials[i]);
        
            besttimes[i] = TimeSort(sort.sort, array, trials[i]);
    
        }

        WriteSortDataToFile(best, besttimes, numtrials);
        WriteSortDataToFile(worst, worsttimes, numtrials);
        WriteSortDataToFile(ave, avetimes, numtrials);

    }

    free(besttimes);
    free(worsttimes);
    free(avetimes);

    free(array);

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
        fprintf(file, "%zu,%lf\n", times[i].n, times[i].time_ms);

}

// Tests the Sort for the Best Case Scenario (Already Sorted)
Data* GenerateBestCase(Data* const array, const size_t n) {

    Assert(array, "Invalid Array Pointer in Best Case Generator");

    for(Data i = 0; i < n; i++) 
        array[i] = i;  // fill the array from 0 to n
    
    return array; // Time the Sort and return the results

}

// Fills the Array with the Worst Case ( Reverse Ordered )
Data* GenerateWorstCase(Data* const array, const size_t n) {

    Assert(array, "Invalid Array Pointer in Worst Case Test");

    for(Data i = 0; i < (Data)n; i++)
        array[i] = maxof(Data) - i; // fill the array from INT_MAX to INT_MAX - n

// Fills an Array with random Data
Data* GenerateAverageCase(Data* const array, const size_t n) {

    Assert(array, "Invalid Array Pointer in Average Case Generator");
    
    srand(clock()); // seed the random generator 

    for(Data i = 0; i < n; i++)
        array[i] = rand() & maxof(Data);  // fill the array with n random numbers

    return array; // Time the Sort and Return the Result

}
