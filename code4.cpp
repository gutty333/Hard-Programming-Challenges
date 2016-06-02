// For this challenge you will be evaluating a mathematical expression within a string.
/*
have the function Calculator(str) take the str parameter being passed and evaluate the mathematical expression within in. For example, if str were "2+(3-1)*3" the output should be 8. Another example: if str were "(2-0)(6/2)" the output should be 6. There can be parenthesis within the string so you must evaluate it properly according to the rules of arithmetic. The string will contain the operators: +, -, /, *, (, and ). If you have a string like this: #/#*# or #+#(#)/#, then evaluate from left to right. So divide then multiply, and for the second one multiply, divide, then add. The evaluations will be such that there will not be any decimal operations, so you do not need to account for rounding and whatnot.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Operation function that performs the specified calculation depending on the operator
int operation(int x, int y, char symbol)
{
	if (symbol == '+')
	{
		return x + y;
	}
	else if (symbol == '-')
	{
		return x - y;
	}
	else if (symbol == '/')
	{
		return x / y;
	}
	else if (symbol == '*')
	{
		return x * y;
	}
	else
		return -1;
}

string Calculator(string str) {
	int index, start, end;
	start = end = 0;
	char symbol;
	vector <int> list; 
	bool analyzed, analyzed2;
	string num;
	int number;

	// Creating a list of int numbers that will be parallel to the string argument
	// This will aid with the calculations
	// Example numList = 2,-1,3 would be stringArg = "2+3"
	for (int x = 0; x <= str.length(); x++)
	{
		if (str[x] >= '0' && str[x] <= '9')
		{
			num += str[x];
		}
		else
		{
			// inserting a misc value if the character is a symbol/non digit
			if (num.empty())
			{
				list.push_back(-1);
			}
			else
			{
				// If is the digit is multiple ex.23,100,etc manipulate the string to stay parallel to the number list
				if (num.length() > 1)
				{
					str.erase(x - num.length(), num.length() - 1);
					x -= num.length() - 1;
				}
				// Converting to an int to include to the number list
				istringstream(num) >> number;
				list.push_back(number);
				if (x < str.length()-1)
				{
					list.push_back(-1);
				}
				num.clear();
			}
		}
	}

	do
	{
		index = 0;
		for (index; index < str.length(); index++)
		{
			analyzed = false;
			analyzed2 = false;
			// Find the start of any parenthesis
			if (str[index] == '(')
			{
				start = index + 1;
			}
			// Find the end of any parenthesis
			if (str[index] == ')')
			{
				end = index;
			}
			// Analyze the inside content when both parenthesis have been found
			// Once the content has been analyzed search for any other parenthesis
			if (start && end)
			{
				for (start; start < end && !analyzed && !analyzed2; start++)
				{
					// In the case of calculating multiple operations ex. (2+3*4+4)
					if (end - start > 3)
					{
						number = start;
						while (start < end) // Multiply or Divide
						{
							if (str[start] == '*' || str[start] == '/')
							{
								symbol = str[start];
								list[start - 1] = operation(list[start - 1], list[start + 1], symbol);
								list.erase(list.begin() + start, list.begin() + (start + 2));
								str.erase(str.begin() + start, str.begin() + (start + 2));
								end -= 2;
							}
							else
								start++;
						}
						// Reset back to the start of the parenthesis to now check for adding or subtracting
						start = number;
						while (start < end) //  Add or Subtract
						{
							if (str[start] == '-' || str[start] == '+')
							{
								symbol = str[start];
								list[start - 1] = operation(list[start - 1], list[start + 1], symbol);
								list.erase(list.begin() + start, list.begin() + (start + 2));
								str.erase(str.begin() + start, str.begin() + (start + 2));
							}
							else
								start++;
						}
						analyzed2 = true;
						start = number;
					}
					else if (str[start] == '*' || str[start] == '/')
					{
						symbol = str[start];
						// perform the calculation inside the parenthesis
						list[start - 2] = operation(list[start - 1], list[start + 1], symbol);
						str[start - 2] = 'x';
						// remove parenthesis and values involved in the operation
						list.erase(list.begin() + start - 1, list.begin() + (start + 3));
						str.erase(str.begin() + start - 1, str.begin() + (start + 3));
						index -= 4;
						// signal that the parenthesis has been analyzed
						analyzed = true;
					}
					else if (str[start] == '-' || str[start] == '+')
					{
						symbol = str[start];
						list[start - 2] = operation(list[start - 1], list[start + 1], symbol);
						str[start - 2] = 'x';
						list.erase(list.begin() + start - 1, list.begin() + (start + 3));
						str.erase(str.begin() + start - 1, str.begin() + (start + 3));
						index -= 4;
						analyzed = true;
					}
				}

				// In the case that there were no operations to perform inside
				// Remove parenthesis
				if (analyzed2)
				{
					list[start - 2] = list[start - 1];
					str[start - 2] = 'x';
					list.erase(list.begin() + start - 1, list.begin() + (start + 1));
					str.erase(str.begin() + start - 1, str.begin() + (start + 1));
				}
				else if (!analyzed)
				{
					list[end - 2] = list[end - 1];
					str[end - 2] = 'x';
					list.erase(list.begin() + start - 1, list.begin() + (start + 1));
					str.erase(str.begin() + start - 1, str.begin() + (start + 1));
				}
				start = end = 0; // Reset back in case there are multiple parenthesis
			}
		}

		index = 0;
		// Solve for any multiplication or division operations after no parenthesis
		while (index < str.length())
		{
			if (str[index] == '*' || str[index] == '/')
			{
				symbol = str[index];
				// calculate the operation
				list[index - 1] = operation(list[index - 1], list[index + 1], symbol); 
				// remove the values involved in the operation
				list.erase(list.begin() + index, list.begin() + (index + 2)); 
				str.erase(str.begin() + index, str.begin() + (index + 2));
			}
			// Calculating when there are neighbor parenthesis ex. (2)(3) = 6
			else if ((str[index] >= '0' && str[index] <= '9' && str[index + 1] == 'x') || (str[index] == 'x' && str[index+1] == 'x'))
			{
				symbol = '*';
				list[index+1] = operation(list[index], list[index + 1], symbol);
				list.erase(list.begin() + index, list.begin() + index + 1);
				str.erase(str.begin() + index, str.begin() + index + 1);
			}
			else
				index++;
		}

		index = 0;
		// Solve for any adding or subtracting operations after no parenthesis
		while (index < str.length())
		{
			if (str[index] == '-' || str[index] == '+') 
			{
				symbol = str[index];
				list[index - 1] = operation(list[index - 1], list[index + 1], symbol);
				list.erase(list.begin() + index, list.begin() + (index + 2));
				str.erase(str.begin() + index, str.begin() + (index + 2));
			}
			else
				index++;
		}
	} while (str.length() > 1);
	
	// Converting the number value to a string
	stringstream convert;
	convert << list[0];
	str = convert.str();
	return str;
}

int main() {
	// keep this function call here
	cout << Calculator("6*(4/2)+3*1") << endl; // 15
	cout << Calculator("2+(3-1)*3") << endl; // 8
	cout << Calculator("(2)+4*2") << endl; // 10
	cout << Calculator("(2-0)(6/2)") << endl; // 6
	cout << Calculator("6/3-1") << endl; // 1
	cout << Calculator("2+4+5") << endl; // 11
	cout << Calculator("3+5*2*2") << endl; // 23
	cout << Calculator("2+7*2+2") << endl; // 18
	cout << Calculator("1+4*2+3*1") << endl; // 12
	cout << Calculator("45-10*2-1") << endl; // 24
	cout << Calculator("100*2") << endl; // 200
	cout << Calculator("7-2+(5-2)") << endl; // 8
	cout << Calculator("812/2*(5-3)") << endl; // 812
	cout << Calculator("7-4-1+8(3)/2") << endl; // 14
	cout << Calculator("(5-2*0-9*0)*0") << endl; // 0
	cout << Calculator("8-7*(12+100/2)*9-2") << endl; // -3900
	return 0;
}
