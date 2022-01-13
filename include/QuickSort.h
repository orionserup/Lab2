/**
 * \file QuickSort.h
 * \author Orion Serup (orionserup@gmail.com)
 * \brief Contains the definition of the Quick Sort Function and its Helpers
 * \version 0.1
 * \date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef QUICK_SORT

#include "SortUtils.h"

/**
 * \brief Sorts the Given array using the Quick Sort Algorithm
 * 
 * \param array: Array to Sort
 * \param size: Size of the Array
 * \return Data*: The Array Back, Sorted
 */
Data* QuickSort(Data* const array, const size_t size);

/// Global Sort Definition For Quick Sort 
#define QUICK_SORT (const Sort){ QuickSort, "QuickSort" }

#endif
