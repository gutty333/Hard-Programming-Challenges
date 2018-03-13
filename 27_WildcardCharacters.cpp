// For this challenge you will determine if a string matches a set of wildcard characters.
/*
have the function WildcardCharacters(str) read str which will contain two strings separated by a space. The first string will consist of the following sets of characters: +, *, and {N} which is optional. The plus (+) character represents a single alphabetic character, the asterisk (*) represents a sequence of the same character of length 3 unless it is followed by {N} which represents how many characters should appear in the sequence where N will be at least 1. Your goal is to determine if the second string exactly matches the pattern of the first string in the input.

For example: if str is "++*{5} gheeeee" then the second string in this case does match the pattern, so your program should return the string true. If the second string does not match the pattern your program should return the string false.
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/*
separate wildcard and result sub string from input
step through result string and check if it follows the rules

at each step we analyze what rule to follow
whether is single character or sequence
if sequence determine if it had default length of 3 or if it is provided with a length

the result string must be parallel to the rules provided by the wildcard
*/
string WildcardCharacters(string str) 
{
	// getting the strings to analyze
	int breakpoint = str.find(' ');
	string wildCard = str.substr(0, breakpoint);
	string result = str.substr(breakpoint + 1, str.length() - breakpoint);

	// step through the wildcard to validate the rule
	int index = 0;
	int step = 0;
	while (index < wildCard.length())
	{
		// checking symbol
		if (wildCard[index] == '+')
		{
			step++;
		}
		else if (wildCard[index] == '*')
		{
			int sequenceLenght = 3;

			// condition to analyze sequence character
			// checking if it falls under default repetition of 3 of if it was assigned a length
			if (index + 1 < wildCard.length())
			{
				// condition to get the assigned length if one is provided
				if (wildCard[index + 1] == '{')
				{
					// getting the length
					string num;
					while (wildCard[index] != '}')
					{
						if (wildCard[index] >= '0' && wildCard[index] <= '9')
						{
							num += wildCard[index];
						}

						index++;
					}

					// converting the gathered number string to an int
					istringstream convert(num);
					convert >> sequenceLenght;
				}
			}

			// first checking for out of bounds
			if (step + sequenceLenght-1 > result.length())
			{
				return "false";
			}
			else
			{
				// loop to ensure the characters are the same in a sequence
				char tempChar = result[step];
				while (sequenceLenght > 0)
				{
					if (result[step] != tempChar)
					{
						return "false";
					}

					sequenceLenght--;
					step++;
				}
			}
		}

		index++;
	}

	// ensure the traversal was parallel
	// in other words for the rules to have been met in the result string we needed to cover everything without any errors
	if (step != result.length())
	{
		return "false";
	}

	return "true";
}

int main() 
{
	cout << WildcardCharacters("++*{5} gheeeee") << endl; // true
	cout << WildcardCharacters("+++++* abcdemmmmmm") << endl; // false
	cout << WildcardCharacters("**+*{2} mmmrrrkbb") << endl; // true
	return 0;
}