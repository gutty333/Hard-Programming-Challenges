// For this challenge you will determine whether a given set of vertices can cover all the edges in the graph.
/*
have the function VertexCovering(strArr) take strArr which will be an array of length three. The first part of the array will be a list of vertices in a graph in the form (A,B,C,...), the second part of the array will be the edges connecting the vertices in the form (A-B,C-D,...) where each edge is bidirectional. The last part of the array will be a set of vertices in the form (X,Y,Z,...) and your program will have to determine whether or not the set of vertices given covers every edge in the graph such that every edge is incident to at least one vertex in the set.

For example: if strArr is ["(A,B,C,D)","(A-B,A-D,B-D,A-C)","(A,B)"] then the vertices (A,B) are in fact one of the endpoints of every edge in the graph, so every edge has been accounted for. Therefore your program should return the string yes. But, if for example the last part of the array was (C,B) then these vertices don't cover all the edges because the edge connecting A-D is left out. If this is the case your program should return the edges given in the second part of the array that are left out in the same order they were listed, so for this example your program should return (A-D).

The graph will have at least 2 vertices and all the vertices in the graph will be connected. The third part of the array listing the vertices may be empty, where it would only contain the parenthesis with no values within it: "()"
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

/*
one approach is to check if each of the connection are possible based on the nodes provided in the 3rd element
if the connection does not check, we would add it to our list of left out connection
*/

// structure representing a node in our graph
struct node
{
	char name;
	vector <char> neighbors;
};


// method for creating our graph with the specified nodes
void createGraph(vector <node*>& graph, string values[])
{
	// removing unnecessary characters from the first element in order to extract the node values
	values[0].erase(remove(values[0].begin(), values[0].end(), ','), values[0].end());
	values[0].erase(remove(values[0].begin(), values[0].end(), ')'), values[0].end());
	values[0].erase(remove(values[0].begin(), values[0].end(), '('), values[0].end());

	cout << "this is now " << values[0] << endl;

	for (int x = 0; x < values[0].length(); x++)
	{
		graph.push_back(new node);

	}
}

string VertexCovering(string strArr[]) 
{

	vector <node*> graph;

	createGraph(graph, strArr);

	return "yes";
}

int main() 
{
	string A[] = { "(A,B,C,D)", "(A-B,A-D,B-D,A-C)", "(A,B)" };
	string B[] = { "(A,B,C,D)", "(A-B,A-D,B-D,A-C)", "(C)" };
	string C[] = { "(X,Y,Z,Q)", "(X-Y,Y-Q,Y-Z)", "(Z,Y,Q)" };

	cout << VertexCovering(A) << endl; // yes
	cout << VertexCovering(B) << endl; // (A-B,A-D,B-D)
	cout << VertexCovering(C) << endl; // yes

	return 0;
}