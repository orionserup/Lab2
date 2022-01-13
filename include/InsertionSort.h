/**
 * \file InsertionSort.h
 * \author Orion Serup (orionserup@gmail.com)
 * \brief Contains the Definitions for the Insertion Sort Function
 * \version 0.1
 * \date 06-01-2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */
#ifndef INSERTION_SORT

#include "SortUtils.h"

/**
 * \brief Sorts the given array using the Insertion sort algorithm
 * 
 * \param array: The Array to Sort
 * \param size: The Size of the Array
 * \return Data*: The Array Back 
 */
Data* InsertionSort(Data* const array, const size_t size);

/// Our Global Insertion Sort Object
#define INSERTION_SORT (const Sort){ InsertionSort,"InsertionSort" }

#endif
