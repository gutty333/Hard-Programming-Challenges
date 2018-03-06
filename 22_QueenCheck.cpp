// This challenge will require knowledge of chess pieces and their movements.
/*
have the function QueenCheck(strArr) read strArr which will be an array consisting of the locations of a Queen and King on a standard 8x8 chess board with no other pieces on the board. The structure of strArr will be the following: ["(x1,y1)","(x2,y2)"] with (x1,y1) representing the position of the queen and (x2,y2) representing the location of the king with x and y ranging from 1 to 8. Your program should determine if the king is in check based on the current positions of the pieces, and if so, return the number of spaces it can move to in order to get out of check. If the king is not in check, return -1. For example: if strArr is ["(4,4)","(6,6)"] then your program should output 6. Remember, because only the queen and king are on the board, if the queen is checking the king by being directly adjacent to it, technically the king can capture the queen.
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

bool analyzeCheck(char, char, char, char);

/*
first extract the points from the string array

an approach is to use a helper function that checks queen location to current king location
if checks all possible attacks from the queen

if king is not in check return -1

else we iterate through all valid paths the king can take
if new king location is not outbounds and is not in check we update our total
for each check we can use the helper function with different king location points
*/
int QueenCheck(string strArr[]) 
{
	// getting points for queen and king location
	char queenX = strArr[0][1];
	char queenY = strArr[0][3];
	char kingX = strArr[1][1];
	char kingY = strArr[1][3];

	// check if the king is safe
	if (!analyzeCheck(queenX, queenY, kingX, kingY))
	{
		return -1;
	}

	// value to store our result to total possible safe moves from the king
	int result = 0;

	// iterate through all 8 possible moves a king can make
	// up
	if (!analyzeCheck(queenX, queenY, char(kingX + 1), kingY))
	{
		result++;
	}

	// down
	if (!analyzeCheck(queenX, queenY, char(kingX - 1), kingY))
	{
		result++;
	}

	// left
	if (!analyzeCheck(queenX, queenY, kingX, char(kingY + 1)))
	{
		result++;
	}

	// right
	if (!analyzeCheck(queenX, queenY, kingX, char(kingY - 1)))
	{
		result++;
	}

	// top left
	if (!analyzeCheck(queenX, queenY, char(kingX+1), char(kingY + 1)))
	{
		result++;
	}

	// top right
	if (!analyzeCheck(queenX, queenY, char(kingX + 1), char(kingY - 1)))
	{
		result++;
	}

	// bottom left
	if (!analyzeCheck(queenX, queenY, char(kingX - 1), char(kingY + 1)))
	{
		result++;
	}

	// bottom right
	if (!analyzeCheck(queenX, queenY, char(kingX - 1), char(kingY - 1)))
	{
		result++;
	}


	// check if king can take the queen
	if ((char(abs(int(queenX - kingX)) + 48) == '1' || char(abs(int(queenX - kingX)) + 48) == '0')
		&& (char(abs(int(queenY - kingY)) + 48) == '1' || char(abs(int(queenY - kingY)) + 48) == '0'))
	{
		result++;
	}

	return result;
}

bool analyzeCheck(char queenX, char queenY, char kingX, char kingY)
{
	// first check king is inside the chessboard
	if (kingX > '8' || kingX < '1' || kingY > '8' || kingY < '1')
	{
		return true;
	}

	// check if there is horizontal or vertical check
	if (kingX == queenX || kingY == queenY)
	{
		return true;
	}

	// check if there is any diagonal check
	// top left
	for (char x = queenX, y = queenY; x <= '8' && y <= '8'; x = char(x + 1), y = char(y + 1))
	{
		if (x == kingX && y == kingY)
		{
			return true;
		}
	}
	// bottom left
	for (char x = queenX, y = queenY; x >= '1' && y <= '8'; x = char(x - 1), y = char(y + 1))
	{
		if (x == kingX && y == kingY)
		{
			return true;
		}
	}
	// top right
	for (char x = queenX, y = queenY; x <= '8' && y >= '1'; x = char(x + 1), y = char(y - 1))
	{
		if (x == kingX && y == kingY)
		{
			return true;
		}
	}
	// bottom right
	for (char x = queenX, y = queenY; x >= '1' && y >= '1'; x = char(x - 1), y = char(y - 1))
	{
		if (x == kingX && y == kingY)
		{
			return true;
		}
	}

	return false;
}

int main() 
{
	string A[] = { "(4,4)", "(6,6)" };
	string B[] = { "(1,1)", "(1,4)" };
	string C[] = { "(3,1)", "(4,4)" };
	string D[] = { "(2,2)", "(2,3)" };
	string E[] = { "(1,8)", "(2,7)" };
	string F[] = { "(1,1)", "(8,1)" };
	string G[] = { "(8,2)", "(7,1)" };


	cout << QueenCheck(A) << endl; // 6
	cout << QueenCheck(B) << endl; // 3
	cout << QueenCheck(C) << endl; // -1
	cout << QueenCheck(D) << endl; // 3
	cout << QueenCheck(E) << endl; // 3
	cout << QueenCheck(F) << endl; // 2
	cout << QueenCheck(G) << endl; // 2

	return 0;
}
