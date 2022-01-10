/**
 * \file RadixSort.h
 * \author your name (you@domain.com)
 * \brief 
 * \version 0.1
 * \date 2022-01-07
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef RADIX_SORT
#define RADIX_SORT

#include "SortUtils.h"

/**
 * \brief  Sorts the Given Array Using the Radix Sort with the Radix Being a Base 2 Number
 * \note   The Radix Can Be Adjusted By Changing the RADIX_POW Macro, the radix Will be two to that power
 * \param  array: Array to sort
 * \param  size: Size of the array
 * \return int*: The Array Back at the end
 */
int* RadixSort(int* const array, const size_t size);

/**
 * \brief  Sorts a Given Array by its nth placed digits
 * \note   Uses a faster algorithm than a traditional Counting Sort by using Base 2 Based methods
 * \param  array: The Array to Sort
 * \param  size: The Size of the Array to Sort
 * \param  place: The Number Place to Sort From (Applies to Every Base System(aka Radix))
 * \return int*: The Array Back At the End
 */
int* CountingSort(int* const array, const size_t size, const size_t place);


#endif