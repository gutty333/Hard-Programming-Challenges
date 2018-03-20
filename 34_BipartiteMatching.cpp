// For this challenge you will be finding the maximum cardinality matching of a bipartite graph. 
/*
have the function BipartiteMatching(strArr) read strArr which will be an array of hyphenated letters representing paths from the first node to the second node. For example: ["a->d", "a->e", "b->f", "c->e"] means that there is a path from node a to d, a to e, b to f, and so on. The graph will be bipartite meaning that it is possible to separate the nodes into two disjoint sets such that every edge only connects a node from the lefthand side to a node on the righthand side. Your program should determine the maximum cardinality matching of the bipartite graph, which means finding the largest possible number of non-adjacent edges that are matching. So for the example above, your program should return 3 because it is possible to connect every single node on the left to a node on the right.

The input will only contain lowercase alphabetic characters with a -> between them signifying an edge between them going from the left node to the right node. The input will contain at least 1 edge connecting 2 nodes.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
using namespace std;


/*
first traverse the string array to store the vertices
at each iteration we can insert the right hand vertex into a hash table
if the key/right hand vertex is repeated we ignore the current connection
we update our count only when right hand vextex is not part of the connections we have gathered
also when left hand vertex does not repeat
we will apply this greedy approach to both scenarios of start to end 
and end to start
*/
int BipartiteMatching(string strArr[], int size) 
{
	map <char, char> table;
	int total = 0;
	int total2 = 0;

	// traverse the input array
	// greedy approach from start to end
	for (int x = 0; x < size; x++)
	{
		// analyzing the current connection
		string current = strArr[x];

		// extracting the node values
		char leftNode = current[0];
		char rightNode = current[3];

		// condition to check if edge connection is unique
		if (table.count(rightNode) == 0)
		{
			bool repeat = false;

			// check that left hand vertex does not repeat
			for (map<char, char>::iterator y = table.begin(); y != table.end(); y++)
			{
				if (y->second == leftNode)
				{
					repeat = true;
					break;
				}
			}

			// updates our total if current edge connection is valid
			if (!repeat)
			{
				table[rightNode] = leftNode;
				total++;
			}
		}
	}

	// reseting our table
	table.clear();

	// greedy approach from end to start
	for (int x = size-1; x >= 0; x--)
	{
		// analyzing the current connection
		string current = strArr[x];

		// extracting the node values
		char leftNode = current[0];
		char rightNode = current[3];

		// condition to check if edge connection is unique
		if (table.count(rightNode) == 0)
		{
			bool repeat = false;

			// check that left hand vertex does not repeat
			for (map<char, char>::iterator y = table.begin(); y != table.end(); y++)
			{
				if (y->second == leftNode)
				{
					repeat = true;
					break;
				}
			}

			if (!repeat)
			{
				table[rightNode] = leftNode;
				total2++;
			}
		}
	}
	
	// getting the result
	if (total > total2)
	{
		return total;
	}
	return total2;
}

int main() 
{
	string A[] = { "a->d", "a->e", "b->f", "c->e" };
	string B[] = { "a->w", "a->x", "b->x", "b->y", "c->x", "c->z", "d->w" };
	string C[] = { "a->b", "c->b", "c->d", "e->b" };
	string D[] = { "a->w", "a->x", "b->y", "c->y", "d->z", "d->r", "e->z", "f->y" };

	cout << BipartiteMatching(A, sizeof(A)/sizeof(A[0])) << endl; // 3
	cout << BipartiteMatching(B, sizeof(B) / sizeof(B[0])) << endl; // 4
	cout << BipartiteMatching(C, sizeof(C) / sizeof(C[0])) << endl; // 2
	cout << BipartiteMatching(D, sizeof(D) / sizeof(D[0])) << endl; // 4
	return 0;
}