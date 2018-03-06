// This challenge will require knowledge of chess pieces and their movements.
/*
have the function QuickKnight(str) read str which will be a string consisting of the location of a knight on a standard 8x8 chess board with no other pieces on the board and another space on the chess board. The structure of str will be the following: "(x y)(a b)" where (x y) represents the position of the knight with x and y ranging from 1 to 8 and (a b) represents some other space on the chess board with a and b also ranging from 1 to 8. Your program should determine the least amount of moves it would take the knight to go from its position to position (a b). For example if str is "(2 3)(7 5)" then your program should output 3 because that is the least amount of moves it would take for the knight to get from (2 3) to (7 5) on the chess board.
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;


int analyzeUp(int, int);
int analyzeDown(int, int);
int analyzeLeft(int, int);
int analyzeRight(int, int);
vector <int>  newLocation(int, int, int);

/*
first step is to extract the points for our knight and the destination

can be solved using a BFS approach
we take current location
check all possible valid moves the knight can make
we store the movement and its cost in a queue

we repeat the same steps now with a different current location
if path is valid we add 1 to the current cost to get a new movement cost
when we reach destination we return the total cost 
*/
int QuickKnight(string str) 
{
	// get location for knight and destination
	int knightX = str[1] - 48;
	int knightY = str[3] -48;
	int destinationX = str[6] - 48;
	int destinationY = str[8] - 48;

	// result
	int cost = 0;

	// making the point pair, alongside its cost to add to the queue
	vector <int> source;
	source.push_back(knightX);
	source.push_back(knightY);
	source.push_back(0);

	// adding source
	queue < vector<int> > list;
	list.push(source);

	while (!list.empty())
	{
		vector <int> currentLocation = list.front();
		list.pop();

		// for ease of access 
		int x = currentLocation[0];
		int y = currentLocation[1];
		int cost = currentLocation[2];

		// check if we reached the destination
		if (x == destinationX && y == destinationY)
		{
			return cost;
		}

		/*
		check for valid knight movements

		rules set: if helper method returns 3 it can move the desired direction and both end directions
		example: knight can go up and move left and right
		example: knight can go left and move up and down

		returns 2 = left  or up
		returns 1 = right or down
		returns 0 = no valid movement
		*/
		// up
		if (analyzeUp(x, y) == 3)
		{
			list.push(newLocation(x + 2, y + 1, cost + 1));
			list.push(newLocation(x + 2, y - 1, cost + 1));
		}
		else if (analyzeUp(x, y) == 2)
		{
			list.push(newLocation(x + 2, y + 1, cost + 1));
		}
		else if (analyzeUp(x, y) == 1)
		{
			list.push(newLocation(x + 2, y - 1, cost + 1));
		}
		// down
		if (analyzeDown(x, y) == 3)
		{
			list.push(newLocation(x - 2, y + 1, cost + 1));
			list.push(newLocation(x - 2, y - 1, cost + 1));
		}
		else if (analyzeDown(x, y) == 2)
		{
			list.push(newLocation(x - 2, y + 1, cost + 1));
		}
		else if (analyzeDown(x, y) == 1)
		{
			list.push(newLocation(x - 2, y - 1, cost + 1));
		}
		// left 
		if (analyzeLeft(x, y) == 3)
		{
			list.push(newLocation(x + 1, y + 2, cost + 1));
			list.push(newLocation(x - 1, y + 2, cost + 1));
		}
		else if (analyzeLeft(x, y) == 2)
		{
			list.push(newLocation(x + 1, y + 2, cost + 1));
		}
		else if (analyzeLeft(x, y) == 1)
		{
			list.push(newLocation(x - 1, y + 2, cost + 1));
		}
		// right
		if (analyzeRight(x, y) == 3)
		{
			list.push(newLocation(x + 1, y - 2, cost + 1));
			list.push(newLocation(x - 1, y - 2, cost + 1));
		}
		else if (analyzeRight(x, y) == 2)
		{
			list.push(newLocation(x + 1, y - 2, cost + 1));
		}
		else if (analyzeRight(x, y) == 1)
		{
			list.push(newLocation(x - 1, y - 2, cost + 1));
		}
	}

	return cost;
}


int analyzeUp(int x, int y)
{
	// moving Up 
	int moveUp = x + 2;

	// making sure we are still inbound when moving up 2 steps
	if (moveUp <= 8)
	{
		// condition to check if we can move left or right
		if (y + 1 <= 8 && y-1 >= 1)
		{
			return 3;
		}
		else if (y + 1 <= 8)
		{
			return 2;
		}
		else if (y - 1 >= 1)
		{
			return 1;
		}
	}

	return 0;
}
int analyzeDown(int x, int y)
{ 
	int moveDown = x - 2;

	if (moveDown >= 1)
	{
		if (y + 1 <= 8 && y - 1 >= 1)
		{
			return 3;
		}
		else if (y + 1 <= 8)
		{
			return 2;
		}
		else if (char(y - 1) >= 1)
		{
			return 1;
		}
	}

	return 0;
}
int analyzeLeft(int x, int y)
{
	int moveLeft = y + 2;

	// condition we are inbounds when moving left 2 steps
	if (moveLeft <= 8)
	{
		// condition to check if we can move up or down
		if (x + 1 <= 8 && x - 1 >= 1)
		{
			return 3;
		}
		else if (x + 1 <= 8)
		{
			return 2;
		}
		else if (x - 1 >= 1)
		{
			return 1;
		}
	}

	return 0;
}
int analyzeRight(int x, int y)
{
	int moveRight = y - 2;

	if (moveRight >= 1)
	{
		if (x + 1 <= 8 && x - 1 >= 1)
		{
			return 3;
		}
		else if (x + 1 <= 8)
		{
			return 2;
		}
		else if (x - 1 >= 1)
		{
			return 1;
		}
	}

	return 0;
}

vector <int> newLocation(int x, int y, int cost)
{
	vector <int> temp;
	temp.push_back(x);
	temp.push_back(y);
	temp.push_back(cost);
	return temp;
}

int main() 
{
	cout << QuickKnight("(2 3)(7 5)") << endl; // 3
	cout << QuickKnight("(1 1)(8 8)") << endl; // 6
	cout << QuickKnight("(2 2)(3 3)") << endl; // 2
	return 0;
}