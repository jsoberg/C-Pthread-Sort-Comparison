/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "Logger.h"
#include "RandomNumberFileGenerator.h"
#include "SorterThread.h"

#ifndef MAIN_H
#define MAIN_H

// Function declarations

/* Generates file of numsToGenerate random integers and fill 
 * 		nums with the generated integers. */
void generateFileAndFillArray(int* nums, int numsToGenerate);

/* Executes sorting threads. Uses numThreads threads. 
 * @param numThreads - Number of threads that were executed when sorting the array. 
 * @param array - Array of random integers to sort.
 * @param arrayLength - Length of array. */
void startSortingThreads(int numThreads, int* array, int arrayLength);

/* Executes merging thread. 
 * @param numThreads - Number of threads that were executed when sorting the array. 
 * @param array - Segmentally sorted array. 
 * @param resultArray - Array to store merge results. 
 * @param arrayLength - The length of segmentally sorted array and result array. */
void startMergeThread(int numThreads, int* array, int* resultArray, int arrayLength);

/* Logs the result of a thread action. If unsuccessful, the log will be fatal.
 * @param result - Result of thread action.
 * @param threadNum - Thread number. 
 * @param lineNumber - Line number that action took place. */
void determineThreadActionResult(int result, int threadNum, int lineNumber);

// Test Function Declarations

void printArray(int* nums, int start, int end);

#endif
