/**
 * \file SortUtils.h
 * \author Orion Serup (orionserup@gmail.com)
 * \brief Contains the Definitions for the Sort Helpers and Utilities
 * \version 0.1
 * \date 2022-01-08
 * 
 * \copyright Copyright (c) 2022
 * 
 */
#ifndef SORT_UTILS
#define SORT_UTILS

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stddef.h>

#include "SortParams.h"

/// Checks if a Data Type is Signed or Not
#define issigned(t) (((t)(-1)) < ((t) 0))

/// Gets the Unsigned Max of a Type
#define umaxof(t) (((0x1ULL << ((sizeof(t) * 8ULL) - 1ULL)) - 1ULL) | \
                    (0xFULL << ((sizeof(t) * 8ULL) - 4ULL)))

/// Gets the Signed Max of a Type t
#define smaxof(t) (((0x1ULL << ((sizeof(t) * 8ULL) - 1ULL)) - 1ULL) | \
                    (0x7ULL << ((sizeof(t) * 8ULL) - 4ULL)))

/// Gets the Maximum Value of a Type t
#define maxof(t) ((unsigned long long) (issigned(t) ? smaxof(t) : umaxof(t)))

/// Gets the Minimum Value of a Type t
#define minof(t) ((issigned(t) * -maxof(t)) - 1 + !issigned(t)*1)

// Fancy Assert For Much Easier Debug, Prints Custom Message, Line Number and File Name in Red
#ifdef __unix__
/// Linux/MAC Debug Assert, Adds Coloration, Messages, and File and Line Numbers for Better Debugging
#define Assert(condition, msg) assert(condition || !fprintf(stderr, "\x1B[31m%s on Line: %d of File %s\n\x1B[0m", msg, __LINE__, __FILE__))
#else
/// Implementation of any other OS, no Colors but otherwise the same
#define Assert(condition, msg) assert(condition || !fprintf(stderr, "\t%s on Line: %d of File %s\n", msg, __LINE__, __FILE__))
#endif

/**
 * \brief A Structure to Represent a Sorting Algorithm For Easier Handling and Benchmarking
 * 
 */
typedef struct {

    Data* (*const sort)(Data* const array, const size_t size); ///< Function Pointer To the Actual Sort
    const char* const name;   ///< The name of the Sort

} Sort;

/**
 * \brief Finds the maximum value of the array
 * 
 * \param array: Array to look Through
 * \param size: Size of the of the Array
 * \return int: The Maximum Value
 */
Data Max(const Data* const array, const size_t size);

/**
 * \brief Checks to see if an Array is Sorted
 * 
 * \param array: Array to Check
 * \param size: Size of the Array
 * \return true If the Array IS Sorted 
 * \return false If the Array IS NOT Sorted
 */
bool IsSorted(const Data* const array, const size_t size);

/**
 * \brief Finds the Index of the Smallest Value in the Array
 * 
 * \param array: The Array to Search
 * \param size: The Size of the Array
 * \return size_t: The Index With the Minimum Value In the Array 
 */
size_t FindMin(const Data* const array, const size_t size);

/**
 * \brief Swaps the values at the Two Given Pointers
 * 
 * \param val1: The First Value
 * \param val2: The Second Value
 */
void Swap(Data* const val1, Data* const val2);

/**
 * \brief  Prints an Array to a File
 * \note   File can Also be stdout, see \ref PrintArray
 * \param  array: Array to Print
 * \param  size: Size of the Array
 * \retval None
 */
void fPrintArray(FILE* const file, const Data* const array, const size_t size);

/// A Special Case to Print to the Standard output
#define PrintArray(array, size) (fPrintArray(stdout, array, size))

#endif

