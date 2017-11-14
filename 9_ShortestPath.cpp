// For this challenge you will have to determine the shortest path from one node to an end node.

/*
have the function ShortestPath(strArr) take strArr which will be an array of strings which models a non-looping Graph. The structure of the array will be as follows: The first element in the array will be the number of nodes N (points) in the array as a string. The next N elements will be the nodes which can be anything (A, B, C .. Brick Street, Main Street .. etc.). Then after the Nth element, the rest of the elements in the array will be the connections between all of the nodes. They will look like this: (A-B, B-C .. Brick Street-Main Street .. etc.). Although, there may exist no connections at all.

An example of strArr may be: ["4","A","B","C","D","A-B","B-D","B-C","C-D"]. Your program should return the shortest path from the first Node to the last Node in the array separated by dashes. So in the example above the output should be A-B-D. Here is another example with strArr being ["7","A","B","C","D","E","F","G","A-B","A-E","B-C","C-D","D-F","E-D","F-G"]. The output for this array should be A-E-D-F-G. There will only ever be one shortest path for the array. If no path between the first and last node exists, return -1. The array will at minimum have two nodes. Also, the connection A-B for example, means that A can get to B and B can get to A.
*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

// hash table to quickly access the nodes
map <string, int> nodeIndex;

const string unknown = "unknown";

/*
First we need to represent the input as a graph
the graph will be represented as an adjacency list
set up as a 2d vector storing structures that represent the nodes

the nodes will store a distance cost also a parent node
the parents will be used to determine in the end the path we took
*/
struct vertex
{
	string name;
	int cost;
	string parent;
	bool visited;
};

// method to set up the vertices for our graph
void createNodes(vector < vector <vertex* > >& graph, vector <string> nodes)
{
	// resetting the hash table for each call before we add values to it
	nodeIndex.clear();

	for (int x = 0; x < nodes.size(); x++)
	{
		// adding key value pair to our table
		nodeIndex.insert(make_pair(nodes[x], x));

		// creating the vertices for our graph
		graph[x].push_back(new vertex);

		// initializing values to default
		graph[x][0]->cost = 100*100; // basically all are set to infinity/large value since we don't know distance yet
		graph[x][0]->name = nodes[x];
		graph[x][0]->parent = unknown;
		graph[x][0]->visited = false;
	}
}

// method to make the edge connection in our graph
void makePair(vector < vector <vertex* > >& graph, string pair)
{
	// getting the nodes we are connecting
	string source, partner;
	int breakpoint = pair.find('-');
	source = pair.substr(0, breakpoint);
	partner = pair.substr(breakpoint + 1);

	/*
	make the undirected connection
	we utilized a hash to quickly target the list of the nodes we are working with
	since this is a bi-directional connection,if the first node connects to the third node
	then the third node must also connect to the first node
	*/
	graph[nodeIndex[source]].push_back(graph[nodeIndex[partner]][0]);
	graph[nodeIndex[partner]].push_back(graph[nodeIndex[source]][0]);
}

