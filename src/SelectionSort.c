/**
 * \file SelectionSort.c
 * \author Orion Serup (orionserup@gmail.com)
 * \brief Contains the Implementation of the Selection sort
 * \version 0.1
 * \date 07-01-2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#include "SelectionSort.h"

Data* SelectionSort(Data* const array, const size_t size) {

    Assert(array, "Invalid Array in Selection Sort");

    if(size < 2) return array; // if the array is only 0 or one elements it's already sorted

    #ifdef DEBUG_SELECTION
    PrintArray(array, size);
    #endif

    for(size_t i = 0; i < size - 1; i++)  // go through each element
        Swap(array + i, array + FindMin(array + i, size - i) + i); // at each index find the smallest value and swap the current value with that one
    
    #ifdef DEBUG_SELECTION
    PrintArray(array, size);
    printf("Sorted: %s\n", IsSorted(array, size)? "True": "False");
    #endif

    return array; // return the sorted array

}
