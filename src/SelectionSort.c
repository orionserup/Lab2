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
#include <stdio.h>

static void Swap(int* const val1, int* const val2);
static size_t FindMinValue(const int* const array, const size_t size);

int* SelectionSort(int* const array, const size_t size) {

    assert(array || !fprintf(stderr, "Invalid Array in Selection Sort"));

    if(size < 2) return array;

    for(size_t i = 0; i < size; i++) 
        Swap(&array[FindMinValue(&array[i], size - i) + i], &array[i]);
    
    return array;

}

size_t FindMinValue(const int* const array, const size_t size) {

    assert(array || !fprintf(stderr, "Invalid Array In Find MinValue"));

    if(size < 2) return size;

    size_t min = 0;
    for(size_t i = 1; i < size; i++) 
        if(array[min] > array[i]) 
            min = i;

    return min;

}


void Swap(int* const val1, int* const val2) {

    assert(val1 || !fprintf(stderr, "Invalid First Value Pointer in Swap"));
    assert(val2 || !fprintf(stderr, "Invalid Second Value Pointer in Swap"));

    if(val1 == val2) return;

    int temp = *val1;
    *val1 = *val2;
    *val2 = temp;

}