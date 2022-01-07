/**
 * @file SelectionSort.c
 * @author Orion Seurp (orionserup@gmail.com)
 * @brief 
 * @version 0.1
 * @date 07-01-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "SelectionSort.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

static void Swap(int* const val1, int* const val2);
static size_t FindMinValue(const int* const array, const size_t size);

int* SelectionSort(int* const array, const size_t size) {

    assert(array || "Invalid Array in Selection Sort");

    if(size < 2) return array;

    for(size_t i = 0; i < size; i++) 
        Swap(&array[FindMinValue(&array[i], size - i)], &array[i]);

    return array;

}

size_t FindMinValue(const int* const array, const size_t size) {

    assert(array || "Invalid Array In Find MinValue");

    if(size < 2) return size;

    int min = INT32_MAX;
    size_t index = SIZE_MAX;

    for(size_t i = 0; i < size; i++) {

        if(array[i] < min) {

            min = array[i];
            index = i;

        }        
    }

    return index;

}

void Swap(int* const val1, int* const val2) {

    assert(val1 || "Invalid First Value Pointer in Swap");
    assert(val2 || "Invalid Second Value Pointer in Swap");

    if(val1 == val2) return;

    int temp = *val1;
    *val1 = *val2;
    *val2 = temp;

}