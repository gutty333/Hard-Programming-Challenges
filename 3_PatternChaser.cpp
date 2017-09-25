// For this challenge you will be given a string and you will have to determine whether some sort of pattern exists.
/*
 have the function PatternChaser(str) take str which will be a string and return the longest pattern within the string. A pattern for this challenge will be defined as: if at least 2 or more adjacent characters within the string repeat at least twice. So for example "aabecaa" contains the pattern aa, on the other hand "abbbaac" doesn't contain any pattern. Your program should return yes/no pattern/null. So if str were "aabejiabkfabed" the output should be yes abe. If str were "123224" the output should return no null. The string may either contain all characters (a through z only), integers, or both. But the parameter will always be a string type. The maximum length for the string being passed in will be 20 characters. If a string for example is "aa2bbbaacbbb" the pattern is "bbb" and not "aa". You must always return the longest pattern possible. 
*/
#include <iostream>
#include <string>
using namespace std;

// loop and take a substring to compare
// loop again from the corresponding index and compare with the original substring
// Keep track of the longest pattern
// Repeat the process and replace if another longer pattern has been found

string PatternChaser(string str) {
	string pattern, pattern2, result;
	int count,high, index,index2;
	index = high = 0;

	// Loop to analyze any patterns within the string
	do
	{
		for (int x = index; x < str.length(); x++)
		{
			pattern.push_back(str[x]); // begin analyzing the string to find a pattern to compare

			// Once we have a pattern ex. ab
			// Analyze the other values of the string to check if the pattern repeats
			if (pattern.length() > 1) 
			{
				index2 = x + 1;
				do
				{
					for (int y = index2; y < str.length(); y++)
					{
						pattern2.push_back(str[y]);

						if (pattern2 == pattern && pattern.length() > high)
						{
							high = pattern.length();
							result = pattern;
						}
						else if (pattern2.length() == pattern.length())
						{
							// reset back to analyze the other patterns and see if they match to the original
							pattern2.clear(); 
						}
					}
					pattern2.clear();
					index2++;
				} while (index2 < str.length());
			}
		}
		pattern.clear();
		index++;
	} while (index < str.length());
	
	if (high)
	{
		return "yes " + result;
	}
	else
	{
		return "no null";
	}
}

int main() {
	// keep this function call here
	cout << PatternChaser("da2kr32a2") << endl; // yes a2
	cout << PatternChaser("sskfssbbb9bbb") << endl; // yes bbb
	cout << PatternChaser("aabecaa") << endl; //  yes aa
	cout << PatternChaser("abbbaac") << endl; // no null
	cout << PatternChaser("aabejiabkfabed") << endl; // yes abe
	cout << PatternChaser("123224") << endl; // no null
	cout << PatternChaser("aa2bbbaacbbb") << endl; // yes bbb
	return 0;
}