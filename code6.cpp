// For this challenge you will be determining whether a car can get around a route with a limited amount of gas.
/*
have the function GasStation(strArr) take strArr which will be an an array consisting of the following elements: N which will be the number of gas stations in a circular route and each subsequent element will be the string g:c where g is the amount of gas in gallons at that gas station and c will be the amount of gallons of gas needed to get to the following gas station. For example strArr may be: ["4","3:1","2:2","1:2","0:1"]. Your goal is to return the index of the starting gas station that will allow you to travel around the whole route once, otherwise return the string impossible. For the example above, there are 4 gas stations, and your program should return the string 1 because starting at station 1 you receive 3 gallons of gas and spend 1 getting to the next station. Then you have 2 gallons + 2 more at the next station and you spend 2 so you have 2 gallons when you get to the 3rd station. You then have 3 but you spend 2 getting to the final station, and at the final station you receive 0 gallons and you spend your final gallon getting to your starting point. Starting at any other gas station would make getting around the route impossible, so the answer is 1. If there are multiple gas stations that are possible to start at, return the smallest index (of the gas station). N will be >= 2.
*/
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// loop through string to compare g and c
// check for stations that provide surplus of gallons or even amount
// calculate the difference in gallons left over and move to the next station
// analyze if is possible to travel the whole route

// Helper function to convert both the g and c values from the string
void expenses(string arr[], int index, int pos, int& gallon, int& travel)
{
	string num;
	// Loop to find the amount of gallons at a station
	for (int x = 0; x < pos; x++)
	{
		num += arr[index][x];
	}
	istringstream(num) >> gallon;
	num.clear();
	// Loop to find amount of gas needed
	for (int y = pos+1; y < arr[index].length(); y++)
	{
		num += arr[index][y];
	}
	istringstream(num) >> travel;
	num.clear();
}

string GasStation(string strArr[], int size) {
	int gallon, travel, station,total, result;
	bool route;
	station = size*2;
	result = -1;
	total = 0;

	// Loop through the gas stations
	for (int x = 1; x < size; x++)
	{		
		int pos = strArr[x].find(':'); // index to help locate g:c
		expenses(strArr, x, pos, gallon, travel);

		// Condition for when having a surplus or even amount of gallons to travel ratio
		if (gallon >= travel)
		{
			total = gallon - travel; // get the amount of gallons left
		
			// loop again through the stations back to the starting route/station from which we started
			int y = x + 1;
			do
			{
				route = true;

				for (y; y < size; y++)
				{
					// ignore the station that we started from
					// Also signal when there is not enough gallons to move to the next station
					if (y == x || total < 0) 
					{
						route = false;
						break;
					}

					pos = strArr[y].find(':');
					expenses(strArr, y, pos, gallon, travel);
					total += gallon;
					total -= travel;
				}

				y = 1; // reset back in the case that our starting station is not at the beginning
			} while (route);

			if (total >= 0 && x < station) // Keeping track of the smallest index in case of multiple stations
			{
				result = total;
				station = x;
			}
		}
	}

	// Condition to analyze if it was possible to travel the whole route
	if (result < 0)
	{
		return "impossible";
	}
	else
	{
		stringstream convert;
		convert << station;
		return convert.str();
	}
}

int main() {
	// keep this function call here
	/* Note: In C++ you first have to initialize an array and set
	it equal to the stdin to test your code with arrays. */
	string A[] = { "4", "1:1", "2:2", "1:2", "0:1" };
	string B[] = { "4", "0:1", "2:2", "1:2", "3:1" };
	string C[] = { "4", "3:1", "2:2", "1:2", "0:1" };
	string D[] = { "3", "2:3", "2:1", "4:4"};
	string E[] = { "5", "3:3", "1:2", "2:2", "3:2", "4:3" };
	string F[] = { "5", "0:1", "2:1", "3:2", "4:6", "4:3" };
	string G[] = { "2", "1:2", "1:2" };
	string H[] = { "6", "3:2", "2:2", "10:6", "0:4", "1:1", "30:10" };
	string I[] = { "5", "2:3", "2:3", "2:3", "500:1", "0:495" };
	cout << GasStation(A, sizeof(A) / sizeof(A[0])) << endl; // impossible
	cout << GasStation(B, sizeof(B) / sizeof(B[0])) << endl; // 4
	cout << GasStation(C, sizeof(C) / sizeof(C[0])) << endl; // 1
	cout << GasStation(D, sizeof(D) / sizeof(D[0])) << endl; // 2
	cout << GasStation(E, sizeof(E) / sizeof(E[0])) << endl; // 3
	cout << GasStation(F, sizeof(F) / sizeof(F[0])) << endl; // 2
	cout << GasStation(G, sizeof(G) / sizeof(G[0])) << endl; // impossible
	cout << GasStation(H, sizeof(H) / sizeof(H[0])) << endl; // 1
	cout << GasStation(I, sizeof(I) / sizeof(I[0])) << endl; // 4
	return 0;
}