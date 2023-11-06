#include <iostream>
using namespace std;

void merge(int arr[], int p, int q, int r) {
  

  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  	L[n1] = M[n2] = INT32_MAX;
	int li = 0;
	int ri = 0;
	for (int i = p; i <= r; ++i)
	{
		if (L[li] <= M[ri])
		{
			arr[i] = L[li];
			li++;
		}
		else
		{
			arr[i] = M[ri];
			ri++;
		}
	}
}

void mergeSort(int arr[], int l, int r) {
  if (l < r) {

    int m = (l+r) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    
    merge(arr, l, m, r);
  }
}


void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++)
    cout << arr[i] << " ";
  cout << endl;
}


int main() {
  int arr[] = {6, 5, 12, 10, 9, 1};
  int size = sizeof(arr) / sizeof(arr[0]);

  mergeSort(arr, 0, size - 1);

  cout << "Sorted array: \n";
  printArray(arr, size);
  return 0;
}

