/**
 * \file HeapSort.h
 * \author Orion Serup (orionserup@gmail.com)
 * \brief Contains the Function Definitions for the Heap Sort and its Helper Functions
 * \version 0.1
 * \date 2022-01-07
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef HEAP_SORT


#include "SortUtils.h"

/**
 * \brief  
 * \note   
 * \param  array: 
 * \param  size: 
 * \retval 
 */
Data* HeapSort(Data* const array, const size_t size);

#define HEAP_SORT (const Sort){ HeapSort, "HeapSort" }

#endif
