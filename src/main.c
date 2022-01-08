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

/**
 * @brief 
 * 
 * @return int 
 */
int main() {

    Sort Selection = { .Sort = SelectionSort, .name = "SelectionSort"};
    Sort Insertion = { .Sort = InsertionSort, .name = "InsertionSort"};

    const Sort sorts[] = { Selection, Insertion };
    const size_t numsorts = 2;

    BenchmarkSorts(sorts, numsorts);

}
