/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "Logger.h"

#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

// ---------- Shared Memory Function Declarations ----------

/* Resets shared memory values. */
void resetSharedMemoryValues();

/* Indicates the largest values across all threads. 
 * 		Uses a mutex to insure only one thread at a time can access. */
void designateLargestValue(int largest);

void fillArrayFromFile(int *array, char* fileName, int startLoc, int valuesToRead);

void storeSortedResultsIntoParentArray(int *parentArray, int *resultArray, int start, int end);

/* Logs the result of a mutex action.
 * @param result - Result of mutex action. 
 * @param lineNumber - Line number that action took place. */
void determineMutexActionResult(int result, int lineNumber);

/* Returns the largest value. */
int getLargestValue();

/* Destroys shared memory values when they are no longer needed. */
void deconstructSharedMemoryValues();

#endif
