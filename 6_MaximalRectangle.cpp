// For this challenge you will be searching a matrix for the largest rectangle submatrix.
/*
have the function MaximalRectangle(strArr) take the strArr parameter being passed which will be a 2D matrix of 0 and 1's, and determine the area of the largest rectangular submatrix that contains all 1's. For example: if strArr is ["10100", "10111", "11111", "10010"] then this looks like the following matrix:

For the input above, you can see the bolded 1's create the largest rectangular submatrix of size 2x3, so your program should return the area which is 6. You can assume the input will not be empty.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int getArea(string[], int, int, int);
bool checkArea(string[], int, int, int, int);

/*
One approach is to step through each point

for each point we expand its width and height
we can then check if the possible rectangle is valid
meaning it must be filled with all 1s

if valid we determine the area and update our highest value
*/
int MaximalRectangle(string strArr[], int size)
{
	int total = 1;

	// traverse for valid points to analyze
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < strArr[row].length(); col++)
		{
			// condition to get a starting point to analyze from
			if (strArr[row][col] == '1')
			{
				int area = getArea(strArr, size, row, col);

				// update value
				if (area > total)
				{
					total = area;
				}
			}
		}
	}

	return total;
}

// get area method
// will analyze current point and find a rectangle by expanding out 
int getArea(string arr[], int size, int row, int col)
{
	int tempRow = row;
	int tempCol = col;

	int width = 1;
	int height = 1;
	bool widthExpansion;
	bool heightExpansion;

	while (tempRow + 1 < size || tempCol + 1 < arr[0].length())
	{
		// flags to help determine if either both the width and height were valid in expanding
		widthExpansion = false;
		heightExpansion = false;

		// expand the width or height
		if (tempRow + 1 < size && arr[tempRow + 1][col] == '1')
		{
			tempRow++;
			heightExpansion = true;
		}

		if (tempCol + 1 < arr[0].length() && arr[row][tempCol + 1] == '1')
		{
			tempCol++;
			widthExpansion = true;
		}

		// check if current expansion is a valid rectangle for both the width and height
		if (widthExpansion && heightExpansion && checkArea(arr, row, col, tempRow, tempCol))
		{
			width++;
			height++;
		}
		else if (widthExpansion && checkArea(arr, row, col, tempRow, tempCol)) // valid width expansion
		{
			width++;
		}
		else if (heightExpansion && checkArea(arr, row, col, tempRow, tempCol)) // valid height expansion
		{
			height++;
		}
		else
		{
			return width * height;
		}
	}

	return width * height;
}

// method to check if points provided form a full rectangle
bool checkArea(string arr[], int row, int col, int rowLimit, int colLimit)
{
	for (row; row <= rowLimit; row++)
	{
		for (int y = col; y <= colLimit; y++)
		{
			if (arr[row][y] != '1')
			{
				return false;
			}
		}
	}

	return true;
}

int main() 
{
	string A[] = { "10100", "10111", "11111", "10010" };
	string B[] = { "1011", "0011", "0111", "1111" };
	string C[] = { "101", "111", "001" };

	cout << MaximalRectangle(A, sizeof(A) / sizeof(A[0])) << endl; // 6
	cout << MaximalRectangle(B, sizeof(B) / sizeof(B[0])) << endl; // 8
	cout << MaximalRectangle(C, sizeof(C) / sizeof(C[0])) << endl; // 3
	return 0;

}