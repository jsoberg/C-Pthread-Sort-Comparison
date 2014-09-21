/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */

#include "SorterThread.h"

/* Function to execute in a thread. */
void *executeThread(void *params)
{
	ThreadParameters *threadParams = params;
	
	int *nums = threadParams->nums;
	int start = threadParams->start;
	int end = threadParams->end;
	
	quickSort(nums, start, end);
	
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
