#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

const string shared = "Shared";
const string confidential = "Confidential";


// structure used to represent each folder
struct folder
{
	int folderId;
	int cowCount;
	string type;
	vector <int> cowIds;

	folder* left;
	folder* right;
	folder* parent;
};

// method to add folders/nodes to our table
// the hash table will later allow us to quickly access any of the folders
void addFolder(map<int, folder*>& graph, int ID, int cowCount, string type, vector <int> cowIds)
{
	// creating the folder and adding its content
	folder* newFolder = new folder;
	newFolder->folderId = ID;
	newFolder->cowCount = cowCount;
	newFolder->type = type;
	newFolder->cowIds = cowIds;

	newFolder->left = NULL;
	newFolder->right = NULL;
	newFolder->parent = NULL;

	// adding the folder to our graph
	graph[ID] = newFolder;
}


// method to create the relationship between the folders (parent/child relation)
void makePair(map<int, folder*> graph, int parent, int child)
{
	// get the current parent and children;
	folder* currentParent = graph[parent];
	folder* currentChild = graph[child];

	// creating the child connection, first we locate a possible space
	if (currentParent->left == NULL && currentParent->right ==  NULL)
	{
		currentParent->left = currentChild;
	}
	else if (currentParent->left == NULL)
	{
		currentParent->left = currentChild;
	}
	else if (currentParent->right == NULL)
	{
		currentParent->right = currentChild;
	}

	// creating the parent connection
	currentChild->parent = currentParent;
}


// method to locate the root of the hierarchy
folder* locateRoot(folder* current)
{
	while (current->parent != NULL)
	{
		current = current->parent;
	}

	return current;
}


/*
method checking for uncool cows
we analyze the current cow and check if that has access to the leaves of the hierarchy
after locating the root node we traverse down the tree


we check the type of current folder
note if folder is shared it can borrow from parent as long as parent was also shared
if folder is confidential it must include the current cow we are checking if is a leaf

when we reach a leaf and the folder is shared we check if the current cow followed it down or was found there 
when we reach a leaf and the folder is confidential we check the current folder's cow ids and check if is included there
*/
bool findCow(folder* root, int cowID, bool parentHas)
{
	// base case when we reach a leaf node
	if (root == NULL)
	{
		return true;
	}
	if (root->left == NULL && root->right == NULL)
	{
		// analyze the cow ids of the confidential folder
		if (root->type == confidential)
		{
			for (int x = 0; x < root->cowIds.size(); x++)
			{
				if (cowID == root->cowIds[x])
				{
					return true;
				}
			}

			return false;
		}
		else
		{
			// analyzing the a leaf shared folder
			// if the parent had that cow than it can access this folder
			// else if not found in the parent it must be located here to not be uncool
			if (parentHas)
			{
				return true;
			}
			else
			{
				for (int x = 0; x < root->cowIds.size(); x++)
				{
					if (cowID == root->cowIds[x])
					{
						return true;
					}
				}

				return false;
			}
		}
	}

	// no need to bother checking if current is shared and the we already located the cow in parent shared folder
	if (parentHas && root->type == shared)
	{
		return findCow(root->left, cowID, parentHas) && findCow(root->right, cowID, parentHas);
	}
	
	// check if cow ID is located in the current folder
	for (int x = 0; x < root->cowIds.size(); x++)
	{
		if (cowID == root->cowIds[x] && root->type == shared)
		{
			parentHas = true;
			break;
		}

		parentHas = false;
	}

	// recursive call to ensure the cow ID is accessible in the leaf folders
	return findCow(root->left, cowID, parentHas) && findCow(root->right, cowID, parentHas);
}


// method that will analyze all the cows and check their placement in the hierarchy
void FoldersAndCows(folder* root, int totalCows)
{
	vector <int> result;

	// checking all the cows
	for (int x = 0; x < totalCows; x++)
	{
		cout << "Current cow we are analyzing is " << x << endl;
		// condition to see if the cow is uncool
		if (!findCow(root, x, false))
		{
			result.push_back(x);
		}
	}

	// outputting the result
	for (int x = 0; x < result.size(); x++)
	{
		cout << result[x] << " ";
	}
	cout << endl;
}

// simple level order traversal method
void levelOrderTraversal(folder* root)
{
	queue<folder*> list;
	list.push(root);

	while (!list.empty())
	{
		folder* current = list.front();
		list.pop();

		cout << "Current folder is " << current->folderId << endl;
		cout << "The children of this folder is/are" << endl;
		for (int x = 0; x < current->cowIds.size(); x++)
		{
			cout << x + 1 << ". cow ID = " << current->cowIds[x] << endl;
		}
		cout << endl;

		if (current->left != NULL)
		{
			list.push(current->left);
		}

		if (current->right != NULL)
		{
			list.push(current->right);
		}
	}
}


int main() 
{
	// getting total amount of cows
	cout << "Enter the total amount of cows" << endl;
	int cowSize;
	cin >> cowSize;

	// hash table to represent our graph
	map <int, folder*> graph;

	// section to get how many share and confidential folders we are working with
	int shareFolderSize;
	int confidentialFolderSize;
	cout << "Total amount of Shared folders" << endl;
	cin >> shareFolderSize;
	cout << "Total amount of Confidential folders" << endl;
	cin >> confidentialFolderSize;

	// temp to retrieve a starting point for the tree
	// from that point we can locate the root of the whole hierarchy since all folders will have only one parent
	int source; 

	// adding our share folders to our graph
	for (int x = 0; x < shareFolderSize; x++)
	{
		int id;
		int cowCount;
		cout << "Enter the shared folder ID and how many cows it will have" << endl;
		cin >> id >> cowCount;

		// extracting a folder id for later use
		if (x == 0)
		{
			source = id;
		}

		vector <int> cowIds;
		for (int y = 0; y < cowCount; y++)
		{
			int num;
			cout << "Enter the cow ID for cow #" << y + 1 << endl;
			cin >> num;
			cowIds.push_back(num);
		}
		addFolder(graph, id, cowCount, shared, cowIds);
	}


	// adding our confidential folders to our graph
	for (int x = 0; x < confidentialFolderSize; x++)
	{
		int id;
		int cowCount;
		cout << "Enter the confidential folder ID and how many cows it will have" << endl;
		cin >> id >> cowCount;

		vector <int> cowIds;
		for (int y = 0; y < cowCount; y++)
		{
			int num;
			cout << "Enter the cow ID for cow #" << y + 1 << endl;
			cin >> num;
			cowIds.push_back(num);
		}
		addFolder(graph, id, cowCount, confidential, cowIds);
	}

	// getting the total number of connections
	int pairTotal;
	cout << "How many pair connections are there" << endl;
	cin >> pairTotal;

	for (int x = 0; x < pairTotal; x++)
	{
		int parent;
		int child;
		cout << "Enter the parent and child ID to create a connection" << endl;
		cin >> parent >> child;
		makePair(graph, parent, child);
	}

	// getting any possible folder
	folder* current = graph[1];

	// getting the root folder of our hierarchy 
	folder* root = locateRoot(current);

	// optional output for feedback
	cout << endl;
	levelOrderTraversal(root);
	cout << endl << endl;

	// algorithm implementing the folders and cows challenge
	FoldersAndCows(root, cowSize);

	return 0;
}