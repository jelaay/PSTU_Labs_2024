#include <iostream>
using namespace std;
int search(int arr[], int n, int x)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == x) return i;
	}
	return -1;
}

int main()
{
	int arr[] = { -7, 23, 56, 1, 88, -42, 17, 0, 99, -130 };
	int arrLength = sizeof(arr) / sizeof(arr[0]);
	int x = 23;
	int res = search(arr, arrLength, x);
	if (res == -1) cout << "Element " << x << " not found" << "\n";
	else cout << "Element " << x << " found with index " << res << "\n";
	return 0;
}

