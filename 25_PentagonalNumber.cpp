// For this challenge you will be finding how many dots can fit into a pentagonal shape.
/*
have the function PentagonalNumber(num) read num which will be a positive integer and determine how many dots exist in a pentagonal shape around a center dot on the Nth iteration. For example, in the image below you can see that on the first iteration there is only a single dot, on the second iteration there are 6 dots, on the third there are 16 dots, and on the fourth there are 31 dots.
*/

#include <iostream>
#include <string>
using namespace std;

// NOT FINISHED

int PentagonalNumber(int num) 
{
	int total = 1;

	for (int x = 1; x < num; x++)
	{
		total += (5 * x);
	}

	return total;
}

int main() 
{
	cout << PentagonalNumber(2) << endl; // 6
	cout << PentagonalNumber(5) << endl; // 51
	return 0;
}