#include <bits/stdc++.h>
using namespace std;

void quicksort(int a[], int l, int h)
{
    if (l >= h)
    {
        return;
    }
    int pivot = a[h];
    int left = l;
    int right = h - 1;
    while (left < right)
    {
        while (a[left] <= pivot and left < right)
            left++;
        while (a[right] >= pivot and left < right)
            right--;
        swap(a[left], a[right]);
    }
    swap(a[left], a[h]);
    quicksort(a, l, left - 1);
    quicksort(a, left + 1, h);
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Driver Code
int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    quicksort(arr, 0, n - 1);
    cout << "Sorted array: \n";
    printArray(arr, n);
    return 0;
}