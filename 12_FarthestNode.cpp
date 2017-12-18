// For this challenge you will determine what nodes are farthest apart.
/*
have the function FarthestNodes(strArr) read strArr which will be an array of hyphenated letters representing paths between those two nodes. For example: ["a-b","b-c","b-d"] means that there is a path from node a to b (and b to a), b to c, and b to d. Your program should determine the longest path that exists in the graph and return the length of that path. So for the example above, your program should return 2 because of the paths a-b-c and d-b-c. The path a-b-c also means that there is a path c-b-a. No cycles will exist in the graph and every node will be connected to some other node in the graph.
*/

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
using namespace std;


// structure to represent each node in the graph
struct node
{
	char name;
	bool visited;
	vector <char> neighbors;
};


string FarthestNodes(string strArr[], int size) 
{

}

int main() 
{
	string A[] = { "a-b","b-c","b-d" };
	string B[] = { "b-e","b-c","c-d","a-b","e-f" };
	string C[] = { "b-a","c-e","b-c","d-c" };

	cout << FarthestNodes(A, sizeof(A)/sizeof(A[0])) << endl; // 2
	cout << FarthestNodes(B, sizeof(B) / sizeof(B[0])) << endl; // 4
	cout << FarthestNodes(C, sizeof(C) / sizeof(C[0])) << endl; // 3

	return 0;
}