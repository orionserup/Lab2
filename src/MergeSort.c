/**
 * \file MergeSort.c
 * \author Orion Serup (orionserup@gmail.com)
 * \brief Contains the Implementation of Merge Sort and its helpers
 * \version 0.1
 * \date 01-12-2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#include "MergeSort.h"

/**
 * \brief Merges Two Arrays Together with a Shuffle technique to Sort At the Same Time
 * 
 * \param arr1: First Array to Merge
 * \param size1: Size of that Array
 * \param arr2: Second Array to Merge
 * \param size2: Size of that array
 * \return Data*: The Merged Array Back 
 *  */
static Data* Merge(Data* const arr1, const size_t size1, Data* const arr2, const size_t size2);

// Sorts the Given Array using the Merge Sort Algorithm
Data* MergeSort(Data* const array, const size_t size) {

    Assert(array, "Invalid Array in Merge Sort"); // we need a validarray to sort it

    if(size < 2) return array; // if there are only 0 or one elements it is already sorted

    size_t middle = size / 2; // find the mid point

    // We recursively reduce the array into size arrays of 1 element and merge them until we are back at the full size
    return Merge(MergeSort(array, middle), middle, MergeSort(array + middle, size - middle),  size - middle);

}

// Merges Two Arrays and Sorts them along the Way
Data* Merge(Data* const arr1, const size_t size1, Data* const arr2, const size_t size2) {

    Assert(arr1, "Invalid First Array In Merge");  // we need valid arras to merge them
    Assert(arr2, "Invalid Second Array in Merge");

    if(arr1 == arr2) return arr1; // If they are the same pointer they are already merged

    Data* array = (arr1 < arr2)? arr1: arr2; // which ever pointer is lower is the base of the array

    #ifndef VLA // if we are using MSVC we cant use VLAs
    Data* temp = malloc(sizeof(Data) * (size1 + size2));
    #else
    Data temp[size1 + size2]; // temporary array to fill with sorted values
    #endif

    size_t i = 0, j = 0, index = 0;
    for( ; i < size1 && j < size2; index++) { // go through and fill in the temp with the numbers in order

        bool leftgoes = arr1[i] <= arr2[j];  // if the left array has the smaller number
        temp[index] = leftgoes? arr1[i]: arr2[j]; // if left is smaller place it,if not take the right 
        leftgoes? i++: j++; // if we took the left advance the index otherwise advance the right index
    
    }
    // once we hit the end of one of the arrays
    for(; index < size1 + size2; index++) {

        bool leftgoes = i != size1; // if there are still elements on the left
        temp[index] = leftgoes? arr1[i]: arr2[j]; // if yes place them into the array, if no place the right elements
        leftgoes? i++: j++; // increment the cooresponding index

    }

    memcpy(array, temp, sizeof(Data) * (size1 + size2)); // copy the temp array to the actual array
    
    #ifndef VLA // Windows Compiler Compatibility
    free(temp);
    #endif

    return array;

}