// For this challenge you will be determining squares of certain numbers.
/*
have the function SquareFigures(num) read num which will be an integer. Your program should return the smallest integer that when squared has a length equal to num. For example: if num is 6 then your program should output 317 because 317^2 = 100489 while 316^2 = 99856 which does not have a length of six.
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/*
first get the total length as a squared value
so instance if input is 2, length as value is 10
3 = 100
4 = 1000
etc

we than apply a square root to our length value to determine a starting point
for finding smallest integer that when squared has same length as input
doing the square root, works similar to a binary search, we can eliminate non redundant iterations
*/
long long SquareFigures(int num) 
{
	long long length = 1;

	// base case
	if (num == 1)
	{
		return 0;
	}

	// getting the length as a value
	for (int x = 0; x < num - 1; x++)
	{
		length *= 10;
	}

	// getting start number through square root to avoid having to do a linear approach
	long long start = sqrt(length);
	long long squaredResult = pow(start, 2);

	// iterate from the start integer until the squared result has same length as input
	while (squaredResult < length)
	{
		start++;
		
		// updating our squared result
		squaredResult = pow(start, 2);
	}

	return start;
}

int main() 
{
	cout << SquareFigures(6) << endl; // 317
	cout << SquareFigures(2) << endl; // 4
	cout << SquareFigures(1) << endl; // 0
	cout << SquareFigures(3) << endl; // 10
	cout << SquareFigures(5) << endl; // 100
	cout << SquareFigures(7) << endl; // 1000
	cout << SquareFigures(9) << endl; // 10000
	cout << SquareFigures(11) << endl; // 10000
	return 0;
}
