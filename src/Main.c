/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */

#include "Main.h"

// Number of random numbers to generate in file.
// TODO: RESET THIS TO INDICATED INTEGER (1,000,000)
static int NUMS_TO_GENERATE = 100;
// Maximum random number to generate.
static int MAX_RANDOM_NUM = 1000000;
// Minimum random number to generate.
static int MIN_RANDOM_NUM = 0;

// Default file name to use when creating the random numbers file.
char *DEFAULT_FILE_NAME = "RandomNumbers.txt";

int main()
{
	int createFileResult = generateFileOfRandomNumbers(MIN_RANDOM_NUM, MAX_RANDOM_NUM, NUMS_TO_GENERATE, DEFAULT_FILE_NAME);
	LogDebug(__FILE__, DEFAULT_FILE_NAME);
	
	// Error creating file, log fatal.
	if(createFileResult != 0) {
		LogFatal(__FILE__, __LINE__, "Fatal error generating file.");
	}
	// Read permissions required.
	FILE *file = fopen(DEFAULT_FILE_NAME, "r");
	
	int nums[NUMS_TO_GENERATE];
	memset(nums, 0, (NUMS_TO_GENERATE * sizeof(int)));
	// Iterating file for randomely generated integers.
	int i = 0;
	while(!feof(file)) {
		fscanf(file, "%d", &nums[i]);
		i++;
	}
	fclose(file);
	
	// Testing. TODO: remove
	sortTest(nums, LENGTH(nums));
	
	return 0;
}

/* Debug function used to test quick sort implementation. */
static void sortTest(int* nums, int length)
{
	// Print unsorted.
	printArray(nums, length);
	// Sort items.
	sort(nums, length);
	// Print sorted.
	printArray(nums, length);
}

/* Prints the contents of the given array to stdout. */
void printArray(int* nums, int length)
{
	int i;
	for(i = 0; i < length; i++) {
		printf("%d", nums[i]);
		if(i < (length - 1))
			printf(", ");
			
		fflush(stdout);
	}
	printf("\n");
	fflush(stdout);
}
