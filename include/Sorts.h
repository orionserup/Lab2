/**
 * \file Sorts.h
 * \author Orion Serup (orionserup@gmail.com)
 * \brief 
 * \version 0.1
 * \date 2022-01-10
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#include "QuickSort.h"
#include "RadixSort.h"
#include "HeapSort.h"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "MergeSort.h"

static const Sort allsorts[] = { SELECTION_SORT, HEAP_SORT, RADIX_SORT, QUICK_SORT, MERGE_SORT };
static const size_t numsorts  = sizeof(allsorts)/sizeof(Sort);


