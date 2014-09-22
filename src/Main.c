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
static int NUM_THREADS_TO_EXECUTE[6] = { 5, 15, 50, 100, 250, 1000 };

// Default file name to use when creating the random numbers file.
char *DEFAULT_FILE_NAME = "RandomNumbers.txt";

int main()
{
	// Intializing nums and filling with randomely generated integers.
	int nums[NUMS_TO_GENERATE];
	generateFileAndFillArray(nums, NUMS_TO_GENERATE);
	
	// Testing sorting threads with 5 threads first.
	startSortingThreads(NUM_THREADS_TO_EXECUTE[0], nums, LENGTH(nums));
	
	// Initializing array to hold completely sorted results.
	int resultArray[LENGTH(nums)];
	memset(resultArray, 0, (NUMS_TO_GENERATE * sizeof(int)));
	startMergeThread(NUM_THREADS_TO_EXECUTE[0], nums, resultArray, LENGTH(nums));
	
	// ---------- DEBUG PRINT ----------
	printArray(resultArray, 0, LENGTH(resultArray));
	
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

/* Executes sorting threads. Uses numThreads threads. 
 * @param numThreads - Number of threads that were executed when sorting the array. 
 * @param array - Array of random integers to sort.
 * @param arrayLength - Length of array. */
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
		SortThreadParameters params;
			params.nums = array;
			params.start = start; 
			params.end = end;
		
		int result;
		// Initializing thread attributes.
		result = pthread_attr_init(&threadAttrs[i]);
		determineThreadActionResult(result, i, __LINE__);
		// Creating thread.
		result = pthread_create(&threads[i], &threadAttrs[i], executeSortThread, &params);
		determineThreadActionResult(result, i, __LINE__);
		// Executing thread.
		result = pthread_join(threads[i], NULL);
		determineThreadActionResult(result, i, __LINE__);
		
		start = (end + 1);
	}
}

/* Executes merging thread. 
 * @param numThreads - Number of threads that were executed when sorting the array. 
 * @param array - Segmentally sorted array. 
 * @param resultArray - Array to store merge results. 
 * @param arrayLength - The length of segmentally sorted array and result array. */
void startMergeThread(int numThreads, int* array, int* resultArray, int arrayLength)
{
	pthread_t mergeThread;
	pthread_attr_t mergeThreadAttr;
	
	// Creating parameters for thread to use.
	MergeThreadParameters params;
		params.array = array;
		params.result = resultArray;
		params.numSegments = numThreads;
		params.arrayLength = arrayLength;
	
	int result;
	// Initializing merge thread attributes.
	result = pthread_attr_init(&mergeThreadAttr);
	// Creating merge thread.
	result = pthread_create(&mergeThread, &mergeThreadAttr, executeMergeThread, &params);
	// Executing merge thread.
	result = pthread_join(mergeThread, NULL);
}

/* Logs the result of a thread action. If unsuccessful, the log will be fatal.
 * @param result - Result of thread action.
 * @param threadNum - Thread number. 
 * @param lineNumber - Line number that action took place. */
void determineThreadActionResult(int result, int threadNum, int lineNumber)
{
	// Making sure variable has enough buffer to hold the message.
	char message[100];
	// Thread action was successful.
	if(result == 0) {
		sprintf(message, "Thread %d had a succesful action. ", threadNum);
		LogDebug(__FILE__, message);
	} else { // Unsuccessful.
		sprintf(message, "Thread %d had an unsuccesful action returning a value of %d.", threadNum, result);
		LogFatal(__FILE__, lineNumber, message);
	}
}

// ---------- Test Functions ----------

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
