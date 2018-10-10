/* Joshua Soberg */

#include "SharedMemoryController.h"

/* Shared memory values. */
pthread_mutex_t sort_array_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t file_access_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t largest_val_mutex = PTHREAD_MUTEX_INITIALIZER;
int sharedLargestVal;

/* Resets shared memory values. */
void resetSharedMemoryValues()
{
	sharedLargestVal = 0;
}

/* Indicates the largest values across all threads. 
 * 		Uses a mutex to insure only one thread at a time can access. */
void designateLargestValue(int largest)
{
	// Value to hold result of mutex action.
	int result;
	// Locking mutex.
	result = pthread_mutex_lock(&largest_val_mutex);
	determineMutexActionResult(result, __LINE__);
	
	// If this number is larger, set the new largest number.
	if(largest > sharedLargestVal)
		sharedLargestVal = largest;
	
	// Unlocking mutex.
	result = pthread_mutex_unlock(&largest_val_mutex);
	determineMutexActionResult(result, __LINE__);
}

/* Fills an array with integers from file fileName from a specified start location to a 
 * 		specified end location. */
void fillArrayFromFile(int *array, char* fileName, int startLoc, int valuesToRead)
{
	// Value to hold result of mutex action.
	int result;
	// Locking mutex.
	result = pthread_mutex_lock(&file_access_mutex);
	determineMutexActionResult(result, __LINE__);
	
	// Read permissions required.
	FILE *file = fopen(fileName, "r");	
	
	/* Since fseek() doesn't always work as expected, the correct start location must be found by scanning. 
	 * 		throwAway is just a holder variable for the unnecessary values until start is reached. */
	int i, throwAway = 0;
	for(i = 0; i < startLoc; i ++) {
		fscanf(file, "%d", &throwAway);
	}
	
	// Iterating file for randomely generated integers.
	for(i = 0; i < valuesToRead; i ++) {
		fscanf(file, "%d", &array[i]);
	}
	
	fclose(file);
	
	// Unlocking mutex.
	result = pthread_mutex_unlock(&file_access_mutex);
	determineMutexActionResult(result, __LINE__);
}

/* Stores sorted results in corresponding area of parent array. */
void storeSortedResultsIntoParentArray(int *parentArray, int *resultArray, int start, int end)
{
	// Value to hold result of mutex action.
	int result;
	// Locking mutex.
	result = pthread_mutex_lock(&sort_array_mutex);
	determineMutexActionResult(result, __LINE__);
	
	int endLocation = (end - start) + 1;
	
	int i;
	int currentParentLoc = start;
	for(i = 0; i < endLocation; i ++) {
		parentArray[currentParentLoc] = resultArray[i];
		currentParentLoc ++;
	}
	
	// Unlocking mutex.
	result = pthread_mutex_unlock(&sort_array_mutex);
	determineMutexActionResult(result, __LINE__);
}

/* Logs the result of a mutex action.
 * @param result - Result of mutex action. 
 * @param lineNumber - Line number that action took place. */
void determineMutexActionResult(int result, int lineNumber)
{
	// Making sure variable has enough buffer to hold the message.
	char message[100];
	// Mutex action was successful.
	if(result == 0) {
		sprintf(message, "Thread %d had a succesful mutex action. ", pthread_self());
		LogDebug(__FILE__, message);
	} else { // Unsuccessful.
		sprintf(message, "Thread %d had an unsuccesful mutex action returning a value of %d.", pthread_self(), result);
		LogError(__FILE__, lineNumber, message);
	}
}

/* Returns the largest value. */
int getLargestValue()
{
	return sharedLargestVal;
}

/* Destroys shared memory values when they are no longer needed. */
void deconstructSharedMemoryValues()
{
	// Destorying mutexes.
	pthread_mutex_destroy(&largest_val_mutex);
	pthread_mutex_destroy(&file_access_mutex);
	pthread_mutex_destroy(&sort_array_mutex);
}
