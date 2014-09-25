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
#include "SharedMemoryController.h"

#ifndef MAIN_H
#define MAIN_H

// Function declarations

/* Generates file of numsToGenerate random integers with each integer
 * 		being formatted to a width of numFormatWidth. */
void generateRandomFile(int numsToGenerate, int numFormatWidth);

/* Executes sorting threads. Uses numThreads threads. 
 * @param numThreads - Number of threads that were executed when sorting the array. 
 * @param array - Array of random integers to sort.
 * @param arrayLength - Length of array. 
 * @param fileName - Name of file to read. */
void startSortingThreads(int numThreads, int* array, int arrayLength, char* fileName);

/* Executes merging thread. 
 * @param numThreads - Number of threads that were executed when sorting the array. 
 * @param array - Segmentally sorted array. 
 * @param resultArray - Array to store merge results. 
 * @param arrayLength - The length of segmentally sorted array and result array. */
void startMergeThread(int numThreads, int* array, int* resultArray, int arrayLength);

/* Logs the result of a thread action. If unsuccessful, the log will be fatal.
 * @param result - Result of thread action.
 * @param lineNumber - Line number that action took place. 
 * @param message - Message to log. */
void logThreadActionResult(int result, int lineNumber, char* message);

/* Prints the contents of the given array (from location start to location end) to a file. */
int printArrayToFile(char* fileName, int* nums, int start, int end);

#endif
