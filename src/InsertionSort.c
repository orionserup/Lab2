/**
 * \file InsertionSort.c
 * \author Orion Serup (orionserup@gmail.com)
 * \brief Contains the Implementation of the Insertion sort and its Helpers
 * \version 0.1
 * \date 07-01-2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */
#include "InsertionSort.h"

Data* InsertionSort(Data* const array, const size_t size) {
    // If there is a Print the Message and Break the Program
    Assert(array, "Invalid Array In the Insertion Sort"); 

    if(size < 2) return array; // if there are one or zero elements then return the array, it is sorted

    #ifdef DEBUG_INSERTION
    PrintArray(array, size);
    #endif

    Data val; // Store a temporary to store the current value
    for(size_t j, i = 1; i < size; i++) { // Go through every element starting from the second

        val = array[i]; // store the element at that index

        // Go Back From that Index, if you find a number that is smaller than the current value then
        // You place the current element there, this requires shifting the array, that is what this loop does
        for(j = i - 1; (array[j] > val) && (j != SIZE_MAX); j--) 
            array[j + 1] = array[j];                   

        array[j + 1] = val; // Insert the Element where it needs to be (thus insertion sort)

    }

    #ifdef DEBUG_INSERTION
    PrintArray(array, size);
    printf("Sorted: %s\n", IsSorted(array, size)? "True": "False");
    #endif
    
    // Once Every Element is in the Order Where all of the numbers before it are lesser then return the sorted array
    return array;

}
