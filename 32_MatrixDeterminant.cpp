// For this challenge you will calculate the determinant of a square matrix.
/*
have the function MatrixDeterminant(strArr) read strArr which will be an array of integers represented as strings. Within the array there will also be "<>" elements which represent break points. The array will make up a matrix where the (number of break points + 1) represents the number of rows. Here is an example of how strArr may look: ["1","2","<>","3","4"]. The contents of this array are row1=[1 2] and row2=[3 4]. Your program should take the given array of elements, create the proper matrix, and then calculate the determinant. For the example above, your program should return -2. If the matrix is not a square matrix, return -1. The maximum size of strArr will be a 6x6 matrix. The determinant will always be an integer.
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int calculator(vector < vector<int> >);
int getSum(vector <int>);

/*
first step is to pass the contents of the input array into a matrix layout
for ease of access later on the type will be turned to integers

after building the matrix we check if is not squared

to calculate the determinant we will use a recursive approach
we will pass it a matrix and check for its squared size
base case will be when the matrix is 2x2

at each iteration of the recursive method
we keep track of whether leading value that is multiplied by determinant is positive or negative
we continue to break the matrix down until we reach base case
matrix is broken down based on the rule that is must not be in the same row or column of leading value

This algorithm follows the Laplace Expansion rule
Reference used https://www.mathsisfun.com/algebra/matrix-determinant.html
*/
int MatrixDeterminant(string strArr[], int size) 
{
	vector < vector <int> > matrix;
	vector <int> temp;

	// traversing the input array to build our matrix
	for (int x = 0; x < size; x++)
	{
		// condition to check for breakpoints
		if (strArr[x] == "<>")
		{
			matrix.push_back(temp);
			temp.clear();
		}
		else
		{
			// converting to int
			int value;
			istringstream convert(strArr[x]);
			convert >> value;

			// adding to our row
			temp.push_back(value);
		}
	}

	// adding last row
	matrix.push_back(temp);
	temp.clear();

	// checking if input matrix is square
	for (int row = 0; row < matrix.size(); row++)
	{
		if (matrix[row].size() != matrix.size())
		{
			return -1;
		}
	}

	// getting the result
	return calculator(matrix);
}
 
/*
Determinant calculator method
This takes a squared matrix as input
based on the square size it will either perform the calculation when size of matrix is 2x2
or continue to break down a matrix 
it keeps track of leading value and whether we add or subtract
*/
int calculator(vector < vector<int> > currentMatrix)
{
	// base case when a matrix is 2x2
	if (currentMatrix.size() == 2)
	{
		return (currentMatrix[0][0] * currentMatrix[1][1]) - (currentMatrix[0][1] * currentMatrix[1][0]);
	}

	// flag to keep track of whether to add or subtract
	bool positiveSign = true;

	// list to store results, for calculating after
	vector <int> result;

	// traversing all the leading values for the current matrix
	for (int row = 0; row < 1; row++)
	{
		for (int col = 0; col < currentMatrix.size(); col++)
		{
			// getting the leading value and determine if we add or subtract
			int leadingValue = currentMatrix[row][col];
			if (!positiveSign)
			{
				leadingValue *= -1;
				positiveSign = true;
			}
			else
			{
				positiveSign = false;
			}

			// section to build the new matrix that does not include the row or column of our current leading value
			vector < vector<int> > newMatrix;
			vector <int> temp;

			// iteration for building our new matrix
			for (int x = 0; x < currentMatrix.size(); x++)
			{
				// condition to avoid adding a row that is part of the value
				if (x == row)
				{
					continue;
				}
				else
				{
					for (int y = 0; y < currentMatrix.size(); y++)
					{
						// condition to avoid adding values from a column that are part of the leading value
						if (y == col)
						{
							continue;
						}
						else
						{
							temp.push_back(currentMatrix[x][y]);
						}
					}

					// adding row content to our new matrix
					newMatrix.push_back(temp);

					// clearing the contents of the row
					temp.clear();
				}
			}
			
			// adding result for this leading value into a list
			result.push_back(leadingValue * calculator(newMatrix));

			// reset the new matrix
			newMatrix.clear();
		}
	}

	return getSum(result);
}

