// For this challenge you will determine how to properly split an array into two sets.
/*
have the function ParallelSums(arr) take the array of integers stored in arr which will always contain an even amount of integers, and determine how they can be split into two even sets of integers each so that both sets add up to the same number. If this is impossible return -1. If it's possible to split the array into two sets, then return a string representation of the first set followed by the second set with each integer separated by a comma and both sets sorted in ascending order. The set that goes first is the set with the smallest first integer.

For example: if arr is [16, 22, 35, 8, 20, 1, 21, 11], then your program should output 1,11,20,35,8,16,21,22
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


// bubble sort 
void bubblesort(int arr[], int size)
{
	bool swap;

	do
	{
		swap = false;

		for (int x = 0; x < size - 1; x++)
		{
			if (arr[x] > arr[x + 1])
			{
				int temp = arr[x];
				arr[x] = arr[x + 1];
				arr[x + 1] = temp;

				swap = true;
			}
		}
	} while (swap);
}


// int to string conversion
void intToString(int set[], int size, string & result)
{
	for (int x = 0; x < size; x++)
	{
		stringstream convert;
		convert << set[x];
		result += convert.str();
		result += ",";
	}
}

/*
A strategy we can use here is to apply a greedy approach

since our input we be set to an even size we can break it in half and that will decide what the size of our sets will be

With a greedy technique we can avoid having to do a brute force approach which would result in exponential time, since we would first check for possible sums, than split it into 2 sets and check again if those sets equal that possible sum. We would have to continue repeating this step until all possible options have been checked.

With my strategy we first sort our values in increasing order
Our selection for the sets will be, select the lowest and highest value and add it to one of the sets
we update our indexes and now select the current lowest and highest values and add it to the other set
We repeat this step until all values have been copied to our sets.

For these requirement we would sort our sets than pass the values of each to a string to return at the end

if is not guarantee for the input to have size n > 2, we could set some base cases where
if n == 0 return 0
if n == 1 return -1
if n == 2 check if both values are equal 
*/
string ParallelSums(int arr[], int size) 
{
	// setting our 2 sets
	int* set1 = new int[size / 2];
	int* set2 = new int[size / 2];

	// we sort our input array
	bubblesort(arr, size);

	// indexes used for our selection we will also be collecting the sum for both sets
	int low = 0; 
	int high = size - 1;
	int index1 = 0;
	int index2 = 0;
	int sum1 = 0;
	int sum2 = 0;

	cout << "hi" << endl;

	// loop to perform our greedy selection
	while (low < high)
	{
		cout << "low is " << low << endl;
		cout << "high is " << high << endl;
		// copying the current lowest and highest to set 1
		set1[index1++] = arr[low++];
		sum1 += set1[index1 - 1];
		set1[index1++] = arr[high--];
		sum1 += set1[index1 - 1];

		// copying the current lowest and highest to set 2
		set2[index2++] = arr[low++];
		sum2 += set2[index2 - 1];
		set2[index2++] = arr[high--];
		sum2 += set2[index2 - 1];
	}

	cout << "the sum of set 1 is " << sum1 << " the sum of set 2 is " << sum2 << endl;

	// condition to check if the it can be divided into 2 sets
	if (sum1 == sum2)
	{
		string result="";

		// first we sort the values in increasing order
		bubblesort(set1, size / 2);
		bubblesort(set2, size / 2);

		
		// we copy the values from our set to our result string
		intToString(set1, size / 2, result);
		intToString(set2, size / 2, result);

		// here we just edit last character to remove the comma
		result.pop_back();

		return result;
	}
	else
	{
		return "-1";
	}
}

int main() 
{
	int A[] = { 16, 22, 35, 8, 20, 1, 21, 11 };
	int B[] = { 1, 2, 3, 4 };
	int C[] = { 1, 2, 1, 5 };
	
	cout << ParallelSums(A, sizeof(A)/sizeof(A[0])) << endl; // 1,11,20,35,8,16,21,22
	cout << ParallelSums(B, sizeof(B) / sizeof(B[0])) << endl; // 1,4,2,3
	cout << ParallelSums(C, sizeof(C) / sizeof(C[0])) << endl; // -1
	
	return 0;
}