// For this challenge you will determine how many times you can jump around within an array.
/*
have the function ArrayJumping(arr) take the array of numbers stored in arr and first determine the largest element in the array, and then determine whether or not you can reach that same element within the array by moving left or right continuously according to whatever integer is in the current spot. If you can reach the same spot within the array, then your program should output the least amount of jumps it took. For example: if the input is [2, 3, 5, 6, 1] you'll start at the spot where 6 is and if you jump 6 spaces to the right while looping around the array you end up at the last element where the 1 is. Then from here you jump 1 space to the left and you're back where you started, so your program should output 2. If it's impossible to end up back at the largest element in the array your program should output -1. The largest element in the array will never equal the number of elements in the array. The largest element will be unique.
*/

#include <iostream>
#include <string>
#include <queue>
#include <map>
using namespace std;

/*
first locate the largest number in the array
based on the target location we get the left and right index array jumps

using BFS we will store the new index locations into our queue
note that we keep track of our count
we also ignore any indexes that have already been analyzed
we continue this process until either everything has been analyzed or the target was found
*/
struct node
{
	int index; 
	int count;
};

int ArrayJumping(int arr[], int size) 
{
	int target = 0;
	int index;

	// map to later check if an index has already been analyzed;
	map <int, bool> indexFound;

	// first locate the largest number
	for (int x = 0; x < size; x++)
	{
		indexFound[x] = false;

		if (arr[x] > target)
		{
			target = arr[x];
			index = x;
		}
	}

	// gathering the left and right index based on the target location
	// also setting conditions for bound checking
	int leftIndex = index - target;
	while(leftIndex < 0)
	{
		leftIndex = size + leftIndex;
	}
	int rightIndex = index + target;
	while (rightIndex > size-1)
	{
		rightIndex = rightIndex - size;
	}

	// nodes to represent the left and right locations after an array jump
	node left;
	left.index = leftIndex;
	left.count = 1;

	node right;
	right.index = rightIndex;
	right.count = 1;

	// adding them to our queue
	queue <node> list;
	list.push(left);
	list.push(right);


	// BFS
	while (!list.empty())
	{
		// get the current index
		node current = list.front();
		list.pop();

		// check if we hit our target location
		if (current.index == index)
		{
			return current.count;
		}

		// update the discovery for the current index
		indexFound[current.index] = true;

		// gathering the left and right index for the current index
		// also setting conditions for bound checking
		leftIndex = current.index - arr[current.index];
		while (leftIndex < 0)
		{
			leftIndex = size + leftIndex;
		}

		rightIndex = current.index + arr[current.index];
		while (rightIndex > size - 1)
		{
			rightIndex = rightIndex - size;
		}

		// updating the count for both index
		left.index = leftIndex;
		left.count = current.count + 1;
		right.index = rightIndex;
		right.count = current.count + 1;

		// check if the new indexes have been previously analyzed
		if (!indexFound[left.index])
		{
			indexFound[left.index] = true;
			list.push(left);
		}
		if (!indexFound[right.index])
		{
			indexFound[right.index] = true;
			list.push(right);
		}
	}

	return -1;
}

int main() 
{
	int A[] = { 2, 3, 5, 6, 1 };
	int B[] = { 1, 2, 3, 4, 2 };
	int C[] = { 1, 7, 1, 1, 1, 1 };
	int D[] = { 1, 2, 1, 2, 1, 12 };
	int E[] = { 0, 5, 2 };

	cout << ArrayJumping(A, sizeof(A)/sizeof(A[0])) << endl; // 2
	cout << ArrayJumping(B, sizeof(B) / sizeof(B[0])) << endl; // 3
	cout << ArrayJumping(C, sizeof(C) / sizeof(C[0])) << endl; // 2
	cout << ArrayJumping(D, sizeof(D) / sizeof(D[0])) << endl; // 1
	cout << ArrayJumping(E, sizeof(E) / sizeof(E[0])) << endl; // 2
	return 0;
}