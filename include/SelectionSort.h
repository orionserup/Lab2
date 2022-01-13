/**
 * \file SelectionSort.h
 * \author Orion Serup (orionserup@gmail.com)
 * \brief Contains the Prototype for the Selection Sort Function 
 * \version 0.1
 * \date 06-01-2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef SELECTION_SORT

#include "SortUtils.h"

/**
 * \brief Sorts the given Array using the Selection sort algorithm
 * 
 * \param array: The Array to Sort
 * \param size: The Size of the Array
 * \return Data*, The Sorted Array
 */
Data* SelectionSort(Data* const array, const size_t size);

/// Global Sort Definition for Selection Sort
#define SELECTION_SORT (const Sort){ SelectionSort, "SelectionSort"}

#endif
