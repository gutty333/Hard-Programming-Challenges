// For this challenge you will be determining the longest common subsequence of two strings.
/*
have the function LCS(strArr) take the strArr parameter being passed which will be an array of two strings containing only the characters {a,b,c} and have your program return the length of the longest common subsequence common to both strings. A common subsequence for two strings does not require each character to occupy consecutive positions within the original strings. For example: if strArr is ["abcabb","bacb"] then your program should return 3 because one longest common subsequence for these two strings is "bab" and there are also other 3-length subsequences such as "acb" and "bcb" but 3 is the longest common subsequence for these two strings.
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
An efficient approach will be to use DP

the technique will be straight forward we first set up our table
This will store solutions to subproblems we solve and allow us to reuse those solutions to solve current problems

We will set our base case
than traverse one of the strings and compare it to the other
the condition we set will check for the optimal solution
for instance if current characters do not match, than select what the most optimal solution is when shift the indexes of either sequence

unlike the brute force approach or recursive approach the DP technique will allow us to avoid having to do more work, since we are storing solutions. In the case when the characters are not equal, instead of solving what happens if we only shift the index in sequence A, we can just take the max from our previously solved problems.
*/
int LCS(string strArr[])
{
	// setting our table
	int size1 = strArr[0].length();
	int size2 = strArr[1].length();
	
	// note we add an extra row and column to store the base cases
	int** table = new int*[size1+1];
	for (int x = 0; x < size1+1; x++)
	{
		table[x] = new int[size2+2];
	}

	// initializing our table with default base cases
	// here if we don't have a sequence to compare than our result will be zero
	for (int row = 0; row <= size1; row++)
	{
		table[row][0] = 0;
	}
	for (int col = 0; col <= size2; col++)
	{
		table[0][col] = 0;
	}

	// loop to traverse the string and tackle each subproblems
	/*
	to visualize it, we first tackle what is the LCS when the size of sequence A is only 1
	than our next subproblem is what is the LCS when size of sequence A is only 2 and so forth
	by the time we get the last character we can utilize the previously solved problems stored in our table to determine the final solution
	*/
	for (int row = 1; row <= size1; row++)
	{
		for (int col = 1; col <= size2; col++)
		{
			// condition to check if current characters are equal, if so than increment the count
			// we take the previous optimal solution and add 1 to it
			if (strArr[0][row - 1] == strArr[1][col - 1])
			{
				table[row][col] = table[row - 1][col - 1] + 1;
			}
			else
			{
				// else here we take what is the most optimal if we either shift the index in sequence A or sequence B
				table[row][col] = max(table[row - 1][col], table[row][col - 1]);
			}
		}
	}

	// the last element in our 2D table represents the optimal solution
	return table[size1][size2];
}

int main() 
{
	string A[] = { "abcabb", "bacb" };
	string B[] = { "abc", "cb" };
	string C[] = { "bcacb", "aacabb" };
	
	cout << LCS(A) << endl; // 3
	cout << LCS(B) << endl; // 1
	cout << LCS(C) << endl; // 3

	return 0;
}