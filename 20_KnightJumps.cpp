// This challenge will require knowledge of chess pieces and their movements.
/*
have the function KnightJumps(str) read str which will be a string consisting of the location of a knight on a standard 8x8 chess board with no other pieces on the board. The structure of str will be the following: "(x y)" which represents the position of the knight with x and y ranging from 1 to 8. Your program should determine the number of spaces the knight can move to from a given location. For example: if str is "(4 5)" then your program should output 8 because the knight can move to 8 different spaces from position x=4 and y=5.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void analyzeUp(char, char, int&);
void analyzeDown(char, char, int&);
void analyzeLeft(char, char, int&);
void analyzeRight(char, char, int&);

/*
we first extract the points for the knight location

one approach is to use helpers that analyze the possible moves
4 methods used  to extends in the  4 directions

we than check for the final possible move
for example one method is used for top path
if knight can move 2 steps to the top
check the possible paths of moving 1 step to both left or right

for any valid possible complete movements we update our total
*/
int KnightJumps(string str) 
{
	// get knight location
	char currentX = str[1];
	char currentY = str[3];

	// keep track of total
	int result = 0;

	// find possible moves for the knight
	analyzeUp(currentX, currentY, result);
	analyzeDown(currentX, currentY, result);
	analyzeLeft(currentX, currentY, result);
	analyzeRight(currentX, currentY, result);

	return result;
}


void analyzeUp(char x, char y, int& total)
{
	// moving Up 
	char moveUp = char(x + 2);

	// condition to check for out of bounds
	if (moveUp > '8')
	{
		return;
	}

	// condition to check if we can move left or right
	if (char(y + 1) <= '8')
	{
		total++;
	}
	if (char(y - 1) >= '1')
	{
		total++;
	}
}
void analyzeDown(char x, char y, int& total)
{
	char moveDown = char(x - 2);

	if (moveDown < '1')
	{
		return;
	}

	if (char(y + 1) <= '8')
	{
		total++;
	}
	if (char(y - 1) >= '1')
	{
		total++;
	}
}
void analyzeLeft(char x, char y, int& total)
{
	char moveLeft = char(y + 2);

	// condition to check for out of bounds
	if (moveLeft > '8')
	{
		return;
	}

	// condition to check if we can move up or down
	if (char(x + 1) <= '8')
	{
		total++;
	}
	if (char(x - 1) >= '1')
	{
		total++;
	}
}
void analyzeRight(char x, char y, int& total)
{
	char moveRight = char(y - 2);

	if (moveRight < '1')
	{
		return;
	}

	if (char(x + 1) <= '8')
	{
		total++;
	}
	if (char(x - 1) >= '1')
	{
		total++;
	}
}

int main() 
{
	cout << KnightJumps("(4 5)") << endl; // 8
	cout << KnightJumps("(1 1)") << endl; // 2
	cout << KnightJumps("(2 8)") << endl; // 3
	return 0;
}
