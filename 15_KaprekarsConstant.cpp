// For this challenge you will determine when a specific sequence terminates.
/*
have the function KaprekarsConstant(num) take the num parameter being passed which will be a 4-digit number with at least two distinct digits. Your program should perform the following routine on the number: Arrange the digits in descending order and in ascending order (adding zeroes to fit it to a 4-digit number), and subtract the smaller number from the bigger number. Then repeat the previous step. Performing this routine will always cause you to reach a fixed number: 6174. Then performing the routine on 6174 will always give you 6174 (7641 - 1467 = 6174). Your program should return the number of times this routine must be performed until 6174 is reached. For example: if num is 3524 your program should return 3 because of the following steps: (1) 5432 - 2345 = 3087, (2) 8730 - 0378 = 8352, (3) 8532 - 2358 = 6174.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int vectorToInt(vector <int>);

/*
First we extract the digits from the current number
we store those numbers in a vector to sort them in both ascending and descending order
set a condition to check that both result in a 4 digit number
perform the subtraction and recursive back to the initial step until the base case is reached
*/
int KaprekarsConstant(int num) 
{
	int count = 0;

	while (num != 6174)
	{
		vector <int> largeNum;

		// extracting the digits
		while (num > 0)
		{
			int temp = num % 10;
			num /= 10;
			largeNum.push_back(temp);
		}

		// make a copy since we need both a list sorted in descending order and one in ascending order
		vector <int> smallerNum = largeNum;

		// sorting the values from both list
		sort(smallerNum.begin(), smallerNum.end());
		sort(largeNum.begin(), largeNum.end());
		reverse(largeNum.begin(), largeNum.end());

		// taking the sorted elements and converting back to an int
		int biggerValue = vectorToInt(largeNum);
		int smallerValue = vectorToInt(smallerNum);

		// condition in the case the number is not 4 digits for the larger value
		if (largeNum.size() < 4)
		{
			biggerValue *= 10;
		}

		// subtracting the numbers
		num = biggerValue - smallerValue;

		// updating the count
		count++;
	}

	return count;
}

// method to convert the vector to an integer
int vectorToInt(vector <int> list)
{
	int result= 0;
	int position;

	// conditions to determine the position place
	if (list.size() == 4)
	{
		position = 1000;
	}
	else if (list.size() == 3)
	{
		position = 100;
	}
	else if (list.size() == 2)
	{
		position = 10;
	}
	else
	{
		position = 1;
	}

	// loop to add each individual element into the correct place of the number
	for (int x = 0; x < list.size(); x++)
	{
		result += (position*list[x]);
		position /= 10;
	}

	return result;
}

int main() 
{
	cout << KaprekarsConstant(3524) << endl; // 3
	cout << KaprekarsConstant(2111) << endl; // 5
	cout << KaprekarsConstant(9831) << endl; // 7

	

	return 0;
}