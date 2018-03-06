// This challenge will require knowledge of basic mathematical combinations.
/*
have the function ChessboardTraveling(str) read str which will be a string consisting of the location of a space on a standard 8x8 chess board with no pieces on the board along with another space on the chess board. The structure of str will be the following: "(x y)(a b)" where (x y) represents the position you are currently on with x and y ranging from 1 to 8 and (a b) represents some other space on the chess board with a and b also ranging from 1 to 8 where a > x and b > y. Your program should determine how many ways there are of traveling from (x y) on the board to (a b) moving only up and to the right. For example: if str is (1 1)(2 2) then your program should output 2 because there are only two possible ways to travel from space (1 1) on a chessboard to space (2 2) while making only moves up and to the right.
*/

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;

/*
first step involves extracting the string values

we can apply a DFS from current location to destination
for example starting at current location
we take any valid paths possible if we move only up or right

if the path is valid we add it to our stack
we repeat the process by analyzing those current points
if the current points match our destination points we update our count on the many ways we can reach the destination
*/
string ChessboardTraveling(string str) 
{
	// extracting point locations from string input
	char destinationX = str[6];
	char destinationY = str[8];

	char currentX = str[1];
	char currentY = str[3];


	// setting up our stack which will store a pair of points
	vector <char> temp;
	temp.push_back(currentX);
	temp.push_back(currentY);

	stack < vector<char> > list;
	list.push(temp);


	// value to keep track of the total possible paths we can take to reach destination;
	int result = 0;

	// loop to perform our DFS
	while (!list.empty())
	{
		// get current spot to analyze its points
		vector <char> currentLocation = list.top();
		list.pop();

		
		// check if current point reached the destination
		if (currentLocation[0] == destinationX && currentLocation[1] == destinationY)
		{
			result++;
		}

		// conditions to check if we can add any other point pairs
		// possible path by moving up
		if (char(currentLocation[0] + 1) <= destinationX)
		{
			vector <char> possiblePoints;
			char possibleX = char(currentLocation[0] + 1);
			char possibleY = currentLocation[1];

			possiblePoints.push_back(possibleX);
			possiblePoints.push_back(possibleY);

			// add the possible pair to our list
			list.push(possiblePoints);
		}

		// possible path by moving to the right
		if (char(currentLocation[1] + 1) <= destinationY)
		{
			vector <char> possiblePoints;
			char possibleX = currentLocation[0];
			char possibleY = char(currentLocation[1] + 1);

			possiblePoints.push_back(possibleX);
			possiblePoints.push_back(possibleY);

			// add the possible pair to our list
			list.push(possiblePoints);
		}
	}

	// output result
	ostringstream convert;
	convert << result;
	return convert.str();
}

int main() 
{
	cout << ChessboardTraveling("(1 1)(2 2)") << endl; // 2
	cout << ChessboardTraveling("(1 1)(3 3)") << endl; // 6
	cout << ChessboardTraveling("(2 2)(4 3)") << endl; // 3
	return 0;
}