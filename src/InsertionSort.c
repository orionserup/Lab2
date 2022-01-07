/**
 * @file InsertionSort.c
 * @author Orion Seurp (orionserup@gmail.com)
 * @brief 
 * @version 0.1
 * @date 07-01-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "InsertionSort.h"
#include <assert.h>

int* InsertionSort(int* const array, const size_t size) {

    assert(array || "Invalid Array In the Insertion Sort");

    if(size < 2) return array; // if there are one or zero elements then return the array, it is sorted

    int val;

    for(size_t j, i = 1; i < size; i++) {

        val = array[i];

        for(j = i - 1; array[j] < val && j != SIZE_MAX; j--) 
            array[j + 1] = array[j];                   

        array[j + 1] = val;

    }
    
    return array;

}