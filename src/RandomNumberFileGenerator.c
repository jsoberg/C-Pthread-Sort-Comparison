/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */
 
#include <stdio.h>
#include "RandomNumberFileGenerator.h"

/* Generates a file containing a predefined number of
 *		randomly generated integers.
 * @param minNum - Minimum number to generate.
 * @param maxNum - Maximum number to generate.
 * @param numtsoGenerate - Number of random numbers to generate in the file.
 * @param fileName - Name of file to be created.
 * @return - Returns the file pointer of the newly generated file. */	
FILE* generateFileOfRandomNumbers(int minNum, int maxNum, int numsToGenerate, char* fileName) 
{
	// Opening file with write permissions.
	FILE *file;
	file = fopen(fileName, "w");
	
	int randomNum = 0; 
	// One randomely generated number per line for numsToGenerate iterations.
	int i;
	for (i = 0; i < numsToGenerate; i++) {
		randomNum = (rand() % maxNum) + minNum;
		fprintf(file, "%d\n", randomNum);
	}

	return file;
}
