/**
 * @file SortTimer.c
 * @author Orion Seurp (orionserup@gmail.com)
 * @brief 
 * @version 0.1
 * @date 07-01-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "SortBenchmark.h"

#include <time.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

void WriteSortDataToFile(FILE* const file, const SortData* const times, const size_t size);

/**
 * @brief 
 * 
 */
static const size_t n[] = {

    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 20, 30, 40, 50, 60, 70, 80, 90,
    100, 200, 300, 400, 500, 600, 700, 800, 900,
    1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
    10000, 20000, 30000, 40000, 50000, 60000, 7000, 80000, 90000

};

static const size_t num_trials = sizeof(n)/sizeof(n[0]);

void BenchmarkSorts(const Sort* const sorts, const size_t numsorts) {

    SortData besttimes[100];
    SortData worsttimes[100];
    SortData avetimes[100];

    char buffer[100];

    for(size_t sortnum = 0; sortnum < numsorts; sortnum++) {

        Sort sort = sorts[sortnum];

        char* prefix = "../data/";
        size_t offset = strlen(prefix) + strlen(sort.name);

        strcpy(buffer, prefix);
        strcat(buffer, sort.name);        

        strcpy(buffer + offset, "Best.csv");
        FILE* best = fopen(buffer, "w");

        strcpy(buffer + offset, "Worst.csv");
        FILE* worst = fopen(buffer, "w");

        strcpy(buffer + offset, "Ave.csv");
        FILE* ave = fopen(buffer, "w");

        for(size_t i = 0; i < num_trials; i++) {

            worsttimes[i] = TestWorstCase(&sort, n[i]);
            besttimes[i] = TestBestCase(&sort, n[i]);
            avetimes[i] = TestAverageCase(&sort, n[i]);

        }

        WriteSortDataToFile(best, besttimes, num_trials);
        WriteSortDataToFile(worst, worsttimes, num_trials);
        WriteSortDataToFile(ave, avetimes, num_trials);
        
        fclose(ave);
        fclose(best);
        fclose(worst);

   }
}

/// Times a Sort and Returns a Struct with the time and N
SortData TimeSort(int* (*Sort)(int* const array, const size_t size), int* const array, const size_t size) {

    assert(Sort  || !fprintf(stderr, "Invalid Sort Function in Time Sort"));
    assert(array || !fprintf(stderr, "Invalid Testing Array in Time Sort"));

    clock_t begin = clock();
    Sort(array, size);
    clock_t end = clock();

    return (SortData){ .time_ms = (double)(end - begin)*1000.0f/CLOCKS_PER_SEC, .n = size };

}

void WriteSortDataToFile(FILE* const file, const SortData* const times, const size_t size) {

    assert(file  || !fprintf(stderr, "Bad File Pointer in Write Time to File"));
    assert(times || !fprintf(stderr, "Bad Times Array in Write Sort Data to File"));

    for(size_t i = 0; i < size; i++)
        fprintf(file, "%lu,%lf\n", times[i].n, times[i].time_ms);

}

SortData TestBestCase(const Sort* const sort, const size_t n) {

    assert(sort       || !fprintf(stderr, "Invalid Sort Pointer in Best Case Test"));
    assert(sort->Sort || !fprintf(stderr, "Invalid Sort Function Pointer in Best Case Test"));

    int array[n + 1];
    for(int i = 0; i < (int)n; i++)
        array[i] = INT32_MIN + i;
    
    return TimeSort(sort->Sort, array, n);

}

SortData TestWorstCase(const Sort* const sort, const size_t n) {

    assert(sort       || !fprintf(stderr, "Invalid Sort Pointer in Worst Case Test"));
    assert(sort->Sort || !fprintf(stderr, "Invalid Sort Function Pointer in Worst Case Test"));

    int array[n + 1];
    for(int i = 0; i < (int)n; i++)
        array[i] = INT32_MAX - i;
    
    return TimeSort(sort->Sort, array, n);

}

SortData TestAverageCase(const Sort* const sort, const size_t n) {

    assert(sort       || !fprintf(stderr, "Invalid Sort Pointer in Average Case Test"));
    assert(sort->Sort || !fprintf(stderr, "Invalid Sort Function Pointer in Average Case Test"));
    
    srand(clock());

    int array[n + 1];
    for(size_t i = 0; i < n; i++)
        array[i] = rand();

    return TimeSort(sort->Sort, array, n);

}