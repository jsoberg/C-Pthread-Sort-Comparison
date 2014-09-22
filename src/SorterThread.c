/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */

#include "SorterThread.h"

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
	const int segmentLength = (length / numSegments);
	
	// Creating array for start location of segments.
	int sortedSegments[numSegments];
	fillStartLocationsArrayForSegments(sortedSegments, numSegments, length);
	
	int i;
	for(i = 0; i < length; i ++) {
		
		int j;
		int lowestLoc = -1;
		for(j = 0; j < LENGTH(sortedSegments); j ++) {
			// This segment has been traversed, ignore it.
			if(sortedSegments[j] >= (segmentLength * (j + 1)))
				continue;
			
			// Checking if a lower number has been found, or if this is the first comparison for this iteration.
			if( (lowestLoc == -1) || (nums[sortedSegments[j]] <= nums[sortedSegments[lowestLoc]]) )
				lowestLoc = j;
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
		sortedSegments[i] = ((arrayLength / numSegments) * i);
	}
}

/* Function to execute sorting in a thread. */
void *executeSortThread(void *params)
{
	SortThreadParameters *threadParams = params;
		int *nums = threadParams->nums;
		int start = threadParams->start;
		int end = threadParams->end;
	
	quickSort(nums, start, end);
	
	return NULL;
}

// ---------- Sorting Functions ----------

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

void swap(int *a, int *b)
{
	*a = *a - *b;
	*b = *b + *a;
	*a = *b - *a;
}
