// For this challenge you will be finding the maximum traffic that will enter a node.
/*
have the function CityTraffic(strArr) read strArr which will be a representation of an undirected graph in a form similar to an adjacency list. Each element in the input will contain an integer which will represent the population for that city, and then that will be followed by a comma separated list of its neighboring cities and their populations (these will be separated by a colon). For example: strArr may be
["1:[5]", "4:[5]", "3:[5]", "5:[1,4,3,2]", "2:[5,15,7]", "7:[2,8]", "8:[7,38]", "15:[2]", "38:[8]"]. This graph then looks like the following picture:

Each node represents the population of that city and each edge represents a road to that city. Your goal is to determine the maximum traffic that would occur via a single road if everyone decided to go to that city. For example: if every single person in all the cities decided to go to city 7, then via the upper road the number of people coming in would be (8 + 38) = 46. If all the cities beneath city 7 decided to go to it via the lower road, the number of people coming in would be (2 + 15 + 1 + 3 + 4 + 5) = 30. So the maximum traffic coming into the city 7 would be 46 because the maximum value of (30, 46) = 46.

Your program should determine the maximum traffic for every single city and return the answers in a comma separated string in the format: city:max_traffic,city:max_traffic,... The cities should be outputted in sorted order by the city number. For the above example, the output would therefore be: 1:82,2:53,3:80,4:79,5:70,7:46,8:38,15:68,38:45. The cities will all be unique positive integers and there will not be any cycles in the graph. There will always be at least 2 cities in the graph.

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

/*
Our first steps will be to set up the graph

One approach we can use is to check every city
Once we arrive at a current city we now check its neighbors, the number of neighbors determine the possible numbers of incoming traffic. Example if a city has 2 neighbors, than is there will be 2 incoming traffics into that city. 

We can perform a BFS from each neighbor start point and get a total of the population.
We store the population of each incoming traffic and record only the maximum possible traffic for that city. 
*/

// hash map to quickly index the vertices
map <int, int> nodeIndex;

// a structure representing each vertex
struct node
{
	int cost;
	bool visited;
};

// method to  create a connection between 2 nodes
void makePairs(vector <vector <node*> >& graph, int source, int partner)
{
	// making the edge connection
	graph[nodeIndex[source]].push_back(graph[nodeIndex[partner]][0]);
}

// method to create our graph
void createGraph(vector <vector <node*> >& graph, string arr[], int size)
{
	// traverse the string array to first extract the cost of each node
	for (int x = 0; x < size; x++)
	{
		// variable to collect the string number
		string num;

		for (int y = 0; y < arr[x].length(); y++)
		{
			// condition to get the cost of the current node
			if (arr[x][y] >= '0' && arr[x][y] <= '9')
			{
				num.push_back(arr[x][y]);
			}
			else
			{
				break;
			}
		}

		// converting from string to int
		int costValue;
		istringstream value(num);
		value >> costValue;

		// adding the key value pair to our table
		nodeIndex.insert(make_pair(costValue, x));

		// creating the node for our graph
		graph[x].push_back(new node);

		// setting its default values
		graph[x][0]->cost = costValue;
		graph[x][0]->visited = false;
	}
}

// method to set up the connections
void addConnections(vector <vector <node*> >& graph, string arr[], int size)
{
	for (int x = 0; x < size; x++)
	{
		string num;

		// loop to check nodes that connect to the current node
		int start = arr[x].find("[");
		for (int y = start+1; y < arr[x].length(); y++)
		{
			if (arr[x][y] >= '0' && arr[x][y] <= '9')
			{
				num.push_back(arr[x][y]);
			}
			else
			{
				// if current character does not represent a number than convert the string value we collected
				int valueCost;
				istringstream convert(num);
				convert >> valueCost;

				// here we call our make pair function to create the connection
				// we are connecting the current node to the current cost extracted
				makePairs(graph, graph[x][0]->cost, valueCost);

				// reset the string number variable
				num.clear();
			}
		}
	}
}

// each time we call this method it will reset the visit signal of each node back to false
void graphReset(vector <vector <node*> >& graph)
{
	for (int x = 0; x < graph.size(); x++)
	{
		graph[x][0]->visited = false;
	}
}

