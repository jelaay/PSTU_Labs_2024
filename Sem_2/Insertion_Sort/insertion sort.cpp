#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_CTYPE, "rus");
	int tmp;
	const int n = 7;
	/*
	int arr[n];
	int range_min, range_max;
	range_min =2;
	range_max=412;
	for (int i=0;i<n;i++)
	{
		arr[i]=((double)rand()/RAND_MAX)*(range_max-range_min)+range_min;
		cout<<arr[i]<<" ";
	}
	cout<<endl;
	*/
	int arr[n] = { 5,2,4,6,0,1,3 };
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	int key;

	for (int i = 0; i < n; i++)
	{
		key = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	return 0;
}