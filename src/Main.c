/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */

#include "Main.h"

// Number of random numbers to generate in file.
static int NUMS_TO_GENERATE = 1000000;
// Maximum random number to generate.
static int MAX_RANDOM_NUM = 1000000;
// Minimum random number to generate.
static int MIN_RANDOM_NUM = 0;

// Number of threads to use for each sort iteration.
static int NUM_THREADS_TO_EXECUTE[6] = { 5, 15, 50, 100, 250, 1000 };

// The size each number will be formatted to in the random numbers file.
static int NUM_FORMAT_WIDTH = 6;
// Default file name to use when creating the random numbers file.
char *DEFAULT_FILE_NAME = "RandomNumbers.txt";
// Default file name to use when creating file to store sorted numbers.
char *DEFAULT_RESULT_FILE_NAME = "Sorted";

int main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stdout, "No input values or incorrect amount of input values detected, run automatic script. ");
		
		// If correct values aren't input, run auto script.
		int i;
		for(i = 0; i < LENGTH(NUM_THREADS_TO_EXECUTE); i ++) {
			executeProgram(NUMS_TO_GENERATE, NUM_THREADS_TO_EXECUTE[i]);
		}

		// Destroying shared memory values.
		deconstructSharedMemoryValues();
	} else { // Input parameters were given.
		executeProgram(atoi(argv[2]), atoi(argv[1]));
	}	
	
	return 0;
}

/* Executes the program fully (sorting and merging). */
void executeProgram(int numsToGenerate, int numThreadsToExecute)
{
	printf("\n\nOutput for %d threads sorting %d random integers\n==============================================================\n", numThreadsToExecute, numsToGenerate);
		
		// Initializing shared memory values.
		resetSharedMemoryValues();
		// Intializing nums (parent array).
		int nums[numsToGenerate];
		memset(nums, 0, LENGTH(nums));
		// Generating file of random integers.
		generateRandomFile(numsToGenerate, NUM_FORMAT_WIDTH);
		
		// Storing time of thread initialization.
		clock_t startTime = clock();
		
		// Sorting.
		startSortingThreads(numThreadsToExecute, nums, LENGTH(nums), DEFAULT_FILE_NAME);
		// Initializing array to hold completely sorted results and merging.
		int resultArray[LENGTH(nums)];
		memset(resultArray, 0, LENGTH(resultArray));
		startMergeThread(numThreadsToExecute, nums, resultArray, LENGTH(nums));
		
		// Storing time of thread completion.
		clock_t endTime = clock();
		
		// Printing time to execute
		printf("\n Seconds to execute %d threads: %f\n", numThreadsToExecute, ((endTime - startTime)/((double) CLOCKS_PER_SEC)));
		
		printf(" Largest value of entire set: %d \n", getLargestValue());
		fflush( stdout );
		
		// Printing sorted results to file.
		char fileName[100];
		sprintf(fileName, "SortedResult-%dIntegers-%dThreads.txt", numsToGenerate, numThreadsToExecute);
		printArrayToFile(fileName, resultArray, 0, LENGTH(resultArray));
		
		// Printing file name.
		printf("\n Sorted output can be found in %s.", fileName);
		fflush( stdout );
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
	// Thread parameters.
	SortThreadParameters params[numThreads];
	
	// Result of thread action.
	int result;	
	// Making sure variable has enough buffer to hold the log message.
	char message[100];
		
	int i, start = 0;
	for(i = 0; i < numThreads; i ++) {
		// Create parameters to send to thread.
		int end;
		if(i < (numThreads - 1)) {
			end = (floor(arrayLength / numThreads) + start) - 1;
		} else { // For the last thread, check if there are more items than usual to sort.
			end = arrayLength - 1;
		}
		
		// Creating parameters for thread to use.
		params[i].parentArray = array;
		params[i].start = start; 
		params[i].end = end;
		params[i].fileName = fileName;
		
		start = (end + 1);
	}
	
	for(i = 0; i < numThreads; i ++) {
		// Initializing thread attributes.
		sprintf(message, "Sort thread %d is being initialized. ", i);
		result = pthread_attr_init(&threadAttrs[i]);
		logThreadActionResult(result, __LINE__, message);
		// Creating thread.
		sprintf(message, "Sort thread %d is being created.", i);
		result = pthread_create(&threads[i], &threadAttrs[i], executeSortThread, &params[i]);
		logThreadActionResult(result, __LINE__, message);
	}
	
	// Joining threads.
	for(i = 0; i < numThreads; i ++) {
		sprintf(message, "Sort thread %d is being joined. ", i);
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
	
	// Making sure variable has enough buffer to hold the log message.
	char message[100];
	
	int result;
	// Initializing merge thread attributes.
	sprintf(message, "Merge thread is being initialized. ");
	result = pthread_attr_init(&mergeThreadAttr);
	logThreadActionResult(result, __LINE__, message);
	// Creating merge thread.
	sprintf(message, "Merge thread is being created. ");
	result = pthread_create(&mergeThread, &mergeThreadAttr, executeMergeThread, &params);
	logThreadActionResult(result, __LINE__, message);
	// Executing merge thread.
	sprintf(message, "Merge thread is being joined. ");
	result = pthread_join(mergeThread, NULL);
	logThreadActionResult(result, __LINE__, message);
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

/* Prints the contents of the given array (from location start to location end) to a file. */
int printArrayToFile(char* fileName, int* nums, int start, int end)
{
	// Opening file with write permissions.
	FILE *file = fopen(fileName, "w");
	// If file is NULL, return 1.
	if(file == NULL) {
		LogError(__FILE__, __LINE__, "Error opening file. ");
		return 1;
	}
	
	int i;
	fprintf(file, "Sorted output: \n");
	for(i = 70; i --; fprintf(file, "="));
	fprintf(file, "\n");
	
	// Keep track of how many items have been printed.
	int printCount = 1;
	
	for(i = start + 1; i <= end; i++) {
		fprintf(file, "%6d", nums[i - 1]);
		// Print "," after every entry except for the last.
		if(i < end) { fprintf(file, ", "); }
		// New line every 20 entries.
		if((printCount % 20) == 0)
			fprintf(file, "\n");
		
		printCount ++;
	}
	// Printing separating line.
	fprintf(file, "\n");
	for(i = 70; i --; fprintf(file, "="));
	fprintf(file, "\n");
	
	return fclose(file);
}
