/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */

#include "SorterThread.h"

// --------- Merging Functions ----------

/* Function to execute merging of segmentally sorted array in a thread. */
void *executeMergeThread(void *params)
{
	MergeThreadParameters *threadParams = params;
		int *array = threadParams->array;
		int *resultArray = threadParams->result;
		int numSegments = threadParams->numSegments;
		int arrayLength = threadParams->arrayLength;
	
	merge(array, resultArray, numSegments, arrayLength);
	
	return NULL;
}

/* Merges segmentally sorted array into a completely sorted array, 
 * 		storing the complete sorted array in result. */
void merge(int *nums, int *result, int numSegments, int length)
{
	// Length of each sorted segment in nums.
	int segmentLength = (length / numSegments);
	
	// Creating array for start location of segments.
	int sortedSegments[numSegments];
	memset(sortedSegments, 0, LENGTH(sortedSegments));
	fillStartLocationsArrayForSegments(sortedSegments, numSegments, length);
	
	int i;
	for(i = 0; i < length; i ++) {
		
		int j;
		int lowestLoc = -1;
		for(j = 0; j < LENGTH(sortedSegments); j ++) {
			// This segment has been traversed, ignore it.
			if(sortedSegments[j] >= ((segmentLength) * (j + 1)) )
				continue;
			
			// Checking if a lower number has been found, or if this is the first comparison for this iteration.
			if( (lowestLoc == -1) || (nums[sortedSegments[j]] <= nums[sortedSegments[lowestLoc]]) ) {
				lowestLoc = j;
			}
		}
		
		// Storing result and iterating through segment.
		result[i] = nums[sortedSegments[lowestLoc]];
		sortedSegments[lowestLoc] += 1;
	}
}

/* Fills sortedSegments with start locations for the calculated sorted segments 
 * 		in the segmentally sorted array. */
void fillStartLocationsArrayForSegments(int *sortedSegments, int numSegments, int arrayLength)
{
	int i;
	for(i = 0; i < numSegments; i ++) {
		sortedSegments[i] = ( (arrayLength / numSegments) * i);
	}
}

// ---------- Sorting Functions ----------

/* Function to execute sorting in a thread. */
void *executeSortThread(void *params)
{	
	SortThreadParameters *threadParams = params;
		int *parentArray = threadParams->parentArray;
		int start = threadParams->start;
		int end = threadParams->end;
		char *fileName = threadParams->fileName;
	
	int resultArrayLength = ((end - start) + 1);
	
	// Initializing array of random integers.
	int resultArray[resultArrayLength];
	memset(resultArray, 0, LENGTH(resultArray));
	
	// Filling array with random integers from file.
	fillArrayFromFile(resultArray, fileName, start, resultArrayLength);
	
	// Running sort.
	quickSort(resultArray, 0, resultArrayLength - 1);
	
	/* Checking for largest value. Since this segment of the list is now sorted, 
	 * 		the largest value will be the last number in this segment. */
	designateLargestValue(resultArray[resultArrayLength - 1]);
	
	// Printing results of smallest/ largest threads in system.
	printf("\n    Smallest value of thread #%d: %d \n", pthread_self(), resultArray[0]);
	printf("    Largest value of thread #%d: %d \n", pthread_self(), resultArray[resultArrayLength - 1]);
	fflush( stdout );
	
	// Storing results into parent.
	storeSortedResultsIntoParentArray(parentArray, resultArray, start, end);
	
	return NULL;
}

/* Sorts an array of integers using the quick sort algorithm. */
void quickSort(int *nums, int start, int end)
{
    if(start < end)
    {
		int pivot = partition(nums, start, end);
		quickSort(nums, start, (pivot - 1));
		quickSort(nums, (pivot + 1), end);
    }
}

/* Executing the 'divide and conquer' scheme of quick sort, finding a 
 * 		pivot value and putting all numbers lower than it to the left,
 *  	all numbers higher than it to the right. */
int partition(int *nums, int start, int end)
{
	int pivot = start;
	int left = start;
	int right = end;
	
	int pivotVal = nums[pivot];
	while(left < right)
	{
		while(nums[left] <= pivotVal && left <= end)
			left++;
		while(nums[right] > pivotVal && right >= 0)
			right--;
		if(left < right)
			swap(&nums[left], &nums[right]);
	}

	nums[start] = nums[right];
	nums[right] = pivotVal;
	return right;
}

/* Swaps to items in an array. */
void swap(int *a, int *b)
{
	*a = *a - *b;
	*b = *b + *a;
	*a = *b - *a;
}
