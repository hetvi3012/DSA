#include iostream>
#include <bits/stdc++.h>
using namespace std;

void heapify(int arr[], int n, int i);
void buildHeap(int arr[], int n);
void heapSort(int arr[], int n);
void insertt(int arr[], int& n, int key);
void deleteRoot(int arr[], int& n);

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2*i;
    int right = 2*i + 1;
    if(left<=n && arr[left] > arr[largest])
            largest = left;
    if (right <=n && arr[right]>arr[laargest])
        largest = right;
    if(largest!= i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr,n,largest);
    }
}

void buildHeap(int arr[], int n)
{

    int startIdx = n/2;
    for(int i = startIdx; i>=1;i--)
            heapify(arr,n,i);
}

void heapSort(int arr[], int n)
{
    buildHeap(arr,n);
    for(int i = n;i>1;i--)
    {
        swap(arr[1], arr[i]);
        heapify(arr,i-1,1);
    }
}

void insertt(int arr[i], int& n, int key)
{
    n++;
    arr[n] = key;
    int i = n;
    while(i>1 && arr[i/2]<arr[i])
    {
        swap(arr[i], arr[i/2]);
        i/=2;
    }
}

void deleteRoot(int arr[], int&n)
{
    if (n==0)
        return;
    arr[1] = arr[n];
    n--;
    heapify(arr,n,1);
}