// applying BFS from the current source, as we traverse we add up the population
int bfsSum(vector < vector <node*> > graph, vector <node*> source)
{
	queue < vector <node*> > list;

	list.push(source);

	int total = 0; // keep track of the total cost from traversing from this source node

	while (!list.empty())
	{
		vector <node* > currentNode = list.front();
		currentNode[0]->visited = true;
		total += currentNode[0]->cost;
		list.pop();

		// checking the neighbors
		for (int x = 1; x < currentNode.size(); x++)
		{
			if (!currentNode[x]->visited)
			{
				// adding valid neighbors to our queue
				list.push(graph[nodeIndex[currentNode[x]->cost]]);
			}
		}
	}

	return total;
}

// sorts our 2d vector which stores the city and max traffic
// using a quick bubble sort to sort our list
void sortResult(vector< vector<int> >& list)
{
	bool swap;

	do
	{
		swap = false;

		for (int row = 0; row < list.size()-1; row++)
		{
			if (list[row][0] > list[row + 1][0])
			{
				int temp1 = list[row][0];
				int temp2 = list[row][1];

				list[row][0] = list[row + 1][0];
				list[row][1] = list[row + 1][1];

				list[row + 1][0] = temp1;
				list[row + 1][1] = temp2;

				swap = true;
			}
		}

	} while (swap);
}

string CityTraffic(string strArr[], int size)
{
	nodeIndex.clear(); // clearing our hash table

	// creating our graph and making the connection
	vector <vector <node*> > graph(size);
	createGraph(graph, strArr, size);
	addConnections(graph, strArr, size);

	string result = ""; // output the final result
	vector < vector<int> > resultOrder(size); // will store the integer values of city:max traffic

	/*
	we analyze each city here and check for all possible routes of incoming traffic
	we collect the total population of people coming in from each route
	in each calculation we are only keeping track of the highest incoming population
	*/
	for (int x = 0; x < graph.size(); x++)
	{
		// reseting our graph each time
		// this step is mandatory so that BFS checks all the valid neighbors
		graphReset(graph); 

		int high = 0; // we store the highest possible incoming traffic

		// we set the current city as visited
		graph[x][0]->visited = true;

		// we take the neighbors
		for (int y = 1; y < graph[x].size(); y++)
		{
			// calling our BFS sum it will return the total cost for this route
			int incomingTraffic = bfsSum(graph, graph[nodeIndex[graph[x][y]->cost]]);
			
			// updating our highest incoming traffic
			if ( incomingTraffic > high)
			{
				high = incomingTraffic;
			}
		}

		// storing our values in a list for sorting later
		resultOrder[x].push_back(graph[x][0]->cost);
		resultOrder[x].push_back(high);
	}

	// sorting our list
	sortResult(resultOrder);

	// loop to extract the integer values and convert back to a final string result
	for (int x = 0; x < resultOrder.size(); x++)
	{
		stringstream convert;
		convert << resultOrder[x][0];
		result += convert.str();

		result += ':';

		convert.str("");
		convert << resultOrder[x][1];
		result += convert.str();
		result += ',';
	}

	result.pop_back(); // removing the last character 
	return result;
}

int main() 
{
	string A[] = { "1:[5]", "4:[5]", "3:[5]", "5:[1,4,3,2]", "2:[5,15,7]", "7:[2,8]", "8:[7,38]", "15:[2]", "38:[8]" };
	string B[] = { "1:[5]", "2:[5]", "3:[5]", "4:[5]", "5:[1,2,3,4]" };
	string C[] = { "1:[5]", "2:[5,18]", "3:[5,12]", "4:[5]", "5:[1,2,3,4]", "18:[2]", "12:[3]" };

	cout << CityTraffic(A, sizeof(A)/sizeof(A[0])) << endl; // 1:82,2:53,3:80,4:79,5:70,7:46,8:38,15:68,38:45
	cout << CityTraffic(B, sizeof(B) / sizeof(B[0])) << endl; // 1:14,2:13,3:12,4:11,5:4
	cout << CityTraffic(C, sizeof(C) / sizeof(C[0])) << endl; // 1:44,2:25,3:30,4:41,5:20,12:33,18:27

	return 0;
}