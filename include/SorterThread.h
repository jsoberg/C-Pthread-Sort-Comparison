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

typedef struct {
    int *nums;
    int start;
    int end;
} SortThreadParameters;

// ---------- Function Declaration ----------

/* Function to execute the sort in a thread. */
void *executeSortThread(void *params);

/* Sorts an array of integers using the quick sort algorithm. */
void quickSort(int *nums, int start, int end);

int partition(int *nums, int start, int end);

void swap(int *a, int *b);

#endif
