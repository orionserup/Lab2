/**
 * \file MergeSort.h
 * \author Orion Serup (orionserup@gmail.com)
 * \brief Contains the Definition of Merge Sort
 * \version 0.1
 * \date 01-12-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MERGE_SORT

#include "SortUtils.h"

/**
 * \brief Performs the Merge Sort Algorithm on the Array
 * 
 * \param array: Array to Perform it on 
 * \param size: Size of that array 
 * \return Data*: The Sorted Array Back
 */
Data* MergeSort(Data* const array, const size_t size);

#define MERGE_SORT (const Sort){ MergeSort, "MergeSort" }

#endif
