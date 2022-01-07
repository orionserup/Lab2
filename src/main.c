/**
 * @file main.c
 * @author Orion Seurp (orionserup@gmail.com)
 * @brief 
 * @version 0.1
 * @date 07-01-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "SelectionSort.h"
#include "InsertionSort.h"
#include "SortBenchmark.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
 * @brief 
 * 
 * @return int 
 */
int main() {

    Sort Selection = { .Sort = SelectionSort, .name = "SelectionSort"};
    Sort Insertion = { .Sort = InsertionSort, .name = "InsertionSort"};

    Sort sorts[] = { Selection, Insertion };

    BenchmarkSorts(sorts, 2);

}
