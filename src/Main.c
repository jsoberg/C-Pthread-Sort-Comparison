/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */

#include <stdio.h>
#include <stdlib.h>
#include "RandomNumberFileGenerator.h"

// Number of random numbers to generate in file.
// TODO: RESET THIS TO INDICATED INTEGER (1000000)
const int NUMS_TO_GENERATE = 10;
// Maximum random number to generate.
const int MAX_RANDOM_NUM = 1000000;
// Minimum random number to generate.
const int MIN_RANDOM_NUM = 0;

// Default file name to use when creating the random numbers file.
char *DEFAULT_FILE_NAME = "RandomNumbers.txt";

int main()
{
	printf("Generating file of %d random numbers from [ %d, %d ]\n", NUMS_TO_GENERATE, MIN_RANDOM_NUM, MAX_RANDOM_NUM);
	int openFileResult = generateFileOfRandomNumbers(MIN_RANDOM_NUM, MAX_RANDOM_NUM, NUMS_TO_GENERATE, DEFAULT_FILE_NAME);
	
	// Error opening file, log error and return.
	if(openFileResult != 0) {
		fprintf(stderr, "Error generating file.");
		return 1;
	}
}
