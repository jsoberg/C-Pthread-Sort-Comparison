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

/* Executes sorting threads. Uses numThreads threads. */
void startSortingThreads(int numThreads, int* array, int arrayLength);

/* Logs the result of a thread action. If unsuccessful, the log will be fatal.
 * @param result - Result of thread action.
 * @param threadNum - Thread number. 
 * @param lineNumber - Line number that action took place. */
void determineThreadActionResult(int result, int threadNum, int lineNumber);

// Test Function Declarations

void printArray(int* nums, int start, int end);

static void sortTest(int* nums, int length);

#endif
