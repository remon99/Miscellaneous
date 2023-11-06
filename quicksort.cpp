#include <bits/stdc++.h>
using namespace std;

void quicksort(int arr[], int lowindex, int highindex)
{
    if (lowindex >= highindex)
        return;
    int pivot = arr[highindex];
    int leftptr = lowindex;
    int rightptr = highindex - 1;
    while (leftptr < rightptr)
    {
        while (arr[leftptr] <= pivot and leftptr < rightptr)
            leftptr++;
        while (arr[rightptr] >= pivot and leftptr < rightptr)
            rightptr--;
        swap(arr[leftptr], arr[rightptr]);
    }
    swap(arr[leftptr], arr[highindex]);
    quicksort(arr, lowindex, leftptr - 1);
    quicksort(arr, leftptr + 1, highindex);
}

int main()
{
    int arr[] = {2, 8, 1, 3, 6, 7, 5, 4};
    quicksort(arr, 0, 7);
    for (auto it : arr)
    {
        cout << it << " ";
    }
}