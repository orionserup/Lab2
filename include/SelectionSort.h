/**
 * @file SelectionSort.h
 * @author Orion Seurp (orionserup@gmail.com)
 * @brief Contains the Prototype for the Selection Sort Function 
 * @version 0.1
 * @date 06-01-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SELECTION_SORT
#define SELECTION_SORT

#include <stdlib.h>

/**
 * @brief Sorts the given Array using the Selection sort algorithm
 * 
 * @param array: The Array to Sort
 * @param size: The Size of the Array
 * @return int*, The Sorted Array
 */
int* SelectionSort(int* const array, const size_t size);


#endif