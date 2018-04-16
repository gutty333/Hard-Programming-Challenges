// For this challenge you will be transposing rows and columns within an array.
/*
have the function MatrixBorder(strArr) read the strArr parameter being passed which will represent an NxN matrix filled with 1's and 0's. Your program should determine the number of swaps between two rows or two columns that must be made to change the matrix such that the border of the matrix contains all 1's and the inside contains 0's. The format of strArr will be: ["(n,n,n...)","(...)",...] where n represents either a 1 or 0. The smallest matrix will be a 3x3 and the largest will be a 6x6 matrix.

For example: if strArr is: ["(0,1,1)","(1,1,1)","(1,1,1)"] then you can swap the first two columns and then swap the first two rows to create a matrix with the 1's on the border and the 0 on the inside, therefore your program should output 2.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void swapColumn(vector <vector<char> >&, int);
void swapRow(vector <vector<char> >&, int);

/*
create a matrix based on the input string

simple solution would be to analyze the border rows and columns
as we traverse we check for any 0
if 0 is at a column border swap with a column that has all 1s
if 0 is at a row border swap with a row that all 1s

keep track of the number of swaps made
*/
int MatrixBorder(string strArr[], int size) 
{
	vector < vector <char> > matrix;
	int swapCount = 0;

	// traverse input to create the matrix
	for (int x = 0; x < size; x++)
	{
		vector <char> temp;

		for (int y = 0; y < strArr[x].length(); y++)
		{
			if (strArr[x][y] == '1' || strArr[x][y] == '0')
			{
				temp.push_back(strArr[x][y]);
			}	
		}

		// fill in the row
		matrix.push_back(temp);
	}

	// analyzing the matrix to assure no border has a 0
	for (int row = 0; row < matrix.size(); row++)
	{
		for (int col = 0; col < matrix[row].size(); col++)
		{
			// condition to check the borders only
			if (row == 0 || row == matrix.size() - 1 || col == 0 || col == matrix[row].size()-1)
			{
				if (matrix[row][col] == '0')
				{
					// column needs to be swapped
					if (col == 0 || col == matrix[row].size() - 1)
					{
						swapColumn(matrix, col);
						swapCount++;
					}
					// row needs to be swapped
					else if (row == 0 || row == matrix.size()-1)
					{
						swapRow(matrix, row);
						swapCount++;
					}
				}
			}
		}
	}

	return swapCount;
}

// method to swap 2 columns
void swapColumn(vector <vector<char> >& matrix, int col)
{
	// traverse to find a column that we can swap with
	for (int y = 0; y < matrix[0].size(); y++)
	{
		// ignore same column or border columns
		if (y == col || y == 0 || y == matrix[0].size()-1)
		{
			continue;
		}
		else
		{
			bool valid = true;

			// analyze current column to check if is valid for swapping
			for (int row = 0; row < matrix.size(); row++)
			{
				if (matrix[row][y] == '0')
				{
					valid = false;
					break;
				}
			}

			// preform the swap between the 2 columns
			if (valid)
			{
				char temp;

				for (int x = 0; x < matrix.size(); x++)
				{
					temp = matrix[x][col];
					matrix[x][col] = matrix[x][y];
					matrix[x][y] = temp;
				}

				return;
			}
		}
	}
}

// method to swap 2 rows
void swapRow(vector <vector<char> >& matrix, int row)
{
	// traverse to find a row that we can swap with
	for (int x = 0; x < matrix.size(); x++)
	{
		// ignore the same row, or any border rows
		if (x == row || x== 0 || x == matrix.size()-1)
		{
			continue;
		}
		else
		{
			bool valid = true;

			// analyze current row to check if is valid for swapping
			for (int col = 0; col < matrix[x].size(); col++)
			{
				if (matrix[x][col] == '0')
				{
					valid = false;
					break;
				}
			}

			// preform the swap between the 2 rows
			if (valid)
			{
				char temp;

				for (int y = 0; y < matrix.size(); y++)
				{
					temp = matrix[row][y];
					matrix[row][y] = matrix[x][y];
					matrix[x][y] = temp;
				}

				return;
			}
		}
	}
}

int main() 
{
	string A[] = { "(0,1,1)", "(1,1,1)", "(1,1,1)" };
	string B[] = { "(0,1,0,1)", "(1,1,1,1)", "(0,1,0,1)", "(1,1,1,1)" };

	cout << MatrixBorder(A, sizeof(A) / sizeof(A[0])) << endl; // 2
	cout << MatrixBorder(B, sizeof(B) / sizeof(B[0])) << endl; // 2
	return 0;
}