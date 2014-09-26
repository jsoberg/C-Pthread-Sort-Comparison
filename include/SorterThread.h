/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include "SharedMemoryController.h"

#ifndef SORTER_THREAD_H
#define SORTER_THREAD_H


// ==================== Macro Declarations ====================


/* @return - Returns the length of the given array. */
#define LENGTH(x)  (sizeof(x) / sizeof(x[0]))


// ==================== Struct Declarations ====================


/* Structure used for merge thread parameters. */
typedef struct {
    int *array;
    int *result;
    int numSegments;
    int arrayLength;
} MergeThreadParameters;

/* Structure used for sorting thread parameters. */
typedef struct {
    int *parentArray;
    int start;
    int end;
    char *fileName;
} SortThreadParameters;


// ==================== Merging Function Declarations ====================


/* Function to execute merging of segmentally sorted array in a thread. */
void *executeMergeThread(void *params);

/* Merges segmentally sorted array into a completely sorted array, 
 * 		storing the complete sorted array in result. */
void merge(int *nums, int *result, int numSegments, int length);

/* Fills sortedSegments with start  and end locations for the calculated sorted segments 
 * 		in the segmentally sorted array. */
void fillStartAndEndLocationsArrayForSegments(int *startSegments, int *endSegments, int numSegments, int arrayLength);

/* Function to execute the sort in a thread. */
void *executeSortThread(void *params);


// ==================== Sorting Function Declarations ====================


/* Sorts an array of integers using the quick sort algorithm. */
void quickSort(int *nums, int start, int end);

/* Executing the 'divide and conquer' scheme of quick sort, finding a 
 * 		pivot value and putting all numbers lower than it to the left,
 *  	all numbers higher than it to the right. */
int partition(int *nums, int start, int end);

/* Swaps to items in an array. */
void swap(int *a, int *b);

#endif
