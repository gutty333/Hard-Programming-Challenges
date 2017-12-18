// For this challenge you will have to determine the shortest weighted path from one node to an end node.
/*
have the function WeightedPath(strArr) take strArr which will be an array of strings which models a non-looping weighted Graph. The structure of the array will be as follows: The first element in the array will be the number of nodes N (points) in the array as a string. The next N elements will be the nodes which can be anything (A, B, C .. Brick Street, Main Street .. etc.). Then after the Nth element, the rest of the elements in the array will be the connections between all of the nodes along with their weights (integers) separated by the pipe symbol (|). They will look like this: (A|B|3, B|C|12 .. Brick Street|Main Street|14 .. etc.). Although, there may exist no connections at all.

An example of strArr may be: ["4","A","B","C","D","A|B|1","B|D|9","B|C|3","C|D|4"]. Your program should return the shortest path when the weights are added up from node to node from the first Node to the last Node in the array separated by dashes. So in the example above the output should be A-B-C-D. Here is another example with strArr being ["7","A","B","C","D","E","F","G","A|B|1","A|E|9","B|C|2","C|D|1","D|F|2","E|D|6","F|G|2"]. The output for this array should be A-B-C-D-F-G. There will only ever be one shortest path for the array. If no path between the first and last node exists, return -1. The array will at minimum have two nodes. Also, the connection A-B for example, means that A can get to B and B can get to A. A path may not go through any Node more than once.
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

/*
For this problem we can utilize the concept of single source shortest path by implementing Dijkstra's algorithm
Reusing BFS as a base, we now need to perform an edge relaxation on the most optimal path for each node
When an optimal path is found we have to update its cost and its parent

Before starting each node will have a cost of infinity and for each iteration of BFS we are checking if the current path is a better choice than the previous path found for this node. 
*/

// global variables
const string defaultParent = "unknown";
const int defaultCost = 1000 * 100;

map <string, int> hashTable; // hash table to quickly reference the nodes

// structure representing a weighted connection in our graph
struct edgeConnection
{
	string neighbor;
	int edgeWeight;
};

// structure representing a node in our graph
struct node
{
	string name;
	int cost;
	string parent;
	vector <edgeConnection> connections;
};


// method to create our nodes for our graph
void createGraph(vector <node*>& graph, string nodeValues[], int size)
{
	for (int x = 1; x <= size; x++)
	{
		// creating the nodes
		graph.push_back(new node);
		graph[x - 1]->name = nodeValues[x];
		graph[x - 1]->cost = defaultCost;
		graph[x - 1]->parent = defaultParent;

		// adding to our hash table
		hashTable[nodeValues[x]] = x - 1;
	}
}

// method to make the connections
void makeConnections(vector <node*>& graph, string neighbors[], int index, int size)
{
	for (int x = index; x < size; x++)
	{
		// extracting the contents from the string
		// we take the 2 nodes that are connecting and the edge weight value
		int breakpoint = neighbors[x].find('|');
		string node1 = neighbors[x].substr(0, breakpoint);
		int breakpoint2 = neighbors[x].find('|', breakpoint + 1);
		string node2 = neighbors[x].substr(breakpoint + 1, breakpoint2 - (breakpoint + 1));

		// getting the edge value
		string value = neighbors[x].substr(breakpoint2 + 1);
		stringstream convert(value);
		int edge;
		convert >> edge;

		// adding the neighbors to the corresponding nodes
		int pair1 = hashTable[node1];
		int pair2 = hashTable[node2];

		edgeConnection temp1;
		temp1.neighbor = node2;
		temp1.edgeWeight = edge;

		edgeConnection temp2;
		temp2.neighbor = node1;
		temp2.edgeWeight = edge;

		graph[pair1]->connections.push_back(temp1);
		graph[pair2]->connections.push_back(temp2);
	}
}


string WeightedPath(string strArr[], int size)
{
	// getting the total number of nodes for our graph
	int nodeSize;
	istringstream value(strArr[0]);
	value >> nodeSize;

	// creating our graph with default values
	vector <node*> graph;
	createGraph(graph, strArr, nodeSize);

	// making the edge connections
	makeConnections(graph, strArr, nodeSize + 1, size);


	string source = graph[0]->name;
	string destination = graph[graph.size() - 1]->name;

	// doing our operations for the single source shortest path
	// first we set up a queue and insert the source node
	// note the cost of our source is set to zero
	queue <node*> list;
	graph[0]->cost = 0;
	list.push(graph[0]);

	while (!list.empty())
	{
		// get current node from our queue to analyze
		node* current = list.front();
		list.pop();

		// loop to check the neighbors of the current node
		if (current->name != destination)
		{
			for (int x = 0; x < current->connections.size(); x++)
			{
				int index = hashTable[current->connections[x].neighbor];
				int edgecost = current->connections[x].edgeWeight;

				if (graph[index]->name != current->parent)
				{
					// condition to check if the current path is more optimal than the last
					// if true we perform edge relaxation and update its parent
					if (current->cost + edgecost < graph[index]->cost)
					{
						// here we update its cost and parent
						graph[index]->cost = current->cost + edgecost;
						graph[index]->parent = current->name;


						// adding to our queue
						list.push(graph[index]);
					}
				}
			}
		}
	}

	// condition to check if we were able to reach the destination
	if (graph[hashTable[destination]]->parent == defaultParent)
	{
		return "-1";
	}
	else
	{
		// collecting our shortest path
		string result;

		node* current = graph[hashTable[destination]];

		// we start at the destination and collect the parents in each iteration
		while (current)
		{
			result += current->name;
			result += '-';

			if (current->parent == defaultParent)
			{
				result.pop_back();
				reverse(result.begin(), result.end());
				return result;
			}
			else
			{
				current = graph[hashTable[current->parent]];
			}
		}
	}
}

int main() 
{
	string A[] = { "4", "A", "B", "C", "D", "A|B|1", "B|D|9", "B|C|3", "C|D|4" };
	string B[] = { "7", "A", "B", "C", "D", "E", "F", "G", "A|B|1", "A|E|9", "B|C|2", "C|D|1", "D|F|2", "E|D|6", "F|G|2" };
	string C[] = { "4", "A", "B", "C", "D", "A|B|2", "C|B|11", "C|D|3", "B|D|2" };
	string D[] = { "4", "x", "y", "z", "w", "x|y|2", "y|z|14", "z|y|31" };

	cout << WeightedPath(A, sizeof(A) / sizeof(A[0])) << endl; // A-B-C-D
	cout << WeightedPath(B, sizeof(B) / sizeof(B[0])) << endl; // A-B-C-D-F-G
	cout << WeightedPath(C, sizeof(C) / sizeof(C[0])) << endl; // A-B-D
	cout << WeightedPath(D, sizeof(D) / sizeof(D[0])) << endl; // -1
	return 0;
}