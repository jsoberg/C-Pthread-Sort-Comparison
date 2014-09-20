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

// Test Function Declarations

void printArray(int* nums, int length);

static void sortTest(int* nums, int length);

#endif
