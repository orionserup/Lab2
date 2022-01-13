/**
 * \file MergeSort.c
 * \author Orion Serup (orionserup@gmail.com)
 * \brief 
 * \version 0.1
 * \date 01-12-2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#include "MergeSort.h"

Data* MergeSort(Data* const array, const size_t size) {

    Assert(array, "Invalid Array in Merge Sort");

    if(size < 2) return array; // if there are only 0 or one elements it is already sorted

    return array;

}

