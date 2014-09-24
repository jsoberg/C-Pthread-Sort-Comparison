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
static int NUM_THREADS_TO_EXECUTE[6] = { 5, 20, 50, 100, 250, 1000 };

// The size each number will be formatted to in the random numbers file.
static int NUM_FORMAT_WIDTH = 6;
// Default file name to use when creating the random numbers file.
char *DEFAULT_FILE_NAME = "RandomNumbers.txt";

int main()
{
	// Intializing nums (parent array).
	int nums[NUMS_TO_GENERATE];
	memset(nums, 0, LENGTH(nums));
	
	// Generating file of random integers.
	generateRandomFile(NUMS_TO_GENERATE, NUM_FORMAT_WIDTH);
	
	// Testing sorting threads with 5 threads first.
	startSortingThreads(NUM_THREADS_TO_EXECUTE[1], nums, LENGTH(nums), DEFAULT_FILE_NAME);
	
	// Initializing array to hold completely sorted results.
	int resultArray[LENGTH(nums)];
	memset(resultArray, 0, LENGTH(resultArray));
	startMergeThread(NUM_THREADS_TO_EXECUTE[1], nums, resultArray, LENGTH(nums));
	
	// ---------- DEBUG PRINT ----------
	printArray(resultArray, 0, LENGTH(resultArray));
	
	printf("\n\n Largest value: %d \n\n", getLargestValue());
	
	// Destroying shared memory values.
	deconstructSharedMemoryValues();
	
	return 0;
}

/* Generates file of numsToGenerate random integers with each integer
 * 		being formatted to a width of numFormatWidth. */
void generateRandomFile(int numsToGenerate, int numFormatWidth)
{
	int createFileResult = generateFileOfRandomNumbers(MIN_RANDOM_NUM, MAX_RANDOM_NUM, numsToGenerate, numFormatWidth, DEFAULT_FILE_NAME);
	LogDebug(__FILE__, DEFAULT_FILE_NAME);
	// Error creating file, log fatal.
	if(createFileResult != 0) {
		LogFatal(__FILE__, __LINE__, "Fatal error generating file.");
	}
}

/* Executes sorting threads. Uses numThreads threads. 
 * @param numThreads - Number of threads that were executed when sorting the array. 
 * @param array - Array of random integers to sort.
 * @param arrayLength - Length of array. 
 * @param fileName - Name of file to read. */
void startSortingThreads(int numThreads, int* array, int arrayLength, char* fileName)
{
	// Thread identifiers.
	pthread_t threads[numThreads];
	// Thread attributes.
	pthread_attr_t threadAttrs[numThreads];
	
	// Result of thread action.
	int result;
	// Making sure variable has enough buffer to hold the log message.
	char message[100];
		
	int i, start = 0;
	for(i = 0; i < numThreads; i ++) {
		// Create parameters to send to thread.
		int end = ( (arrayLength / numThreads) + start) - 1;
		
		// Creating parameters for thread to use.
		SortThreadParameters params;
			params.parentArray = array;
			params.start = start; 
			params.end = end;
			params.fileName = fileName;
		
		// Initializing thread attributes.
		sprintf(message, "Thread %d is being initialized. ", i);
		result = pthread_attr_init(&threadAttrs[i]);
		logThreadActionResult(result, __LINE__, message);
		// Creating thread.
		sprintf(message, "Thread %d is being created. Start value: %d, End value: %d ", i, start, end);
		result = pthread_create(&threads[i], &threadAttrs[i], executeSortThread, &params);
		logThreadActionResult(result, __LINE__, message);
		
		start = (end + 1);
	}
	
	// Joining threads.
	for(i = 0; i < numThreads; i ++) {
		sprintf(message, "Thread %d is being joined. ", i);
		result = pthread_join(threads[i], NULL);
		logThreadActionResult(result, __LINE__, message);
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
 * @param lineNumber - Line number that action took place. 
 * @param message - Message to log. */
void logThreadActionResult(int result, int lineNumber, char* message)
{
	// Thread action was successful.
	if(result == 0) {
		LogDebug(__FILE__, message);
	} else { // Unsuccessful.
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
