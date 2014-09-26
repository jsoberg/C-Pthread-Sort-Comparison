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

/* Fills an array with integers from file fileName from a specified start location to a 
 * 		specified end location. */
void fillArrayFromFile(int *array, char* fileName, int startLoc, int valuesToRead);

/* Stores sorted results in corresponding area of parent array. */
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