string ShortestPath(string strArr[], int size)
{
	string source, destination;

	// total number of nodes in our graph
	int totalNodes;
	istringstream value(strArr[0]);
	value >> totalNodes;

	// getting the name of each node
	vector <string> nodes;
	for (int x = 1; x <= totalNodes; x++)
	{
		// condition to get the names of our starting node and our destination
		if (x == 1)
		{
			source = strArr[x];
		}
		else if (x == totalNodes)
		{
			destination = strArr[x];
		}

		nodes.push_back(strArr[x]);
	}

	// setting up our nodes in the graph
	vector < vector <vertex*> > graph(totalNodes);
	createNodes(graph, nodes);

	// making the edge connection based on the pair inputs
	for (int x = totalNodes + 1; x < size; x++)
	{
		string currentPair = strArr[x];

		makePair(graph, currentPair);
	}

	/*
	Now we will perform a BFS to our graph
	when we find an optimal path to our neighboring node we need to update their cost and their parent
	we will utilize a queue and to commence we add our source node
	we check the neighbors and update their stats, we will continue the BFS until the queue is empty meaning all possible connections have been checked
	In the end if the parent of the destination node is unknown than we can conclude that no path was found from the source
	else if a parent is located we can backtrack from the destination and collect the parent nodes which showcases the shortest path we took
	*/
	queue < vector < vertex* > > list;
	// starting node will have a cost of 0
	graph[0][0]->cost = 0;
	list.push(graph[0]);

	// BFS
	while (!list.empty())
	{
		vector <vertex*> current = list.front();
		current[0]->visited = true; // update the current node
		list.pop();

		// now we check all of it's unvisited neighbors and update their stats
		for (int x = 1; x < current.size(); x++)
		{
			if (!current[x]->visited)
			{
				/*
				here we check for optimal paths
				if the neighbors can be reached sooner from this current node than update the cost of our neighbor
				also update their parent
				*/
				if (current[0]->cost + 1 < current[x]->cost)
				{
					current[x]->cost = current[0]->cost + 1;
					current[x]->parent = current[0]->name;
				}

				// adding the valid neighbors to the queue
				list.push(graph[nodeIndex[current[x]->name]]);
			}
		}
	}

	// condition to check if a path was found
	if (graph[nodeIndex[destination]][0]->parent == unknown)
	{
		return "-1";
	}
	else
	{
		stack <string> result;

		vertex* current = graph[nodeIndex[destination]][0];
		result.push(current->name); // initially add the destination to our result

		// tracing back
		while (current->parent != unknown)
		{
			// adding parent of current node to our path
			string parent = current->parent;
			result.push("-");
			result.push(parent);

			// updating our current node
			current = graph[nodeIndex[parent]][0];
		}

		// getting the elements from our stack to showcase the result
		string output = "";

		while (!result.empty())
		{
			output+=result.top();
			result.pop();
		}

		return output;
	}
}

int main() 
{
	string A[] = { "4", "A", "B", "C", "D", "A-B", "B-D", "B-C", "C-D" };
	string B[] = { "7", "A", "B", "C", "D", "E", "F", "G", "A-B", "A-E", "B-C", "C-D", "D-F", "E-D", "F-G" };
	string C[] = { "5", "A", "B", "C", "D", "F", "A-B", "A-C", "B-C", "C-D", "D-F" };
	string D[] = { "4", "X", "Y", "Z", "W", "X-Y", "Y-Z", "X-W" };
	string E[] = { "7", "C", "B", "A", "D", "E", "G", "F", "A-B", "B-E", "E-G", "C-D", "D-B", "D-E", "E-F" };
	string F[] = { "9", "Z", "B", "C", "D", "R", "A", "Y", "Q", "E", "A-Z", "A-R", "Z-Y", "Z-C", "C-B", "Y-Q", "Q-D", "D-E", "R-E" };
	string G[] = { "5", "N1", "N2", "N3", "N4", "N5", "N1-N3", "N3-N4", "N4-N5", "N5-N2", "N2-N1" };

	cout << ShortestPath(A, sizeof (A)/sizeof(A[0])) << endl; // A-B-D
	cout << ShortestPath(B, sizeof(B) / sizeof(B[0])) << endl; // A-E-D-F-G
	cout << ShortestPath(C, sizeof(C) / sizeof(C[0])) << endl; // A-C-D-F
	cout << ShortestPath(D, sizeof(D) / sizeof(D[0])) << endl; // X-W
	cout << ShortestPath(E, sizeof(E) / sizeof(E[0])) << endl; // C-D-E-F
	cout << ShortestPath(F, sizeof(F) / sizeof(F[0])) << endl; // Z-A-R-E
	cout << ShortestPath(G, sizeof(G) / sizeof(G[0])) << endl; // N1-N2-N5
	
	return 0;
}