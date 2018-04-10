// For this challenge you will determine whether a matrix is symmetric or not.
/*
have the function SymmetricMatrix(strArr) read strArr which will be an array of integers represented as strings. Within the array there will also be "<>" elements which represent break points. The array will make up a matrix where the (number of break points + 1) represents the number of rows. Here is an example of how strArr may look: ["1","0","1","<>","0","1","0","<>","1","0","1"]. There are two "<>", so 2 + 1 = 3. Therefore there will be three rows in the array and the contents will be row1=[1 0 1], row2=[0 1 0] and row3=[1 0 1]. Your program should take the given array of elements, create the proper matrix, and then determine whether the matrix is symmetric, in other words, if matrix M is equal to M transpose. If it is, return the string symmetric and if it isn't return the string not symmetric. A matrix may or may not be a square matrix and if this is the case you should return the string not possible. For the example above, your program should return symmetric.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
first step is to traverse the string array and build a matrix
separate to a different row when we reach the element "<>"

once the matrix is build first check if is a square
we can get a size for the rows and columns
if not a square return "not possible"

if is a square we check if is symmetric
we traverse our build matrix for each row create a column in a new matrix
after new matrix is build we can check that all elements are equals in both
*/
string SymmetricMatrix(string strArr[], int size) 
{
	vector <vector<string> > matrix;
	vector <vector <string> > matrix2;
	vector <string> temp;

	// traversing input array to build matrix
	for (int x = 0; x < size; x++)
	{
		// adding the new row
		if (strArr[x] == "<>")
		{
			matrix.push_back(temp);
			temp.clear();
		}
		else
		{
			temp.push_back(strArr[x]);
		}
	}

	// adding the last row
	matrix.push_back(temp);
	temp.clear();

	// checking that the matrix is squared;
	int width = matrix[0].size();
	int heigth = matrix.size();

	if (width != heigth)
	{
		return "not possible";
	}

	// creating a skeleton for our second matrix
	for (int x = 0; x < heigth; x++)
	{
		vector <string> tempRow;

		matrix2.push_back(tempRow);
	}

	// creating a transpose of our current matrix
	for (int x = 0; x < matrix.size(); x++)
	{
		// get the elements of current row which will represent a column in our second matrix
		for (int y = 0; y < matrix[x].size(); y++)
		{
			temp.push_back(matrix[x][y]);
		}

		// creating the column for our second matrix
		for (int z = 0; z < temp.size(); z++)
		{
			matrix2[z].push_back(temp[z]);
		}

		// reseting the row
		temp.clear();
	}

	// traversal to check if matrix is symmetric
	for (int row = 0; row < matrix.size(); row++)
	{
		for (int col = 0; col < matrix[row].size(); col++)
		{
			if (matrix[row][col] != matrix2[row][col])
			{
				return "not symmetric";
			}
		}
	}

	return "symmetric";
}

int main() 
{
	string A[] = { "1", "0", "1", "<>", "0", "1", "0", "<>", "1", "0", "1" };
	string B[] = { "5", "0", "<>", "0", "5" };
	string C[] = { "1", "2", "4", "<>", "2", "1", "1", "<>", "-4", "1", "-1" };

	cout << SymmetricMatrix(A,sizeof(A)/sizeof(A[0])) << endl; // symmetric
	cout << SymmetricMatrix(B, sizeof(B) / sizeof(B[0])) << endl; // symmetric
	cout << SymmetricMatrix(C, sizeof(C) / sizeof(C[0])) << endl; // not symmetric
	return 0;
}