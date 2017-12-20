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
one approach is to check if each of the connections are possible based on the nodes provided in the 3rd element
if the connection does not check, we would add it to our list of left out connection
*/

// method to check if the current pair of nodes check based on the specified nodes
bool checkConnections(char node1, char node2, string nodes)
{
	// loop to check if any of the provided nodes covers this specified connection
	for (int x = 0; x < nodes.length(); x++)
	{
		if (nodes[x] == node1 || nodes[x] == node2)
		{
			return true;
		}
	}

	return false;
}

string VertexCovering(string strArr[]) 
{
	string result;

	// getting the connections from the second element, we also remove any unnecessary characters
	string connections = strArr[1];
	connections.erase(remove(connections.begin(), connections.end(), ','), connections.end());
	connections.erase(remove(connections.begin(), connections.end(), ')'), connections.end());
	connections.erase(remove(connections.begin(), connections.end(), '('), connections.end());
	connections.erase(remove(connections.begin(), connections.end(), '-'), connections.end());

	// getting the nodes from the third element
	string nodes = strArr[2];
	nodes.erase(remove(nodes.begin(), nodes.end(), ','), nodes.end());
	nodes.erase(remove(nodes.begin(), nodes.end(), ')'), nodes.end());
	nodes.erase(remove(nodes.begin(), nodes.end(), '('), nodes.end());

	// loop to analyze each of the connections
	for (int x = 0; x < connections.length(); x += 2)
	{
		// if the current connection does not check than add it to our result of left out connections
		if (!checkConnections(connections[x], connections[x + 1], nodes))
		{
			if (result.empty())
			{
				result.push_back('(');
			}

			// adding our missing connection to our result
			result.push_back(connections[x]);
			result.push_back('-');
			result.push_back(connections[x + 1]);
			result.push_back(',');
		}
	}

	if (result.size() > 0)
	{
		result.pop_back(); // removing the extra comma
		result.push_back(')'); // adding closing tag

		return result;
	}
	else
	{
		return "yes";
	}
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