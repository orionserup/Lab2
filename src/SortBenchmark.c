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
#ifdef PARALLEL
#include <omp.h>
#endif

// Writes an Array of SortData to a File
static void WriteSortDataToFile(FILE* const file, const SortData* const times, const size_t size);

// Benchmarks all all of the sorts in an array a number of times 
void BenchmarkSorts(const Sort* const sorts, const size_t numsorts, const Data* const trials, const size_t numtrials, const size_t numtimes) {

    #ifdef PARALLEL
    #pragma omp parallel for
    #endif
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

    strcpy(buffer, path); // copy the path to the buffer
    strcat(buffer, sort.name); // add the Sort Name to the Name       

    strcpy(buffer + offset, "Best.csv"); // Add Best for the Best Case Data
    FILE* best = fopen(buffer, "w");
    
    // repeat for Worst and Average Case
    strcpy(buffer + offset, "Worst.csv");
    FILE* worst = fopen(buffer, "w");

    strcpy(buffer + offset, "Avg.csv");
    FILE* ave = fopen(buffer, "w");

    #ifdef LOG
    strcpy(buffer + offset, ".log");
    FILE* log = fopen(buffer, "w");
    fprintf(log, "%s Log \n%zu Trials per Run \nAveraged Over %zu Runs\n\n", sort.name, numtrials, numtimes);
    clock_t start = clock();
    #endif

    #ifndef VLA // We have to use malloc in windows over VLAs
    SortData* besttimes = malloc(numtrials * numtimes * sizeof(SortData));  // arrays to store the sorting results
    SortData* worsttimes = malloc(numtrials * numtimes * sizeof(SortData));
    SortData* avetimes = malloc(numtrials * numtimes * sizeof(SortData));

    Data* array = malloc(Max(trials, numtrials) * sizeof(Data));
    #else
    SortData besttimes[numtrials * numtimes]; // arrays to store the sorting results
    SortData worsttimes[numtrials * numtimes];
    SortData avetimes[numtrials * numtimes];

    Data array[Max(trials, numtrials) * sizeof(Data)];
    #endif

    #ifdef PARALLEL
    #pragma omp parallel for
    #endif
    for(size_t i = 0; i < numtrials; i++) {

        for(size_t j = 0; j < numtimes; j++) {
            
            GenerateWorstCase(array, trials[i]);
            #ifdef LOG
            fputs("Before ", log);
            fPrintArray(log, array, trials[i]);
            #endif
            worsttimes[i + j * numtrials] = TimeSort(sort.sort, array, trials[i]);
            #ifdef LOG
            fputs("After ", log);
            fPrintArray(log, array, trials[i]);
            fprintf(log, "%ld Elements in %lf Milliseconds\n", worsttimes[i + j * numtrials].n, worsttimes[i + j * numtrials].time_ms);
            fprintf(log, "Sorted: %s\n\n", IsSorted(array, trials[i])? "True": "False");
            #endif
            
            GenerateAverageCase(array, trials[i]);
            #ifdef LOG
            fputs("Before ", log);
            fPrintArray(log, array, trials[i]);
            #endif
            avetimes[i + j * numtrials] = TimeSort(sort.sort, array, trials[i]); // Its sorted after this
            #ifdef LOG
            fputs("After ", log);
            fPrintArray(log, array, trials[i]);
            fprintf(log, "%ld Elements in %lf Milliseconds\n", avetimes[i + j * numtrials].n, avetimes[i + j * numtrials].time_ms);
            fprintf(log, "Sorted: %s\n\n", IsSorted(array, trials[i])? "True": "False");
            #endif
            
            besttimes[i + j * numtrials] = TimeSort(sort.sort, array, trials[i]);

        }
    }

    for(size_t i = 0; i < numtrials; i++) { // Take the Average of all the times 

        for(size_t j = 1; j < numtimes; j++) { // sum up the elements

            worsttimes[i].time_ms += worsttimes[ i + j * numtrials].time_ms;  
            avetimes[i].time_ms += avetimes[i + j * numtrials].time_ms;
            besttimes[i].time_ms += besttimes[i + j * numtrials].time_ms;
        
        }

        worsttimes[i].time_ms /= numtimes;  // divide the sum by the number of elements
        besttimes[i].time_ms /= numtimes;
        avetimes[i].time_ms /= numtimes;

    }

    WriteSortDataToFile(best, besttimes, numtrials);
    WriteSortDataToFile(worst, worsttimes, numtrials);
    WriteSortDataToFile(ave, avetimes, numtrials);

    #ifndef VLA
    free(besttimes);
    free(worsttimes);
    free(avetimes);

    free(array);
    #endif

    fclose(best);
    fclose(worst);
    fclose(ave);

    #ifdef LOG
    fprintf(log, "Benchmark Finished: Took %lf Milliseconds", (clock() - start)*1000.0f/CLOCKS_PER_SEC);
    fclose(log);
    #endif

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

    for(Data i = 0; i < n; i++)
        array[i] = maxof(Data) - i - 200; // fill the array from INT_MAX to INT_MAX - n

    return array;

}

// Fills an Array with random Data
Data* GenerateAverageCase(Data* const array, const size_t n) {

    Assert(array, "Invalid Array Pointer in Average Case Generator");
    
    srand(clock()); // seed the random generator 

    for(Data i = 0; i < n; i++)
        array[i] = rand() & maxof(Data);  // fill the array with n random numbers

    return array; // Time the Sort and Return the Result

}
