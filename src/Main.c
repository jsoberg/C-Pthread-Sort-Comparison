/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */

#include "Main.h"

// Number of random numbers to generate in file.
// TODO: RESET THIS TO INDICATED INTEGER (1,000,000)
static int NUMS_TO_GENERATE = 1000;
// Maximum random number to generate.
static int MAX_RANDOM_NUM = 1000000;
// Minimum random number to generate.
static int MIN_RANDOM_NUM = 0;

// Number of threads to use for each sort iteration.
static int NUM_THREADS_TO_EXECUTE[6] = { 5, 15, 50, 100, 250, 100 };

// Default file name to use when creating the random numbers file.
char *DEFAULT_FILE_NAME = "RandomNumbers.txt";

int main()
{
	int nums[NUMS_TO_GENERATE];
	generateFileAndFillArray(nums, NUMS_TO_GENERATE);
	
	// Testing sorting threads with 5 threads first.
	startSortingThreads(NUM_THREADS_TO_EXECUTE[0], nums, LENGTH(nums));
	
	return 0;
}

/* Generates file of numsToGenerate random integers and fill 
 * 		array with the generated integers. */
void generateFileAndFillArray(int* array, int numsToGenerate)
{
	int createFileResult = generateFileOfRandomNumbers(MIN_RANDOM_NUM, MAX_RANDOM_NUM, numsToGenerate, DEFAULT_FILE_NAME);
	LogDebug(__FILE__, DEFAULT_FILE_NAME);
	// Error creating file, log fatal.
	if(createFileResult != 0) {
		LogFatal(__FILE__, __LINE__, "Fatal error generating file.");
	}
	
	// Read permissions required.
	FILE *file = fopen(DEFAULT_FILE_NAME, "r");
	// Initializing array of random integers.
	memset(array, 0, (NUMS_TO_GENERATE * sizeof(int)));
	// Iterating file for randomely generated integers.
	int i = 0;
	while(!feof(file)) {
		fscanf(file, "%d", &array[i]);
		i++;
	}
	fclose(file);
}

/* Executes sorting threads. Uses numThreads threads. */
void startSortingThreads(int numThreads, int* array, int arrayLength)
{
	// Thread identifiers.
	pthread_t threads[numThreads];
	// Thread attributes.
	pthread_attr_t threadAttrs[numThreads];
	
	int i, start = 0;
	for(i = 0; i < numThreads; i ++) {
		// Create parameters to send to thread.
		int end = ((arrayLength / numThreads) + start) - 1;
		
		// Creating parameters for thread to use.
		ThreadParameters params;
		params.nums = array;
		params.start = start; 
		params.end = end;
		
		// Initializing thread attributes.
		pthread_attr_init(&threadAttrs[i]);
		// Creating thread.
		pthread_create(&threads[i], &threadAttrs[i], executeThread, &params);
		// Executing thread.
		pthread_join(threads[i], NULL);
		
		// ---------- DEBUG PRINT ----------
		printArray(array, start, end);
		
		start = (end + 1);
	}
}

// ---------- Test Functions ----------

/* Debug function used to test quick sort implementation. */
static void sortTest(int* nums, int length)
{
	// Print unsorted.
	printArray(nums, 0, length);
	// Sort items.
	quickSort(nums, 0, length);
	// Print sorted.
	printArray(nums, 0, length);
}

/* Prints the contents of the given array (from location start to location end) to stdout. */
void printArray(int* nums, int start, int end)
{
	// Keep track of how many items have been printed.
	int printCount = 1;
	
	int i;
	for(i = start + 1; i <= end; i++) {
		printf("%6d", nums[i - 1]);
		// Print "," after every entry except for the last.
		if(i < end) { printf(", "); }
		// New line every 9 entries.
		if((printCount % 9) == 0)
			printf("\n");
		
		fflush(stdout);
		printCount ++;
	}
	// Printing separating line.
	printf("\n");
	for(i = 70; i --; printf("="));
	printf("\n");
	fflush(stdout);
}
