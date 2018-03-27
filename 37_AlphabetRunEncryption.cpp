// For this challenge you will be decoding a message.
/*
have the function AlphabetRunEncryption(str) read the str parameter being passed which will be an encrypted string and your program should output the original decrypted string. The encryption being used is the following: For every character i in str up to the second to last character, take the i and i+1 characters and encode them by writing the letters of the alphabet, in order, that range in the same direction between those chosen characters. For example: if the original string were bo then it would be encoded as cdefghijklmn, but if the string were boa then bo is encoded as cdefghijklmn and oa is encoded as nmlkjihgfedcb with the final encrypted string being cdefghijklmnnmlkjihgfedcb. So str may be something like the encrypted string just written, and your program should decrypt it and output the original message.

The input string will only contains lowercase characters (a...z). There are also three important rules to this encryption based on specific character sequences.

1) If the original string contains only one letter between two chosen characters, such as the string ac then this would be encrypted as bR with R standing for what direction in the alphabet to go in determining the original characters. The encrypted string bR represents ac but the encrypted string bL represents ca (R = right, L = left).

2) If the original string contains zero letters between two chosen characters, such as the string ab then this would be encrypted as abS, with S representing the fact that no decryption is needed on the two letters preceding S. For example, if the original string were aba then the encryption would be abSbaS, but be careful because decrypting this you get abba, but the actual original string is aba.

3) If the original string contains a repeat of letters, such as the string acc then this would be encrypted as bRcN, with N representing the fact that no change in characters occurred on the character preceding N. The input string will never only be composed of repeated characters.
*/

#include <iostream>
#include <string>
using namespace std;

void sequenceBreak(string&, char, char, bool&, bool&);

/*
as we traverse the string we check if next character is an increment or decrement alphabetically
we keep track of our starting letter and ending letter

when sequence breaks, if it broke due to a letter
we write out the pair (cdef) = bg

else if next letter of start is 'N' just process the repeat

if next letter of start/current is 'R' get pair from right to left
if is 'L' get pair from left to right

if next letter of start/current is 'S' process the pair
note always check for possible repeats, that is if another pair starts with same letter
as previous pair (abba = aba)
*/
string AlphabetRunEncryption(string str)
{
	char start = NULL;
	char end = NULL;
	bool forward = false;
	bool backward = false;

	string result = "";
	string temp = "";

	// traverse the string
	for (int current = 0; current < str.length(); current++)
	{
		// condition to determine a possible sequence start
		if (start == NULL)
		{
			start = str[current];
			end = str[current];
		}
		// forward sequence = a->b->c etc 
		// providing a bound check in case of neighboring characters that belong to the S rule
		else if (str[current] == char(end + 1) && current < str.length() - 2 && str[current + 2] != 'S')
		{
			end = str[current];
			forward = true;
		}
		// backward sequence = c->b->a etc
		else if (str[current] == char(end - 1) && current < str.length()-2 && str[current + 2] != 'S')
		{
			end = str[current];
			backward = true;
		}
		// contains no letter between the characters
		else if (str[current] == 'S')
		{
			// first check for no repeats before appending
			if (!result.empty() && result[result.length() - 1] == start)
			{
				result.push_back(end);
			}
			else
			{
				result.push_back(start);
				result.push_back(end);
			}

			// reseting our start and end characters to analyze a new sequence
			start = end = NULL;
		}
		// condition for repeat in letters
		else if (str[current] == 'N')
		{
			// fix possible sequence break
			if (end != start)
			{
				sequenceBreak(result, start, str[current-2], forward, backward);
			}

			// append repeating character
			result.push_back(end);

			// reseting our start and end characters
			start = end = NULL;
		}
		// single letter between characters going to the right direction
		else if (str[current] == 'R')
		{
			// checking for repeats
			if (!result.empty() && result[result.length() - 1] == char(start - 1))
			{
				result.push_back(char(start + 1));
			}
			else
			{
				result.push_back(char(start - 1));
				result.push_back(char(start + 1));
			}

			// reseting our start and end characters
			start = end = NULL;
		}
		// single letter going to the left direction
		else if (str[current] == 'L')
		{
			if (!result.empty() && result[result.length() - 1] == char(start + 1))
			{
				result.push_back(char(start - 1));
			}
			else
			{
				result.push_back(char(start + 1));
				result.push_back(char(start - 1));
			}

			// reseting our start and end characters
			start = end = NULL;
		}
		// if no other conditions are met a sequence was broken due to different characters
		else
		{
			// will analyze sequence only when all valid character pertaining to the sequence are gathered
			// if not analyzed we continue appending 
			if ((start != char(end + 1) && start != char(end - 1) && start != end) &&
				!(current == str.length() - 2 && str[current + 1] >= 'a' && str[current + 1] <= 'z') &&
				current != str.length()-1)
			{
				sequenceBreak(result, start, end, forward, backward);

				// resetting our start and end to the current letter
				start = str[current];
				end = str[current];
			}
			else if (str[current] == char(end + 1))
			{
				end = str[current];
			}
			else if (str[current] == char(end - 1))
			{
				end = str[current];
			}
		}
	}

	// final condition in case last character is part of a sequence that was not analyzed
	if (end >= 'a' && end <= 'z')
	{
		sequenceBreak(result, start, end, forward, backward);
	}

	return result;
}

// helper function that will update our result when a sequence breaks due to different alphabetical characters
void sequenceBreak(string& result, char start, char end, bool& forward, bool& backward)
{
	// checking the direction
	if (forward)
	{
		// avoiding repeats
		if (!result.empty() && result[result.length() - 1] == char(start - 1))
		{
			result.push_back(char(end + 1));
		}
		else
		{
			result.push_back(char(start - 1));
			result.push_back(char(end + 1));
		}

		forward = false;
	}
	else if (backward)
	{
		if (!result.empty() && result[result.length() - 1] == char(start + 1))
		{
			result.push_back(char(end - 1));
		}
		else
		{
			result.push_back(char(start + 1));
			result.push_back(char(end - 1));
		}

		backward = false;
	}
}

int main() 
{
	cout << AlphabetRunEncryption("cdefghijklmnnmlkjihgfedcb") << endl; // boa
	cout << AlphabetRunEncryption("bcdefghijklmnopqrstN") << endl; // att
	cout << AlphabetRunEncryption("abSbaSaNbR") << endl; // abaac
	cout << AlphabetRunEncryption("defghijklmnnmlkjihgfedeS") << endl; // code
	return 0;
}