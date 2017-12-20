// For this challenge you will determine whether a given set of vertices form a Hamiltonian path on the graph.
/*
have the function HamiltonianPath(strArr) take strArr which will be an array of length three. The first part of the array will be a list of vertices in a graph in the form (A,B,C,...), the second part of the array will be the edges connecting the vertices in the form (A-B,C-D,...) where each edge is bidirectional. The last part of the array will be a set of vertices in the form (X,Y,Z,...) and your program will have to determine whether or not the set of vertices given forms a Hamiltonian path on the graph which means that every vertex in the graph is visited only once in the order given.

For example: if strArr is ["(A,B,C,D)","(A-B,A-D,B-D,A-C)","(C,A,D,B)"] then the vertices (C,A,D,B) in this order do in fact form a Hamiltonian path on the graph so your program should return the string yes. If for example the last part of the array was (D,A,B,C) then this doesn't form a Hamiltonian path because once you get to B you can't get to C in the graph without passing through the visited vertices again. Here your program should return the vertex where the path had to terminate, in this case your program should return B.

The graph will have at least 2 vertices and all the vertices in the graph will be connected.
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

/*
we first we create a graph representation for the nodes and their respective connections
to solve the problem we can use element 3 as our foundation
the first value will represent our source node
from their we can check if the next value is part of its neighbor
if true we update our current node and update it's visit flag
we repeat this until all nodes from element 3 have been analyzed
if a current node does not have a neighbor that matches the target we can signal the node where we terminate
*/

map <char, int> hashTable;

// structure representing a node in our graph
struct node
{
	char name;
	bool visit;
	vector <char> neighbors;
};

// method to create our graph
void createGraph(vector <node*>& graph, string values[])
{
	// removing unneeded characters from the first element to extract the node values
	values[0].erase(remove(values[0].begin(), values[0].end(), ','), values[0].end());
	values[0].erase(remove(values[0].begin(), values[0].end(), ')'), values[0].end());
	values[0].erase(remove(values[0].begin(), values[0].end(), '('), values[0].end());

	for (int x = 0; x < values[0].length(); x++)
	{
		graph.push_back(new node);
		graph[x]->name = values[0][x];
		graph[x]->visit = false;

		hashTable[values[0][x]] = x;
	}
}

// method for making the connections
void makeConnections(vector <node*> graph, string values[])
{
	// removing unneeded characters from the second element
	values[1].erase(remove(values[1].begin(), values[1].end(), ','), values[1].end());
	values[1].erase(remove(values[1].begin(), values[1].end(), ')'), values[1].end());
	values[1].erase(remove(values[1].begin(), values[1].end(), '('), values[1].end());
	values[1].erase(remove(values[1].begin(), values[1].end(), '-'), values[1].end());

	for (int x = 0; x < values[1].length(); x+=2)
	{
		char node1 = values[1][x];
		char node2 = values[1][x + 1];

		// making the bidirectional connections
		graph[hashTable[node1]]->neighbors.push_back(node2);
		graph[hashTable[node2]]->neighbors.push_back(node1);
	}
}

// method to check if the path is valid, we take 2 nodes and check if based on our graph a connection is possible
bool checkPath(char node1, char node2, vector<node*>& graph)
{
	node* current = graph[hashTable[node1]];

	// loop to check if any of the unvisited neighbors are the target node (node2)
	for (int x = 0; x < current->neighbors.size(); x++)
	{
		node* temp = graph[hashTable[current->neighbors[x]]];

		if (temp->visit == false && temp->name == node2)
		{
			temp->visit = true;
			return true;
		}
	}
	return false;
}

string HamiltonianPath(string strArr[]) 
{
	// setting up our graph
	vector <node*> graph;
	createGraph(graph, strArr);
	makeConnections(graph, strArr);

	// getting the 3rd element which determines the order of our path
	string path = strArr[2];
	path.erase(remove(path.begin(), path.end(), ','), path.end());
	path.erase(remove(path.begin(), path.end(), ')'), path.end());
	path.erase(remove(path.begin(), path.end(), '('), path.end());

	for (int x = 0; x < path.length() - 1; x++)
	{
		// condition that checks if the path is valid
		// recall we take 2 nodes and check if there is a connection between them
		if (!checkPath(path[x], path[x + 1], graph))
		{
			// when not valid we return the node at which it terminates
			string result;
			result.push_back(path[x]);
			hashTable.clear();
			return result;
		}
	}

	hashTable.clear();
	return "yes";
}

int main() 
{
	string A[] = { "(A,B,C,D)", "(A-B,A-D,B-D,A-C)", "(C,A,D,B)" };
	string B[] = { "(A,B,C)", "(B-A,C-B)", "(C,B,A)" };
	string C[] = { "(X,Y,Z,Q)", "(X-Y,Y-Q,Y-Z)", "(Z,Y,Q,X)" };

	cout << HamiltonianPath(A) << endl; // yes
	cout << HamiltonianPath(B) << endl; // yes
	cout << HamiltonianPath(C) << endl; // Q
	return 0;
}