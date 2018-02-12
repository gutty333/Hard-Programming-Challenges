// For this challenge you will be optimally assigning tasks to a number of machines.
/*
have the function OptimalAssignments(strArr) read strArr which will represent an NxN matrix and it will be in the following format: ["(n,n,n...)","(...)",...] where the n's represent integers. This matrix represents a machine at row i performing task at column j. The cost for this is matrix[i][j]. Your program should determine what machine should perform what task so as to minimize the whole cost and it should return the pairings of machines to tasks in the following format: (i-j)(...)... Only one machine can perform one task. For example: if strArr is ["(5,4,2)","(12,4,3)","(3,4,13)"] then your program should return (1-3)(2-2)(3-1) because assigning the machines to these tasks gives the least cost. The matrix will range from 2x2 to 6x6, there will be no negative costs in the matrix, and there will always be a unique answer.
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// NOT FINISHED


bool linearSearch(vector <int>, int);

/*
Here we can apply a greedy approach
first is to convert the string input into integers
we well set a selection criteria that selects the current available task with lowest cost
once a task is selected for that particular machine it cannot be available for the next machines
*/
string OptimalAssignments(string strArr[], int size) {
	vector <vector <int>> newList(size); // 2D vector
	vector <int> taskTaken; // keeps track of the task we have used

	// Make the string argument into a list of integers for ease of handling down the line
	string num;
	int temp;
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

	string result;

	for (int row = 0; row < newList.size(); row++)
	{
		// update our output
		// following the output format rules
		result += '(' + (row + 1) + '-';

		int col = 0;
		int currentLow = col; // keeps track of the current lowest available task 

		// loop to perform our greedy choice for the current machine
		for (col; col < newList[row].size(); col++)
		{
			// condition only selects the lowest available task
			if (newList[row][col] < newList[row][currentLow] && !linearSearch(taskTaken, currentLow))
			{
				currentLow = col;
			}
		}
		cout << endl;
	}

	return "test";
}


// linear search method
bool linearSearch(vector <int> list, int target)
{
	for (int x = 0; x < list.size(); x++)
	{
		if (list[x] == target)
		{
			return true;
		}
	}
	return false;
}

int main() 
{
	string A[] = { "(1,2,1)", "(4,1,5)", "(5,2,1)" };
	string B[] = { "(13,4,7,6)", "(1,11,5,4)", "(6,7,2,8)", "(1,3,5,9)" };
	string C[] = { "(5,4,2)", "(12,4,3)", "(3,4,13)" };
	string D[] = { "(90,75,75,80)", "(35,85,55,65)", "(125,95,90,105)", "(45,110,95,115)" };
	
	// (3,2) , (1,5)
	cout << OptimalAssignments(A, sizeof(A) / sizeof(A[0])) << endl; // (1-1)(2-2)(3-3)
	cout << OptimalAssignments(B, sizeof(B) / sizeof(B[0])) << endl; // (1-2)(2-4)(3-3)(4-1)
	cout << OptimalAssignments(C, sizeof(C) / sizeof(C[0])) << endl; // (1-3)(2-2)(3-1)
	cout << OptimalAssignments(D, sizeof(D) / sizeof(D[0])) << endl; // (1-4)(2-3)(3-2)(4-1) or (1-2)(2-4)(3-3)(4-1)
	return 0;
}