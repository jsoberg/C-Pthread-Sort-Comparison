/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */

#ifndef SORTER_THREAD_H
#define SORTER_THREAD_H

// Macro Declaration

/* @return - Returns the length of the given array. */
#define LENGTH(x)  (sizeof(x) / sizeof(x[0]))

// Function Declaration

/* Sorts an array of integers using the quick sort algorithm. */
void sort(int *nums, int n);

#endif
