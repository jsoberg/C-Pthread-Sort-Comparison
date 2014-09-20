/* Joshua Soberg
 * CPSC 542
 * Program 1: Master-Slave Application using Pthreads */

/* Sorts an array of integers using the quick sort algorithm. */
void sort(int *nums, int n) 
{
    if (n < 2)
        return;
        
    int pivot = nums[n / 2];
    int *left = nums;
    int *right = nums + (n - 1);
    
    while (left <= right) {
        if (*left < pivot) {
            left++;
        }
        else if (*right > pivot) {
            right--;
        }
        else {
			int temp = *left; 
			*left = *right; 
			*right = temp;
			
            left++;
            right--;
        }
    }
    
    sort(nums, right - nums + 1);
    sort(left, nums + n - left);
}
