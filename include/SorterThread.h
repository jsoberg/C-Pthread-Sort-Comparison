/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */

#include <stdio.h>

#ifndef SORTER_THREAD_H
#define SORTER_THREAD_H

// ---------- Macro Declaration ----------

/* @return - Returns the length of the given array. */
#define LENGTH(x)  (sizeof(x) / sizeof(x[0]))

// ---------- Struct Declaration ----------

/* Structure used for merge thread parameters. */
typedef struct {
    int *array;
    int *result;
    int numSegments;
    int arrayLength;
} MergeThreadParameters;

/* Structure used for sorting thread parameters. */
typedef struct {
    int *nums;
    int start;
    int end;
} SortThreadParameters;

// ---------- Function Declaration ----------

/* Function to execute merging of segmentally sorted array in a thread. */
void *executeMergeThread(void *params);

/* Merges segmentally sorted array into a completely sorted array, 
 * 		storing the complete sorted array in result. */
void merge(int *nums, int *result, int numSegments, int length);

/* Fills sortedSegments with start locations for the calculated sorted segments 
 * 		in the segmentally sorted array. */
void fillStartLocationsArrayForSegments(int *sortedSegments, int numSegments, int arrayLength);

/* Function to execute the sort in a thread. */
void *executeSortThread(void *params);

// ---------- Sorting Function Declarations ----------

/* Sorts an array of integers using the quick sort algorithm. */
void quickSort(int *nums, int start, int end);

int partition(int *nums, int start, int end);

void swap(int *a, int *b);

#endif
