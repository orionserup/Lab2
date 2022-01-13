/**
 * \file SortUtils.c
 * \author Orion Serup (orionserup@gmail.com)
 * \brief Contains the Implementation of Teh Sort Utilities and helpers
 * \version 0.1
 * \date 2022-01-08
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#include "SortUtils.h"

// Finds the maximum value of the array
Data Max(const Data* const array, const size_t size) {

    Assert(array, "Invalid Array in Find Max");

    if(size == 0) return minof(Data); // If there are no elements there is no max
    else if(size == 1) return array[0];  // if there is only one element then its the first
    
    Data max = array[0]; // we choose the max t be the first element to start with
    for(size_t i = 1; i < size; i++) // we go through the array
        if(array[i] > max) // if an element is bigger than the max it becomes the max
            max = array[i];
    
    return max;  // we filtered through and found the max

}

// Swaps the values pointed at
void Swap(Data* const val1, Data* const val2) {

    Assert(val1, "Invalid First Value Pointer in Swap");
    Assert(val2, "Invalid Second Value Pointer in Swap");

    if(val1 == val2) return; // if they are pointing to the same thing then don't do anything

    int temp = *val1;
    *val1 = *val2;
    *val2 = temp;

}

// Gets the Index of the Smallest Element
size_t FindMin(const Data* const array, const size_t size) {

    Assert(array, "Invalid Array In Find MinValue");

    if(size < 2) return size; // If the element is 1 or zero the minimum is that element

    size_t min = 0; // we pick the initial min to be element 0
    for(size_t i = 1; i < size; i++) // we go through the array
        if(array[min] > array[i]) // if an element is less than the min it becomes the new min
            min = i;

    return min;  // after we go through the array mi is actually the min

}

// Prints the Array to a file
void fPrintArray(FILE* const file, const Data* const array, const size_t size) {

    Assert(file, "Invalid file pointer in fPrintArray");
    Assert(array, "Invalid array in fPrintArray");

    for(size_t i = 0; i < size; i++)  // Goes through the whole array, it it hits the end, place a new line
        fprintf(file, "%ld ", (int64_t)array[i]); // Print Each element to the file

    fputc('\n', file);

}

// Checks if an array is sorted
bool IsSorted(const Data* const array, const size_t size) {

    Assert(array, "Invalid Array in IsSorted");

    if(size < 2) return true; // Arrays with 1 or zero elements are automatically sorted

    for(size_t i = 1; i < size; i++) // goes through the array
        if(array[i - 1] > array[i]) // if the element before the current element is greater than it the it is not sorted
            return false;
    
    return true; // If every element is greater than or equal to the one before then it is sorted

}
