/* Joshua Soberg */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Logger.h"

#ifndef RANDOM_NUMBER_FILE_GENERATOR_H
#define RANDOM_NUMBER_FILE_GENERATOR_H

// ---------- Function Declarations ----------

/* Generates a file containing a predefined number of
 *		randomly generated integers.
 * @param minNum - Minimum number to generate.
 * @param maxNum - Maximum number to generate.
 * @param numtsoGenerate - Number of random numbers to generate in the file.
 * @param numFormatWidth - Used to format the length of each number when printing to the file.
 * @param fileName - Name of file to be created.
 * @return - The result of the file being closed. */	
int generateFileOfRandomNumbers(int minNum, int maxNum, int numsToGenerate, int numFormatWidth, char* fileName);

#endif
