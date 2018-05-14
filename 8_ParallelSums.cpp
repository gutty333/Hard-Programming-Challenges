// For this challenge you will determine how to properly split an array into two sets.
/*
have the function ParallelSums(arr) take the array of integers stored in arr which will always contain an even amount of integers, and determine how they can be split into two even sets of integers each so that both sets add up to the same number. If this is impossible return -1. If it's possible to split the array into two sets, then return a string representation of the first set followed by the second set with each integer separated by a comma and both sets sorted in ascending order. The set that goes first is the set with the smallest first integer.

For example: if arr is [16, 22, 35, 8, 20, 1, 21, 11], then your program should output 1,11,20,35,8,16,21,22
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>
using namespace std;


// NOT FINISHED

/*
first add up all the values of the input array
we divide by 2 to check if is possible to split into 2 sets

With my strategy we first sort our values in increasing order
Our selection for the sets will be, select the lowest and highest value and add it to one of the sets
we update our indexes and now select the current lowest and highest values and add it to the other set
We repeat this step until all values have been copied to our sets.
*/
string ParallelSums(int arr[], int size)
{
	// calculate total sum
	int sum = 0;
	int setSum;
	for (int x = 0; x < size; x++)
	{
		sum += arr[x];
	}

	// check if input values can be split into 2 even sets
	if (sum % 2 != 0)
	{
		return "-1";
	}
	else
	{
		setSum = sum / 2;
	}

	// making a copy of our input array to a vector for ease of use
	// we will also sort the values in ascending order to apply our greedy approach
	vector <int> values(arr,arr + size);
	sort(values.begin(), values.end());

	// indexes used for our selection we will also be collecting the sum for both sets
	int low = 0; 
	int high = size - 1;

	vector <int> set1;
	vector <int> set2;

	// sum of each set
	int sum1 = 0;
	int sum2 = 0;

	// loop to perform our greedy selection
	while (low < high)
	{
		cout << "low is " << low << endl;
		cout << "high is " << high << endl;

		if (set1.size() + 1 < size / 2)
		{
			// copying the current lowest and highest to set 1
			set1.push_back(values[low++]);
			set1.push_back(values[high--]);

			// copying the current lowest and highest to set 2
			set2.push_back(values[low++]);
			set2.push_back(values[high--]);
		}

		// special condition
		int difference = setSum - accumulate(set1.begin(), set1.end(), 0);

		// check which of the remaining values we select based on the different
		if (values[low] == difference)
		{
			set1.push_back(values[low++]);
			set2.push_back(values[high--]);
		}
		else
		{
			set2.push_back(values[low++]);
			set1.push_back(values[high--]);
		}
	}

	string result = "";

	// sorting both sets
	sort(set1.begin(), set1.end());
	sort(set2.begin(), set2.end());

	// storing both sets into a string
	for (auto current : set1)
	{
		result += to_string(current);
		result += ',';
	}
	for (auto current : set2)
	{
		result += to_string(current);
		result += ',';
	}
	result.pop_back();

	return result;
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