// For this challenge you will be checking if a Sudoku board is legal.
/*
have the function SudokuQuadrantChecker(strArr) read the strArr parameter being passed which will represent a 9x9 Sudoku board of integers ranging from 1 to 9. The rules of Sudoku are to place each of the 9 integers integer in every row and column and not have any integers repeat in the respective row, column, or 3x3 sub-grid. The input strArr will represent a Sudoku board and it will be structured in the following format: ["(N,N,N,N,N,x,x,x,x)","(...)","(...)",...)] where N stands for an integer between 1 and 9 and x will stand for an empty cell. Your program will determine if the board is legal; the board also does not necessarily have to be finished. If the board is legal, your program should return the string legal but if it isn't legal, it should return the 3x3 quadrants (separated by commas) where the errors exist. The 3x3 quadrants are numbered from 1 to 9 starting from top-left going to bottom-right.

For example, if strArr is: ["(1,2,3,4,5,6,7,8,1)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(1,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)"] then your program should return 1,3,4 since the errors are in quadrants 1, 3 and 4 because of the repeating integer 1.

Another example, if strArr is: ["(1,2,3,4,5,6,7,8,9)","(x,x,x,x,x,x,x,x,x)","(6,x,5,x,3,x,x,4,x)","(2,x,1,1,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,x)","(x,x,x,x,x,x,x,x,9)"] then your program should return 3,4,5,9.
*/

#include <iostream>
#include <string>
using namespace std;

// Helper function to help determine in which quadrant the error is located
void quadrantLocation(string& result, int x, int y)
{
	if (x < 3)
	{
		if (y < 3)
		{
			result += ",1";
		}
		else if (y >= 3 && y < 6)
		{
			result += ",2";
		}
		else if (y >= 6 && y < 9)
		{
			result += ",3";
		}
	}
	else if (x >= 3 && x < 6)
	{
		if (y < 3)
		{
			result += ",4";
		}
		else if (y >= 3 && y < 6)
		{
			result += ",5";
		}
		else if (y >= 6 && y < 9)
		{
			result += ",6";
		}
	}
	else if (x >= 6 && x < 9)
	{
		if (y < 3)
		{
			result += ",7";
		}
		else if (y >= 3 && y < 6)
		{
			result += ",8";
		}
		else if (y >= 6 && y < 9)
		{
			result += ",9";
		}
	}
}
// Overload function but this time we want to find the range of the quadrant
// This will aid for when searching the current quadrant to check if the number repeats
void quadrantLocation(int x, int y, int& rowSize, int& columnSize)
{
	if (x < 3)
	{
		rowSize = 3;
		if (y < 3)
		{
			columnSize = 3;
		}
		else if (y >= 3 && y < 6)
		{
			columnSize = 6;
		}
		else if (y >= 6 && y < 9)
		{
			columnSize = 9;
		}
	}
	else if (x >= 3 && x < 6)
	{
		rowSize = 6;
		if (y < 3)
		{
			columnSize = 3;
		}
		else if (y >= 3 && y < 6)
		{
			columnSize = 6;
		}
		else if (y >= 6 && y < 9)
		{
			columnSize = 9;
		}
	}
	else if (x >= 6 && x < 9)
	{
		rowSize = 9;
		if (y < 3)
		{
			columnSize = 3;
		}
		else if (y >= 3 && y < 6)
		{
			columnSize = 6;
		}
		else if (y >= 6 && y < 9)
		{
			columnSize = 9;
		}
	}
}

string SudokuQuadrantChecker(string strArr[], int size) {
	// Removing unnecessary characters such as commas and parentheses
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < strArr[row].length(); col++)
		{
			if (strArr[row][col] == '(' || strArr[row][col] == ')' || strArr[row][col] == ',')
			{
				strArr[row].erase(strArr[row].begin() + col);
			}
		}
	}

	// Analyzing the rules
	string quadrant ="";
	int rowIndex, colIndex;
	for (int x = 0; x < size; x++)
	{
		for (int current = 0; current < size; current++)
		{
			for (int y = 0; y < size; y++)
			{
				// Checking for repetition in rows and columns
				if (strArr[x][current] == strArr[x][y] && y != current && strArr[x][current] != 'x') // Rows
				{
					quadrantLocation(quadrant, x, current); // Function call to provide the error location
					break;
				}
				else if (strArr[x][current] == strArr[y][current] && y != x && strArr[x][current] != 'x') // Columns
				{
					quadrantLocation(quadrant, x, current); // Function call to provide the error location
					break;
				}
				else if (strArr[x][current] != 'x')
				{
					quadrantLocation(x, current, rowIndex, colIndex); // Function call to provide the current quadrant we need to analyze
					int i, z;
					// Switch statements to find the starting index for the current quadrant
					switch (rowIndex)
					{
					case 3:
						i = 0;
						break;
					case 6:
						i = 3;
						break;
					case 9:
						i = 6;
						break;
					}
					switch (colIndex)
					{
					case 3:
						z = 0;
						break;
					case 6:
						z = 3;
						break;
					case 9:
						z = 6;
						break;
					}
					// Loop to check if numbers repeat in the current quadrant
					for (i; i < rowIndex; i++)
					{
						for (z; z < colIndex; z++)
						{
							if (x == i && z == current)
							{
								continue;
							}
							else if (strArr[x][current] == strArr[i][z]) // Check if the numbers repeat
							{
								// Function call to find error location when the quadrant contains repeating numbers
								quadrantLocation(quadrant, i, z);
								break;
							}
						}
					}
				}
			}
		}
	}

	if (quadrant.length() > 0)
	{
		quadrant.erase(quadrant.begin() + 0);
		for (int r = 0; r < quadrant.length(); r++) // Safeguard in the case we have the same quadrant listed multiple times
		{
			if (isdigit(quadrant[r]))
			{
				for (int t = 0; t < quadrant.length(); t++)
				{
					if (t == r)
					{
						continue;
					}
					else if (isdigit(quadrant[t]) && quadrant[r] == quadrant[t])
					{
						quadrant.erase(quadrant.begin() + t);
						quadrant.erase(quadrant.begin() +(t- 1));
					}
				}
			}
		}
		return quadrant;
	}
	else
	{
		return "legal";
	}
}

int main() {

	// keep this function call here
	/* Note: In C++ you first have to initialize an array and set
	it equal to the stdin to test your code with arrays. */

	string A[] = { "(1,2,3,4,5,6,7,8,1)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(1,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)" };
	string B[] = { "(1,2,3,4,5,6,7,8,9)", "(x,x,x,x,x,x,x,x,x)", "(6,x,5,x,3,x,x,4,x)", "(2,x,1,1,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,9)" };
	string C[] = { "(1,2,3,4,5,6,7,8,9)", "(4,5,6,1,2,3,x,x,x)", "(7,8,9,x,x,6,x,x,x)", "(2,3,4,x,x,x,x,x,x)", "(5,6,7,x,x,x,x,x,x)", "(8,9,1,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,x)", "(x,x,x,x,x,x,x,x,1)" };
	cout << SudokuQuadrantChecker(A, sizeof(A) / sizeof(A[0])) << endl; // 1,3,4
	cout << SudokuQuadrantChecker(B, sizeof(B) / sizeof(B[0])) << endl; // 3,4,5,9
	cout << SudokuQuadrantChecker(C, sizeof(C) / sizeof(C[0])) << endl; // 2
	return 0;
}