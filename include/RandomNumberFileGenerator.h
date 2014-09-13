/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */
 
#include <stdio.h>

#ifndef RANDOM_NUMBER_FILE_GENERATOR_H
#define RANDOM_NUMBER_FILE_GENERATOR_H

// Function declaration.

FILE* generateFileOfRandomNumbers(int minNum, int maxNum, int numsToGenerate, char* fileName);

#endif