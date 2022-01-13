/**
 * \file RadixSort.c
 * \author Orion Serup (orionserup@gmail.com)
 * \brief Contains the Implentation of Radix Sort and its Helpers
 * \version 0.1
 * \date 2022-01-07
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#include "RadixSort.h"

/// The Actual Radix (aka The Number we are taking the remainder of for the Sort) 
#define RADIX (1 << RADIX_POW)

/// Finds the Number of Counting Sort Iterations Needed to Sort the Number Max
static inline size_t FindNumIterations(Data max);

/// Performs the Super Fast Base 2 Based Radix Sort
Data* RadixSort(Data* const array, const size_t size) {

    Assert(array, "Invalid Array In Radix Sort"); // We have to have a valid array to sort

    if(size < 2) return array; // if the array is 1 element or zero elements its already sorted

    #ifdef DEBUG_RADIX
    PrintArray(array, size);
    #endif

    // We only need to run the Counting Sort as many times as the largest number needs to be run to be sorted 
    size_t n = FindNumIterations(Max(array, size));  

    // Now we run the Counting Sort As many times as needed
    for(size_t i = 0; i < n; i++) // Sort by the ith most significant digit up to the most significant
        CountingSort(array, size, i);

    #ifdef DEBUG_RADIX
    PrintArray(array, size); // if debugging then print the array
    printf("Sorted: %s\n", IsSorted(array, size)? "True": "False");
    #endif

    return array; // return the sorted array

}

/// Performs the Optimized Base 2 Based Counting Sort
Data* CountingSort(Data* const array, const size_t size, const size_t place) {

    // If the Array is NULL or the we will be searching past what is an integer then print the 
    // message to the error console and then break the Program
    Assert(array, "Invalid Array in Counting Sort");
    Assert(place * RADIX_POW <= 8 * sizeof(Data), "Place is Too Large in Counting Sort");

    if(size < 2) return array;
    
    // Array to store the number of numbers that have the digit cooresponding to the index of the array 
    size_t count[RADIX] = {0};
    Data* out = malloc(size * sizeof(Data)); // copy of the input array that we can manipulate

    // Fill the Count Array With The Correct Values (The Number of Times the Array has the number i in its place place)
    for(size_t i = 0; i < size; i++)
        count[(array[i] >> (place * RADIX_POW)) & (RADIX - 1)]++; 
            // Equivalent to array[i]/(Radix^place) % radix for radices of powers of 2, finds the place'th digit

    for(size_t i = 1; i < RADIX; i++) // Creating a Rolling Sum on Count
        count[i] += count[i - 1]; // Every value is the number of counts before it

    for(size_t i = size - 1; i != SIZE_MAX ; i--) {  // Do the Actual Sort

        size_t index = (array[i] >> (place * RADIX_POW)) & (RADIX - 1); // Same as before, gets the place'th digit
        out[count[index] - 1] = array[i]; // The Number of Digits before the place'th digit minus one creates a sorting function 
        count[index]--; // decrement so that we know where to place the next number with the same digit

    }

    memcpy(array, out, sizeof(size * sizeof(Data)));  // copy the temporary output array to the array  
    free(out);

    return array; // return the sorted array

}


/**
 * \brief  Finds the Number of Iterations Needed for a Radix Sort with radix RADIX to sort the number
 * \note   Utility for radix Sort
 * \param  max: Number to Check
 * \retval size_t : The Number of iterations Needed
 */
size_t FindNumIterations(Data max) {

    size_t i = 0;

    while(max) {
    
        max >>= RADIX_POW;
        i++;
    
    }

    return i;

}
