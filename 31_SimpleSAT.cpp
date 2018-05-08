// This challenge will require knowledge of basic Boolean logic.
/*
have the function SimpleSAT(str) read str which will be a string consisting of letters, parenthesis, logical operators and tilde's representing a Boolean formula. For example: str may be "(a&b)|c" which means (a AND b) OR c. Your program should output the string yes if there is some arrangement of replacing the letters with TRUE or FALSE in such a way that the formula equates to TRUE. If there is no possible way of assigning TRUE or FALSE to the letters, then your program should output the string no. In the example above, your program would return yes because a=TRUE, b=TRUE and c=FALSE would make the formula TRUE. Another example: if str is "((a&c)&~a)" which means ((a AND c) AND NOT a) then your program should output no because it is not possible to assign TRUE or FALSE values to the letters to produce a TRUE output.

A Boolean formula will always have at most 5 letters, i.e. a, b, c, d and e. A tilde will never appear outside of a parenthesis, i.e. ~(a&b).
*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

bool checkFormula(map <char, bool>, string, int&);

/*
traverse the string input
any valid letters will be stored inside a map
by default their bool value will be set to true
only condition in which they are set to false is if there is an AND NOT sequence

to analyze the formula we will use a recursive method
we keep track of our overall bool value for the section we are analyzing
at each iteration, by storing our operator we update our bool value based on the current value
for example if operator is & and previous overall value is true but current is false
our overall value is updated to false
we make a recursive call for each opening parenthesis
at the same time we update our index
*/
string SimpleSAT(string str) 
{
	map <char, bool> table;

	// traversing the string input to extract our letters
	for (int x = 0; x < str.length(); x++)
	{
		// getting the letters
		if (str[x] >= 'a' && str[x] <= 'z')
		{
			table[str[x]] = true;
		}

		// checking for special condition of an AND NOT sequence
		if (str[x] == '&' && str[x + 1] == '~')
		{
			x += 2;
			table[str[x]] = false;
		}
	}

	int start = 0;
	if (checkFormula(table,str, start)) // calling our method to check if the boolean formula is true or false
	{
		return "yes";
	}
	else
	{
		return "no";
	}
}

// method to analyze the boolean formula from the string input
bool checkFormula(map <char, bool> table, string str, int& index)
{
	int currentResult = 0;
	char currentOperator = 'x';
	bool notEqual = false;

	// traversing the string to analyze it's content
	for (; index < str.length(); index++)
	{
		// condition to enter and analyze a parenthesis section
		if (str[index] == '(')
		{
			index++;
			currentResult = checkFormula(table, str, index); // getting the result from that section
		}
		else if (str[index] >= 'a' && str[index] <= 'z')
		{
			// condition to analyze current value based on our rules
			// get current boolean value and determine if a not operator was applied to it
			bool temp;
			if (notEqual)
			{
				temp = !table[str[index]];
			}
			else
			{
				temp = table[str[index]];
			}
			notEqual = false;

			// analyze which operator was included
			if (currentOperator == '&')
			{
				// we update our current result only if previous was true
				if (currentResult)
				{
					currentResult = temp;
				}
			}
			else if (currentOperator == '|')
			{
				// we can replace our current result only if new boolean value is true
				if (temp)
				{
					currentResult = temp;
				}
			}
			else
			{
				currentResult = temp;
			}
		}
		else if (str[index] == '&') // collect the AND operator
		{
			currentOperator = '&';
		}
		else if (str[index] == '|') // collect the OR operator
		{
			currentOperator = '|';
		}
		else if (str[index] == '~') // collect the NOT operator
		{
			notEqual = true;
		}
		else if (str[index] == ')')
		{
			// sending back our result pertaining to a section
			// this represents our base case
			return currentResult;
		}
	}

	return currentResult;
}

int main() 
{	
	cout << SimpleSAT("(a&b)|c") << endl; // yes
	cout << SimpleSAT("((a&c)&~a)") << endl; // no
	cout << SimpleSAT("(a&b&c)|~a") << endl; // yes
	cout << SimpleSAT("a&(b|c)&~b&~c") << endl; // no
	cout << SimpleSAT("(a&(b)&~c)") << endl; // yes
	cout << SimpleSAT("(c|a|b)&~c") << endl; // yes
	return 0;
}
