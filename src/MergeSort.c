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

static Data* Merge(Data* const arr1, const size_t size1, Data* const arr2, const size_t size2);

Data* MergeSort(Data* const array, const size_t size) {

    Assert(array, "Invalid Array in Merge Sort");

    if(size < 2) return array; // if there are only 0 or one elements it is already sorted

    size_t middle = size / 2;

    return Merge(MergeSort(array, middle), middle, MergeSort(array + middle, size - middle),  size - middle);

}

Data* Merge(Data* const arr1, const size_t size1, Data* const arr2, const size_t size2) {

    Assert(arr1, "Invalid First Array In Merge");
    Assert(arr2, "Invalid Second Array in Merge");

    if(arr1 == arr2) return arr1;

    Data* array = (arr1 < arr2)? arr1: arr2;
    Data* temp = malloc(sizeof(Data) * (size1 + size2));

    size_t i = 0, j = 0, index = 0;
    for( ; i < size1 && j < size2; index++) {

        bool leftgoes = arr1[i] <= arr2[j];
        temp[index] = leftgoes? arr1[i]: arr2[j];
        leftgoes? i++: j++;
    
    }

    for(; index < size1 + size2; index++) {

        bool leftgoes = i != size1;
        temp[index] = leftgoes? arr1[i]: arr2[j];
        leftgoes? i++: j++;

    }

    memcpy(array, temp, sizeof(Data) * (size1 + size2)); 
    free(temp);

    return array;

}