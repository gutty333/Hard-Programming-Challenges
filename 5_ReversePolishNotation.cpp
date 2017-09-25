// This challenge will require knowledge of postfix notation for arithmetic expressions.
/*
have the function ReversePolishNotation(str) read str which will be an arithmetic expression composed of only integers and the operators: +,-,* and / and the input expression will be in postfix notation (Reverse Polish notation), an example: 
 (1 + 2) * 3 would be 1 2 + 3 * in postfix notation. Your program should determine the answer for the given postfix expression. For example: if str is 2 12 + 7 / then your program should output 2.
*/

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
using namespace std;


/*
we will utilize a stack ADT
as we traverse the string we store any operands we encounter
when we reach an operator, we pop the last 2 operands from our stack
we evaluate the 2 values and push the result back into the stack
*/
int ReversePolishNotation(string str)
{
	stack <int> list;
	string num = "";

	for (int x = 0; x < str.length(); x++)
	{

		// condition to check if current character represents a number
		if (str[x] >= '0' && str[x] <= '9')
		{
			num.push_back(str[x]);
		}
		else if (str[x] == '+' || str[x] == '-' || str[x] == '*' || str[x] == '/')
		{
			// We retrieve the last 2 values added to the list for evaluation
			int value1 = list.top();
			list.pop();

			int value2 = list.top();
			list.pop();

			// Here we evaluate based on the operation
			// After we add the result to the stack
			int result;
			switch (str[x])
			{
			case '+':
				result = value1 + value2;
				break;

			case '-':
				result = value2 - value1;
				break;

			case '*':
				result = value1* value2;
				break;

			case '/':
				result = value2 / value1;
				break;
			}

			list.push(result);
		}
		else
		{
			// condition to convert our string number to a valid integer
			// will also add it to the stack
			
			if (num.length() >= 1)
			{
				int value;

				istringstream(num) >> value;
				list.push(value);

				num = "";
			}
			
		}
	}

	return list.top();
}

int main() 
{
	cout << ReversePolishNotation("2 12 + 7 /") << endl; // 2
	cout << ReversePolishNotation("1 1 + 1 + 1 +") << endl; // 4
	cout << ReversePolishNotation("4 5 + 2 1 + *") << endl; // 27 
	cout << ReversePolishNotation("6 2 * 5 2 * * 4 2 * * 1 5 + +") << endl; // 966

	return 0;
}