// For this challenge you will determine what nodes are farthest apart.
/*
have the function FarthestNodes(strArr) read strArr which will be an array of hyphenated letters representing paths between those two nodes. For example: ["a-b","b-c","b-d"] means that there is a path from node a to b (and b to a), b to c, and b to d. Your program should determine the longest path that exists in the graph and return the length of that path. So for the example above, your program should return 2 because of the paths a-b-c and d-b-c. The path a-b-c also means that there is a path c-b-a. No cycles will exist in the graph and every node will be connected to some other node in the graph.
*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

/*
one approach is to treat each node as a possible starting point from where we can expand and perform BFS
at each step of our BFS we update the cost of each node
this cost determines the length from the current starting node
we repeat this process for all the nodes in our graph and keep track of the highest length
*/

map <char, int> hashTable;

// structure to represent each node in the graph
struct node
{
	int cost;
	char name;
	bool visited;
	vector <char> neighbors;
};

// method to create the nodes in our graph
void createGraph(vector <node*>& graph, string values[], int size)
{
	int index = 0;

	for (int x = 0; x < size; x++)
	{
		char node1 = values[x][0];
		char node2 = values[x][2];

		// check if the current node is already in our hash table
		// this determines if we need to add it to our graph
		// for the first iteration we add the first 2 letters analyzed
		if (x == 0)
		{
			hashTable[node1] = index;

			// making the node
			graph.push_back(new node);
			graph[index]->cost = 0;
			graph[index]->visited = false;
			graph[index]->name = node1;
			index++;

			hashTable[node2] = index;
			graph.push_back(new node);
			graph[index]->cost = 0;
			graph[index]->visited = false;
			graph[index]->name = node2;
			index++;
		}
		else
		{
			if (hashTable.count(node1) <= 0)
			{
				hashTable[node1] = index;
				graph.push_back(new node);
				graph[index]->cost = 0;
				graph[index]->visited = false;
				graph[index]->name = node1;
				index++;
			}

			if (hashTable.count(node2) <= 0)
			{
				hashTable[node2] = index;
				graph.push_back(new node);
				graph[index]->cost = 0;
				graph[index]->visited = false;
				graph[index]->name = node2;
				index++;
			}
		}
	}
}

// method to create the pair connections
void makeConnections(vector <node*> graph, string values[], int size)
{
	for (int x = 0; x < size; x++)
	{
		char node1 = values[x][0];
		char node2 = values[x][2];

		// making the bidirectional edge connection between the 2 nodes
		graph[hashTable[node1]]->neighbors.push_back(node2);
		graph[hashTable[node2]]->neighbors.push_back(node1);
	}
}

// method to reset our graph to default values
void resetGraph(vector <node*> graph)
{
	for (int x = 0; x < graph.size(); x++)
	{
		graph[x]->cost = 0;
		graph[x]->visited = false;
	}
}

// method that return the farthest node from the specified source node
int getFarthest(node* source, vector <node*> graph)
{
	// in this method we are applying a simple BFS from the source
	queue <node*> list;
	list.push(source);

	// keep track of farthest length
	int length = 0;

	while (!list.empty())
	{
		node* current = list.front();
		list.pop();

		current->visited = true;

		// check the neighbors of current node
		for (int x = 0; x < current->neighbors.size(); x++)
		{
			int index = hashTable[current->neighbors[x]];

			// only analyze unvisited neighbors
			if (graph[index]->visited == false)
			{
				// update its cost and compare it to the length
				int newLength = current->cost + 1;
				graph[index]->cost = newLength;

				if (newLength > length)
				{
					length = newLength;
				}

				// adding to our queue
				list.push(graph[index]);
			}
		}
	}

	return length;
}

int FarthestNodes(string strArr[], int size) 
{
	int length = 0;

	// setting up our graph
	vector <node*> graph;
	createGraph(graph, strArr, size);

	// making the connections
	makeConnections(graph, strArr, size);

	// in this operation we perform a BFS from every node in our graph
	for (int x = 0; x < graph.size(); x++)
	{
		int currentLength = getFarthest(graph[x], graph);

		if (currentLength > length)
		{
			length = currentLength;
		}

		// resetting our graph;
		resetGraph(graph);
	}

	hashTable.clear();
	
	return length;
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