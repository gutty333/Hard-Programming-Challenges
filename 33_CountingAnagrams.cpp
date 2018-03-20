// For this challenge you will determine how many anagrams exist in a string.
/*
have the function CountingAnagrams(str) take the str parameter and determine how many anagrams exist in the string. An anagram is a new word that is produced from rearranging the characters in a different word, for example: cars and arcs are anagrams. Your program should determine how many anagrams exist in a given string and return the total number. For example: if str is "cars are very cool so are arcs and my os" then your program should return 2 because "cars" and "arcs" form 1 anagram and "so" and "os" form a 2nd anagram. The word "are" occurs twice in the string but it isn't an anagram because it is the same word just repeated. The string will contain only spaces and lowercase letters, no punctuation, numbers, or uppercase letters.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iterator>
using namespace std;


/*
Solution will involve
first traverse the string and extract each word
at each step store the words into a table, with the word and its length

we make comparisons of words with equal length
first ensure they are not repeats
second we iterate and check if all characters match
if true remove previous stored pair from table

continue stepping through the input
until all words have been analyzed
*/
int CountingAnagrams(string str) 
{
	vector <string> list;
	map <string, int> table;
	int total = 0;

	istringstream convert(str);

	// loop to pass the words to our list for ease of use later on
	string current;
	while (convert >> current)
	{
		bool repeat = false;

		// condition to avoid adding repeats
		for (int x = 0; x < list.size(); x++)
		{
			if (current == list[x])
			{
				repeat = true;
				break;
			}
		}

		if (!repeat)
		{
			list.push_back(current);
		}
	}

	// adding first word
	table[list[0]] = list[0].length();

	// loop to analyze each word from our input
	for (int x = 1; x < list.size(); x++)
	{
		// check if there are possible anagrams in our table
		for (map<string, int>::iterator y = table.begin(); y != table.end(); y++)
		{
			// possible match
			if (y->second == list[x].length())
			{
				// ensure is not a repeat
				if (y->first != list[x])
				{
					string temp = y->first;
					bool anagram = true;

					// traverse current words and check if they match
					for (int z = 0; z < list[x].length(); z++)
					{
						int currentIndex = temp.find(list[x][z]);

						// ensure all characters match
						// also that no repeat of characters is found (aabc compared with abbc)
						if (currentIndex == -1)
						{
							// not anagrams so we add new word to the table
							table[list[x]] = list[x].length();
							anagram = false;
							break;
						}
						else
						{
							temp.erase(temp.begin() + currentIndex);
						}
					}

					// update our total;
					if (anagram)
					{
						total++;
						break;
					}
				}
			}
			else
			{
				// adding new word to list that has no possible matching anagram
				table[list[x]] = list[x].length();
			}
		}
	}

	return total;
}

int main() 
{
	cout << CountingAnagrams("cars are very cool so are arcs and my os") << endl; // 2
	cout << CountingAnagrams("aa aa odg dog gdo") << endl; // 2
	cout << CountingAnagrams("a c b c run urn urn") << endl; // 1
	cout << CountingAnagrams("mom omm mmo pop opp") << endl; // 3
	return 0;
}