// getSum method, returns the sum of a list
int getSum(vector <int> results)
{
	int total = 0;
	for (int x = 0; x < results.size(); x++)
	{
		total += results[x];
	}

	return total;
}

int main() 
{
	string A[] = { "1", "2", "<>", "3", "4" };
	string B[] = { "5", "0", "<>", "0", "5" };
	string C[] = { "1", "2", "4", "<>", "2", "1", "1", "<>", "4", "1", "1" };
	string D[] = { "3", "8", "<>", "4", "6" };
	string E[] = { "6", "1", "1", "<>", "4", "-2", "5", "<>", "2", "8", "7" };
	string F[] = { "1", "2", "<>", "2", "1", "<>", "1", "1", "1" };
	string G[] = { "1", "2", "3", "4", "5", "<>", "2", "2", "4", "5", "6", "<>", "3", "4", "4", "5", "6", "<>", "4", "5", "5", "0", "1", "<>", "5", "6", "6", "1", "1" };
	string H[] = { "1000", "2", "3", "4", "5", "<>", "2", "2", "4", "5", "6", "<>", "3", "4", "4", "5", "6", "<>", "4", "5", "5", "0", "1", "<>", "5", "6", "6", "1", "1000" };
	string I[] = { "1", "2", "3", "4", "<>", "2", "6", "4", "2", "<>", "6", "6", "1", "1", "<>", "4", "8", "0", "1" };
	string J[] = { "6", "4", "2", "<>", "6", "1", "1", "<>", "8", "0", "1" };
	string K[] = { "1", "2", "3", "4", "<>", "5", "6", "7", "8", "<>", "9", "10", "11", "12", "<>", "13", "14", "15", "16" };
	string L[] = { "4", "2", "1", "3", "<>", "8", "2", "6", "6", "<>", "1", "1", "4", "2", "<>", "0", "1", "6", "6" };
	string M[] = { "2", "6", "4", "<>", "6", "6", "1", "<>", "4", "8", "0" };
	string N[] = { "2", "4", "5", "6", "<>", "4", "4", "5", "6", "<>", "5", "5", "0", "1", "<>", "6", "6", "1", "1" };

	cout << MatrixDeterminant(A, sizeof(A)/sizeof(A[0])) << endl;  // -2
	cout << MatrixDeterminant(B, sizeof(B) / sizeof(B[0])) << endl; // 25
	cout << MatrixDeterminant(C, sizeof(C) / sizeof(C[0])) << endl; // -4
	cout << MatrixDeterminant(D, sizeof(D) / sizeof(D[0])) << endl;  // -14
	cout << MatrixDeterminant(E, sizeof(E) / sizeof(E[0])) << endl;  // -306
	cout << MatrixDeterminant(F, sizeof(F) / sizeof(F[0])) << endl;  // -1
	cout << MatrixDeterminant(G, sizeof(G) / sizeof(G[0])) << endl;  // 43
	cout << MatrixDeterminant(H, sizeof(H) / sizeof(H[0])) << endl;  // 49801192
	cout << MatrixDeterminant(I, sizeof(I) / sizeof(I[0])) << endl;  // -294
	cout << MatrixDeterminant(J, sizeof(J) / sizeof(J[0])) << endl;  // -2
	cout << MatrixDeterminant(K, sizeof(K) / sizeof(K[0])) << endl;  // 0
	cout << MatrixDeterminant(L, sizeof(L) / sizeof(L[0])) << endl;  // -148
	cout << MatrixDeterminant(M, sizeof(M) / sizeof(M[0])) << endl;  // 104
	cout << MatrixDeterminant(N, sizeof(N) / sizeof(N[0])) << endl;  // -62
	return 0;
}
