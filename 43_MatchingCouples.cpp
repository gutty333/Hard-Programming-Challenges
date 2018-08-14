// This challenge will require knowledge of basic mathematical combinations.
/*
have the function MatchingCouples(arr) take the arr parameter being passed which will be an array of integers in the following format: [B, G, N] where B represents the number of boys, G represents the number of girls, and N represents how many people you want to pair together. Your program should return the number of different ways you can match boys with girls given the different arguments. For example: if arr is [5, 3, 2], N=2 here so you want to pair together 2 people, so you'll need 1 boy and 1 girl. You have 5 ways to choose a boy and 3 ways to choose a girl, so your program should return 15. Another example: if arr is [10, 5, 4], here N=4 so you need 2 boys and 2 girls. We can choose 2 boys from a possible 10, and we can choose 2 girls from a possible 5. Then we have 2 different ways to pair the chosen boys and girls. Our program should therefore return 900

N will always be an even number and it will never be greater than the maximum of (B, G). B and G will always be greater than zero.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
we use a step down approach
we gather the amount of possible combinations pertaining to each boy
*/
int MatchingCouples(int arr[]) 
{
	int pairSize = arr[2]/2;
	int total = 0;

	if (pairSize == 1)
	{
		return arr[0] * arr[1];
	}
	else
	{
		for (int x = arr[0]; x > 0; x--)
		{
			int currentTotal = (x - 1)*((pairSize-1)*(arr[1] - 1))*arr[1];
			total += currentTotal;
		}
	}

	return total;
}

int main() 
{
	int A[] = { 5, 3, 2 };
	int B[] = { 10, 5, 4 };
	int C[] = { 5, 5, 4 };
	int D[] = { 2, 2, 2 };
	int E[] = { 10, 10, 6 };
	int F[] = { 15, 10, 6 };

	cout << MatchingCouples(A) << endl; // 15
	cout << MatchingCouples(B) << endl; // 900
	cout << MatchingCouples(C) << endl; // 200
	cout << MatchingCouples(D) << endl; // 4
	cout << MatchingCouples(E) << endl; // 86400
	cout << MatchingCouples(F) << endl; // 327600

	return 0;
}
