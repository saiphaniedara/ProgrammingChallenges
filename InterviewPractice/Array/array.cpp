//
//----------------------------------------------------------------------------------------
/* //
Table of Contents
1. Maximum Subarray Problem using Kadane's Algorithm
2. Sorted Shifted Array with only distinct elements, find if a value exist in the sorted shifted array, T(n) = O(logn) = S(n)
3. Given an array of integers, find two numbers such that they add up to a specific target number. T(n) = O(nlogn), S(n) = O(1)
TODO:
// Sorted Shifted Array with duplicate elements, find the amount array is shifted by 
// Sorted shifted array with duplicate elements, search for an element

// Buy and sell stocks as many times. But only 1 transaction at a time (must sell whatever bought before can buy again)
   Max profit? buy and sell stock at most k times. Max profit? (k's base case is 1, k = 1)
    - For many times, just do it recursively. Solve for k = 1, then divide left and right to 2 recursions 
    - For k times, do similarly as many times, but use O(n) space by returning linked list of all the components of many times in sorted order
    - Sorting takes O(n) since it's the merge step in merge sort at each recursion. 
    - Then just pick the first k. 
    (DONE IN LEETCODE)


// CIRCULAR ARRAY: 
    HouseRobberIIFromLeetCode: Find the maximum sum of non-adjacent elements in a circular array. 
    e.g. [2,6,5,7,8] = 6+8 = 14 (can't pick both 2 and 8 in the sum as it is circular array and so 2 and 8 will be adjacent)
    Time Complexity, T(n) = O(n) single pass, Space Complexity, S(n) = O(1)
    Hint: Use dynamic programming
    
// Find the only singular integer in an array of pairs of integers (done in leetcode)
// Array with n distinct elements and local minimums, find one local min in O(logN)
e.g. 10, 6, 4, 3, 12, 19, 18, 20, 17 has 3 local mins at : 3, 18, 17
// ADD Array questions implemented in RandomDecision for ECE345 assignments here, where you find intersection of 2 different arrays etc. 
// Given circular array with reference indexing, return if it is a complete circular array.T(n) = O(n), S(n) = O(1) , (Google Practice Interview) note: Use a single pass only
        // hint: Just check if nth element is the starting element. If it is not, then error, if you reach starting element before n, then error
    
Easy, just prove that if A[n-1] < A[n] , there must exist local min in A[1] -> A[n-1]
Similarly for A[n-1] < A[n-2] => There must exist local min in A[n-1] -> A[n]
note: Always check for A[n-1] itself being local min as base case cause
 you must always set top or bottom to not include it. If not may end up with infinite
 loop in certain cases. basically must always exclude the middle element that you checked itself
 so that don't end up checking it again in any way.

// TODO: 2. Merge two equally sized integer arrays, the first one   having the capacity to accommodate the result.
            Hint: Merge from end to first so won't overwrite non-merge values
// TODO 3.   Implement a method for a Fibonacci sequence where instead of adding the last 2 elemenT's you add the last n elements. For n=3. 1 1 1 3 5 9...
//----------------------------------------------------------------------------------------------------------------------------------
// Common Hints
//-------------------------
- Have 2 pointers, one at each end and move towards the middle 
- Sort and use binary search 
- Counting sort and Radix sort 
- Solve for 1, then recursively solve the remainders  
- Have 2 pointers, one at each end, have third pointer moving from one end to another and swapping elements in and out from both end pointers. 
- Partition values to left and right of middle element (quicksort) 
//-------------------------
// Common Questions
//-------------------------
- (-) index? 
- resizable or fixed size? 
- the type the array is holding? 
- circular or straight array? 
- Traverse from left to right, then traverse from right to left. 
    (e.g. Product of entire array except itself without using division(/) operator) 
    (e.g. Sum of entire array except itself without using deduct (-) operator) 
// */
//----------------------------------------------------------------------------------------------------------------------------------
/* //
// 1 Maximum Subarray Problem using Kadane's Algorithm
// Time Complexity = O(n)
// Space Complexity = O(1)
#include <stdlib.h> // for rand()
#include <time.h>
#include <limits.h> // INT_MAX
#include <iostream>
using namespace std;

int maxSubArray(int* a, int N, int &startIndex, int &endIndex);
int maxSubArrayDynamic(int* a, int N);
int main(void)
{
    int N = 10;
    int * a;
    a = (int*) malloc(sizeof(int) * N);
    int i = 0;
    srand (time(NULL));
    for(i = 0; i < N; i++)
    {
        a[i] = rand()%20;
        if((rand()%20) > 10)
        {
            a[i] *= -1;
        }
    }
    for(i = 0; i < N; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    int k,l;
    int maximum = maxSubArray(a, N, k, l);
    int maximum2 = maxSubArrayDynamic(a, N);
    cout<<"Start: "<< k<<" to End: " << l <<" is maximum: "<< maximum << endl;
    cout<<"maximum: "<< maximum2 << endl;
    int b[5] = { -4, -2, -3, -1, -5};
    maximum = maxSubArray(b, 5, k, l);
    maximum2 = maxSubArrayDynamic(b, 5);
    cout<<"Start: "<< k<<" to End: " << l <<" is maximum: "<< maximum << endl;
    cout<<"maximum: "<< maximum2 << endl;
    return 0;
}

int maxSubArray(int* a, int N, int &startIndex, int &endIndex)
{
    startIndex = 0;
    endIndex = 0;
    int currStartIndex = 0;
    int currEndIndex = 0;
    int i = 0;
    int cumulativeSum = -1*INT_MAX;
    int maxSum = cumulativeSum;
    for(i = 0; i < N; i++)
    {
        if(cumulativeSum < 0)
        {
            cumulativeSum = a[i];
            currStartIndex = i;
            currEndIndex = i;
        }
        else
        {
            cumulativeSum += a[i];
            currEndIndex = i;
        }
        if (cumulativeSum >= maxSum)
        {
            maxSum = cumulativeSum;
            startIndex = currStartIndex;
            endIndex = currEndIndex;
        }
    }
    return maxSum;
}

// or another implementation which is easier to understand
// Note: You solved this yourself! Kadane's algorithm is basically a dynamic programming solution that can easily be solved!=) 


// Basically 2 cases: 
// Case 1: There is a positive number in the array
//      Then, you just output your dynamic programming solution
// Case 2: There is no positive number at all in the array
//      Then, you output the minimum value of the array 

// Time Complexity, T(n) = O(n) // one pass only 
// Space Complexity, S(n) = O(1) 
// Note: Haven't accounted for start and end index yet
int maxSubArrayDynamic(int* a, int N)
{
    bool notAllNegative = false; // initialize to all are negative
    int minNegative = a[0]; // initialize minNegative to first element assuming there exist a first element
    int maxSum = a[0]; // initialize maximumSum to be first element
    int currSum = 0; // initialize to 0 for a[-1] 
    for(int i = 0; i <N; i++)
    {
        currSum = max(0, currSum + a[i]);
        if(currSum > maxSum) 
        {
            maxSum = currSum; 
        }
        if(!notAllNegative)
        {
            if(a[i] >= 0)
            {
                notAllNegative = true; // there is a positive value, so don't need to evaluate this anymore 
            }
            else 
            {
                if(minNegative < a[i])
                {
                    minNegative = a[i]; 
                }
            }
        }

    }
    // If special case where all negative numbers
    if(!notAllNegative) return minNegative;
    // Otherwise, return the maximumSum from dynamic programming solution 
    else return maxSum; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 2 Sorted Shifted Array with only distinct elements, find if a value exist in the sorted shifted array, T(n) = O(logn) = S(n)
// Time Complexity, T(n) = O(logn), S(n) = O(logn)
//------------------------
/*
Questions: 
Can duplicates exist?  NO
Can the values be (-)? can the integer be any values? 
what is maximum length of array ?
Does [-1] indexing work on this rotated array? 
What if array is empty?  return -1 
Do i output the minimum value or its index?  // this is for finding shift that has been updated to find minimum as it depends on shift

Function Prototype 

int getPivot(vector<int>& nums); 

TEST_CASE: 
	4567012 => return 4 (indexof 0) 
	1 => return 0 
	1,2=> return 0
	2,1 => return 1
	2,1,3 
	3,3,1,3 => returns 2 (CODE DOESNT WORK FOR THIS CASE!) 

ALGORITHM: 
	Binary search. 
	// base case
	If nums[mid] < nums[mid-1] return mid  
	if (nums[mid] > nums[end])
		begin = mid+1
		end = end 
		Search 
	else 
		begin = begin
		end = mid-1
		search 

Implementation: 
TEST!
*/
//------------------------
/* //
#include <vector> 
#include <iostream> 
using namespace std; 

int binarySearchGetPivot(vector<int>& nums, int begin, int end)
{
    int mid = ((end + begin)/2); 
    // Base cases
    if((mid > begin && nums[mid] < nums[mid-1]) || (mid == begin && nums[mid] <= nums[end]))     
        return mid; 
    // General case 
    if (nums[mid] > nums[end]) 
    {
        begin = mid+1; 
        return binarySearchGetPivot(nums, begin, end); 
    }
    else
    {
        end = mid -1; 
        return binarySearchGetPivot(nums, begin, end); 
    }	
} 

int getPivot(vector<int>& nums)
{
    if( nums.size() == 0) return -1; 
    int result = binarySearchGetPivot(nums, 0, nums.size()-1); 
    return result; 
}

int binarySearchSearch(vector<int>& nums, int begin, int end, int target, int pivot)
{
    if (begin > end) return -1; 
    int mid = (begin+end)/2;
    int n = nums.size();  
    if (n <= 0) return -1; 
    while(begin <= end)
    {
        mid = (begin+end)/2; 
        int midFix = (mid+pivot) % n; 
        if(nums[midFix] == target) 
        {
            return midFix; 
        }
        else if (nums[midFix] < target)
        {
            begin = mid+1; 
        }
        else
        {
            end = mid - 1; 
        }
    }
    return -1; 
}

int search(vector<int>& nums, int target) 
{
    int pivot = getPivot(nums); 
    int begin = 0; 
    int end = nums.size() - 1; 
    int result = binarySearchSearch(nums, begin, end, target, pivot); 
    return result; 
}

int main(void)
{
	vector<int> nums = {4,5,6,7,0,1,2}; // C++ 11 compiler required 
	int result = getPivot(nums); 
	cout << result << endl; 
	cout << nums[result] << endl; 
    int target = 6;
    result = search(nums, target); 
    cout << result << endl;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 3 Given an array of integers, find two numbers such that they add up to a specific target number.
// Time Complexity, T(n) = O(nlgn + n) = O(nlgn) , S(n) = O(1)
/* //
Questions:
1. 	Is the array of integers sorted?  
2. 	Can the numbers be (-) 
3.  	Can array contain repeated elements? 
4. 	Can I modify the array? 
Test Case: 
	-3, -2 -8 7 5
// */
//---------------------------------
/* // 
#include <vector> 
#include <cstdlib> // bool 
#include <algorithm> // sort()
#include <iostream> 
using namespace std; 
bool targetNumber(vector<int>& vec , int sum, int& first, int& second)
{
	sort(vec.begin(), vec.end()); 	
	int i = 0; 
	int j = vec.size()-1; 
	while(i != j)
	{
		if (vec[i] + vec[j] == sum)
		{
			first = vec[i]; 
			second = vec[j]; 
			return true; 
        }
        else if (vec[i] + vec[j] < sum)
        {
            i++; 
        }
        else 
        {
            j--;  
        }
    }
    return false; 
}
int main(void)
{
    vector<int> vec(4, 0);
    vec[0] = -2; 
    vec[1] = -8; 
    vec[2] = 7; 
    vec[3] = 5; 
    int first = 0; 
    int second = 0; 
    if(targetNumber( vec , -3,  first,second))
    {
        cout << "Numbers found are: " << first << " , " << second; 
    }
    else
    {
        cout << "No numbers found" << endl; 
    }
    return 0; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
