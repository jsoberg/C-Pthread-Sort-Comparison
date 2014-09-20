/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Logger.h"
#include "RandomNumberFileGenerator.h"
#include "SorterThread.h"

#ifndef MAIN_H
#define MAIN_H

// Function declarations

/* Generates file of numsToGenerate random integers and fill 
 * 		an array with the generated integers. */
void generateFileAndFillArray(int* nums, int numsToGenerate);

// Test Function Declarations

void printArray(int* nums, int length);

static void sortTest(int* nums, int length);

#endif
