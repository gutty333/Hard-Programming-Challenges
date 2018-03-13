// This challenge will require knowledge of basic Boolean logic.
/*
have the function SimpleSAT(str) read str which will be a string consisting of letters, parenthesis, logical operators and tilde's representing a Boolean formula. For example: str may be "(a&b)|c" which means (a AND b) OR c. Your program should output the string yes if there is some arrangement of replacing the letters with TRUE or FALSE in such a way that the formula equates to TRUE. If there is no possible way of assigning TRUE or FALSE to the letters, then your program should output the string no. In the example above, your program would return yes because a=TRUE, b=TRUE and c=FALSE would make the formula TRUE. Another example: if str is "((a&c)&~a)" which means ((a AND c) AND NOT a) then your program should output no because it is not possible to assign TRUE or FALSE values to the letters to produce a TRUE output.

A Boolean formula will always have at most 5 letters, i.e. a, b, c, d and e. A tilde will never appear outside of a parenthesis, i.e. ~(a&b).
*/

#include <iostream>
#include <string>
using namespace std;


/*

*/
string SimpleSAT(string str) 
{


}

int main() 
{	
	cout << SimpleSAT("(a&b)|c") << endl; // yes
	cout << SimpleSAT("((a&c)&~a)") << endl; // no
	cout << SimpleSAT("(a&b&c)|~a") << endl; // yes
	cout << SimpleSAT("a&(b|c)&~b&~c") << endl; // no
	return 0;
}
