// This challenge will require knowledge of arrays.
/*
have the function ArrayRotation(arr) take the arr parameter being passed which will be an array of non-negative integers and circularly rotate the array starting from the Nth element where N is equal to the first integer in the array. For example: if arr is [2, 3, 4, 1, 6, 10] then your program should rotate the array starting from the 2nd position because the first element in the array is 2. The final array will therefore be [4, 1, 6, 10, 2, 3], and your program should return the new array as a string, so for this example your program would return 4161023. The first element in the array will always be an integer greater than or equal to 0 and less than the size of the array.
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

/*
we can set up a list to pass the values to
first determine the starting index

iterate through the array in a circular fashion until all elements have been passed
pass the elements from temp list to a string 
return the string value
*/
string ArrayRotation(int arr[], int size) 
{
	// our temp list
	vector <int> list;

	// iterating through the array until all elements have been passed;
	int index = arr[0];
	int count = 0;

	while (count < size)
	{
		// passing the value
		list.push_back(arr[index]);

		// updating our index
		index = (index%size) + 1;
		if (index == size)
		{
			index = 0;
		}
		count++;
	}

	// converting result into a string
	ostringstream convert;
	for (int x = 0; x < list.size(); x++)
	{
		convert << list[x];
	}

	return convert.str();
}

int main() 
{
	int A[] = { 2, 3, 4, 1, 6, 10 };
	int B[] = { 3, 2, 1, 6 };
	int C[] = { 4, 3, 4, 3, 1, 2 };

	cout << ArrayRotation(A, sizeof(A)/sizeof(A[0])) << endl; // 4161023
	cout << ArrayRotation(B, sizeof(B) / sizeof(B[0])) << endl; // 6321
	cout << ArrayRotation(C, sizeof(C) / sizeof(C[0])) << endl; // 124343
	return 0;
}
