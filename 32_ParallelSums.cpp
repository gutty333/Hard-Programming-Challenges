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

int ParallelSums(int arr[], int size) 
{

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
