// For this challenge you will be optimally assigning tasks to a number of machines.
/*
have the function OptimalAssignments(strArr) read strArr which will represent an NxN matrix and it will be in the following format: ["(n,n,n...)","(...)",...] where the n's represent integers. This matrix represents a machine at row i performing task at column j. The cost for this is matrix[i][j]. Your program should determine what machine should perform what task so as to minimize the whole cost and it should return the pairings of machines to tasks in the following format: (i-j)(...)... Only one machine can perform one task. For example: if strArr is ["(5,4,2)","(12,4,3)","(3,4,13)"] then your program should return (1-3)(2-2)(3-1) because assigning the machines to these tasks gives the least cost. The matrix will range from 2x2 to 6x6, there will be no negative costs in the matrix, and there will always be a unique answer.
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// Not finished, Logical Error

// Linear Search
bool search(vector <int> arr, int size, int value)
{
	for (int x = 0; x < size; x++)
	{
		if (value == arr[x])
		{
			return true;
		}
	}
	return false;
}

// Optimal Checker function
// Recursive function to check for the optimal assignment
// It checks for the zeros corresponding to its row it then checks the whole matrix to find which columns correspond to each machine
// Since the other steps have been done prior a solution will be found no MATTER WHAT :)
void optimalChecker(string& optimal, vector <vector <int>> strArr, int& row, int col, int size, vector <int>& colList)
{
	// Check to see if we found an optimal solution
	if (colList.size() == size)
	{
		return;
	}
	else if (row < size && colList.size() == row)
	{
		optimal.push_back('(');
		optimal.push_back(char(row + 49));
		optimal.push_back('-');
		for (col; col < size && row < size; col++)
		{
			// Set the possible combinations
			if (strArr[row][col] == 0 && !search(colList, colList.size(), col))
			{
				colList.push_back(col); // Keep track of the column location for that combination
				// Check the current combination
				optimal.push_back(char(colList[colList.size()-1] + 49));
				optimal.push_back(')');
				row++;
				optimalChecker(optimal, strArr, row, 0, size, colList);
			}
		}
	}
	// If no match was found with the current combination
	// Note that a match will be found regardless
	// Basically this will take a step back and allow us to analyze other possible combinations
	if (colList.size() != size)
	{
		optimal.erase(optimal.size()-5); // Remove the output column
		row--; // Trace back to previous row
		colList.pop_back(); // Remove last recorded column index
	}
	else
	{
		return;
	}
}

// This function performs the step of step 3 in the Hungarian method
bool lineCover(vector <vector <int>> newList, int size, vector<int>& rowList, vector <int>& colList)
{
	// Step 3 includes covering the zeros of the matrix
	int count,x,y;
	int lines = 0;
	rowList.clear();
	colList.clear();

	// Loop checking for multiple zeros in a x
	for (x = 0; x < size; x++)
	{
		count = 0;
		for (y = 0; y < size; y++)
		{
			if (newList[x][y] == 0)
			{
				count++;
			}
		}
		if (count > 1)
		{
			lines++;
			rowList.push_back(x);
		}
	}
	// Loop to check for zeros in the columns
	for (y = 0; y < size; y++)
	{
		count = 0;
		for (x = 0; x < size; x++)
		{
			if (newList[x][y] == 0 && !search(rowList, rowList.size(), x))
			{
				count++;
			}
		}
		if (count >= 1)
		{
			lines++;
			colList.push_back(y);
		}
	}

	if (lines == size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// This function will performs the procedures of step 5 found in the Hungarian method
void smallestEntry(vector<vector <int>>& newList, int size, vector <int> rowList, vector <int> colList)
{
	int x, y, low;
	// Step 5 we find the smallest entry not covered by a line

	do
	{
		for (x = 0; x < size; x++)
		{
			low = 10000 * 1000;
			// Only checking the uncovered lines
			// In this case if that column was covered by a line, ignore and analyze the next
			if (!search(rowList, rowList.size(), x))
			{
				for (y = 0; y < size; y++)
				{
					// Here also make sure that if the column was cover ignore values that fall in that column
					if (!search(colList, colList.size(), y) && newList[x][y] < low)
					{
						low = newList[x][y];
					}
				}
			}
			
			// Subtracting 5 from each uncovered row
			for (x = 0; x < size; x++)
			{
				if (!search(rowList, rowList.size(), x))
				{
					for (y = 0; y < size; y++)
					{
						newList[x][y] -= 5;
					}
				}
			}
			
			// Adding 5 to each covered column
			for (y = 0; y < size; y++)
			{
				if (search(colList, colList.size(), y))
				{
					for (x = 0; x < size; x++)
					{
						newList[x][y] += 5;
					}
				}
			}
		}
	} while (!lineCover(newList, size, rowList, colList));
	// Continues to loop back to step 3 until the minimum number of lines is equal to n
}

string OptimalAssignments(string strArr[], int size) {
	vector <vector <int>> newList(size); // 2D vector
	string num;
	int temp;
	// Make the string argument into a list of integers for ease of handling down the line
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < strArr[x].length(); y++)
		{
			if ((strArr[x][y] == '(' || strArr[x][y] == ')' || strArr[x][y] == ',') && !num.empty())
			{
				istringstream(num) >> temp;
				newList[x].push_back(temp);
				num.clear();
			}
			else if (isdigit(strArr[x][y]))
			{
				num += strArr[x][y];
			}
		}
	}

	// Here we perform step 1 from the Hungarian method
	// This includes subtracting the smallest value from its current row
	int row, col;
	int low;
	for (row = 0; row < size; row++)
	{
		low = 1000 * 100000;
		// Finding the low value for that row
		for (col = 0; col < size; col++)
		{
			if (newList[row][col] < low)
			{
				low = newList[row][col];
			}
		}
		// Subtract that value from the current row it belongs to
		for (col = 0; col < size; col++)
		{
			newList[row][col] -= low;
		}
	}

	// Here is step 2 from the Hungarian method
	// Now we subtract the smallest value from the columns
	for (col = 0; col < newList[0].size(); col++)
	{
		low = 1000 * 10000;
		// Find the low entry in the column
		for (row = 0; row < size; row++)
		{
			if (newList[row][col] < low)
			{
				low = newList[row][col];
			}
		}
		// Subtract the low entry from its current column
		for (row = 0; row < size; row++)
		{
			newList[row][col] -= low;
		}
	}

	// Step 4 checking if the number of covering lines is equal to n
	// n = size
	vector <int> rowList;
	vector <int> colList;
	string optimal;
	if (lineCover(newList, size, rowList, colList))
	{
		row = 0;
		colList.clear();
		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y < size; y++)
			{
				cout << newList[x][y] << "    ";
			}
			cout << endl;
		}
		optimalChecker(optimal, newList, row, 0, size, colList);
		return optimal;
	}
	else
	{
		smallestEntry(newList, size, rowList, colList);
		row = 0;
		colList.clear();
		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y < size; y++)
			{
				cout << newList[x][y] << "    ";
			}
			cout << endl;
		}
		optimalChecker(optimal, newList, row, 0, size, colList);
		return optimal;
	}
}

int main() {
	// keep this function call here
	/* Note: In C++ you first have to initialize an array and set
	it equal to the stdin to test your code with arrays. */
	string A[] = { "(1,2,1)", "(4,1,5)", "(5,2,1)" };
	string B[] = { "(13,4,7,6)", "(1,11,5,4)", "(6,7,2,8)", "(1,3,5,9)" };
	string C[] = { "(5,4,2)", "(12,4,3)", "(3,4,13)" };
	string D[] = { "(90,75,75,80)", "(35,85,55,65)", "(125,95,90,105)", "(45,110,95,115)" };
	
	cout << OptimalAssignments(A, sizeof(A) / sizeof(A[0])) << endl; // (1-1)(2-2)(3-3)
	cout << OptimalAssignments(B, sizeof(B) / sizeof(B[0])) << endl; // (1-2)(2-4)(3-3)(4-1)
	cout << OptimalAssignments(C, sizeof(C) / sizeof(C[0])) << endl; // (1-3)(2-2)(3-1)
	cout << OptimalAssignments(D, sizeof(D) / sizeof(D[0])) << endl; // (1-4)(2-3)(3-2)(4-1) or (1-2)(2-4)(3-3)(4-1)
	return 0;
}