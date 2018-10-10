/* Joshua Soberg */
 
#include "RandomNumberFileGenerator.h"

/* Generates a file containing a predefined number of
 *		randomly generated integers.
 * @param minNum - Minimum number to generate.
 * @param maxNum - Maximum number to generate.
 * @param numtsoGenerate - Number of random numbers to generate in the file.
 * @param numFormatWidth - Used to format the length of each number when printing to the file.
 * @param fileName - Name of file to be created.
 * @return - The result of the file being closed. */	
int generateFileOfRandomNumbers(int minNum, int maxNum, int numsToGenerate, int numFormatWidth, char* fileName) 
{
	// Opening file with write permissions.
	FILE *file = fopen(fileName, "w");
	// If file is NULL, return 1.
	if(file == NULL) {
		LogError(__FILE__, __LINE__, "Error opening file. ");
		return 1;
	}
	
	// Creating a random seed.
	srand( time(NULL) );
	// Twenty randomely generated numbers per line for numsToGenerate iterations.
	int randomNum, i;
	for (i = 1; i <= numsToGenerate; i++) {
		randomNum = (rand() % maxNum) + minNum;
		fprintf(file, "%-*d ", numFormatWidth, randomNum);
		
		// Printing newline every 20 integers
		if((i % 20) == 0) {
			fprintf(file, "\n");
		}
	}
	
	return fclose(file);
}
