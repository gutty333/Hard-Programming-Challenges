// For this challenge you will be determining the winning position of a Tic-tac-toe board.
/*
have the function NoughtsDeterminer(strArr) take the strArr parameter being passed which will be an array of size eleven. The array will take the shape of a Tic-tac-toe board with spaces strArr[3] and strArr[7] being the separators ("<>") between the rows, and the rest of the spaces will be either "X", "O", or "-" which signifies an empty space. So for example strArr may be ["X","O","-","<>","-","O","-","<>","O","X","-"]. This is a Tic-tac-toe board with each row separated double arrows ("<>"). Your program should output the space in the array by which any player could win by putting down either an "X" or "O". In the array above, the output should be 2 because if an "O" is placed in strArr[2] then one of the players wins. Each board will only have one solution for a win, not multiple wins. You output should never be 3 or 7 because those are the separator spaces.
*/

#include <iostream>
#include <string>
using namespace std;

bool checkHorizontal(string[],int,string);
bool checkVertical(string[],int,string);
bool checkDiagonal(string[],int, string);

/*
Solution involves traversing the input array
at each index equal to "-" we check for possible solutions
we call on helper functions to check for horizontal,vertical and diagonal solution
*/
int NoughtsDeterminer(string strArr[]) 
{
	// traverse the array
	for (int x = 0; x < 11; x++)
	{
		// condition to check if current spot has a winning condition for either X or O
		if (strArr[x] == "-")
		{
			if (checkHorizontal(strArr, x, "O") || checkVertical(strArr, x, "O") || checkDiagonal(strArr,x, "O"))
			{
				return x;
			}
			else if (checkHorizontal(strArr, x, "X") || checkVertical(strArr, x, "X") || checkDiagonal(strArr,x, "X"))
			{
				return x;
			}
		}
	}
}

// method to check for winning solution going horizontal
bool checkHorizontal(string arr[], int index, string symbol)
{
	// checking which row to analyze
	if (index < 3)
	{
		for (int x = 0; x < 3; x++)
		{
			if (x == index)
			{
				continue;
			}

			if (arr[x] != symbol)
			{
				return false;
			}
		}
		return true;
	}
	else if (index > 3 && index < 7)
	{
		for (int x = 4; x < 7; x++)
		{
			if (x == index)
			{
				continue;
			}

			if (arr[x] != symbol)
			{
				return false;
			}
		}
		return true;
	}
	else if (index > 7)
	{
		for (int x = 8; x < 11; x++)
		{
			if (x == index)
			{
				continue;
			}

			if (arr[x] != symbol)
			{
				return false;
			}
		}
		return true;
	}

	return false;
}

// method to check for a winning solution going vertical
bool checkVertical(string arr[], int index, string symbol)
{
	// locating index location
	if (index < 3)
	{
		if (arr[index+4] == symbol && arr[index+8] == symbol)
		{
			return true;
		}
	}
	else if (index > 3 && index < 7)
	{
		if (arr[index+4] == symbol && arr[index-4] == symbol)
		{
			return true;
		}
	}
	else if (index > 7)
	{
		if (arr[index-4] == symbol && arr[index-8] == symbol)
		{
			return true;
		}
	}

	return false;
}

// method to check for a winning solution going diagonal
bool checkDiagonal(string arr[], int index, string symbol)
{
	// checking which row to analyze
	if (index < 3)
	{
		if ((arr[5] == symbol && arr[8] == symbol && index == 2) || (arr[5] == symbol && arr[10] == symbol && index == 0))
		{
			return true;
		}
	}
	else if (index > 3 && index < 7)
	{
		if ((arr[2] == symbol && arr[8] == symbol && index == 5) || (arr[0] == symbol && arr[10] == symbol && index == 5))
		{
			return true;
		}
	}
	else if (index > 7)
	{
		if ((arr[5] == symbol && arr[0] == symbol && index == 10) || (arr[5] == symbol && arr[2] == symbol && index == 8))
		{
			return true;
		}
	}

	return false;
}

int main() 
{
	string A[] = { "X", "O", "-", "<>", "-", "O", "-", "<>", "O", "X", "-" };
	string B[] = { "X", "-", "O", "<>", "-", "-", "O", "<>", "-", "-", "X" };
	string C[] = { "X", "O", "X", "<>", "-", "O", "O", "<>", "X", "X", "O" };
	string D[] = { "O", "-", "O", "<>", "-", "X", "-", "<>", "-", "-", "X" };
	string E[] = { "X", "-", "X", "<>", "-", "O", "-", "<>", "-", "-", "O" };
	string F[] = { "X", "-", "X", "<>", "-", "-", "O", "<>", "O", "-", "-" };
	string G[] = { "X", "O", "X", "<>", "-", "O", "-", "<>", "-", "-", "-" };

	cout << NoughtsDeterminer(A) << endl; // 2
	cout << NoughtsDeterminer(B) << endl; // 5
	cout << NoughtsDeterminer(C) << endl; // 4 
	cout << NoughtsDeterminer(D) << endl; // 1
	cout << NoughtsDeterminer(E) << endl; // 1
	cout << NoughtsDeterminer(F) << endl; // 1
	cout << NoughtsDeterminer(G) << endl; // 9
	return 0;
}