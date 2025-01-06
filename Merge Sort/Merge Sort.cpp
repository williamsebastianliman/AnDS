#include <stdio.h>
void merge(int arr[], int left, int mid, int right)
{
	int n1 = mid-left+1;
	int n2 = right-mid;
	int L[n1];
	int R[n2];
	for(int i=0;i<n1;i++)
	{
		L[i] = arr[left+i];
	}
	for(int i=0;i<n2;i++)
	{
		R[i] = arr[mid+1+i];
	}
	int i = 0;
	int j = 0;
	int k = left;
	while(i<n1&&j<n2)
	{
		if(L[i] < R[j])
		{
			arr[k] = L[i];
			k++;
			i++;
		}
		else
		{
			arr[k] = R[j];
			k++;
			j++;
		}
	}	
	while(i<n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	while(j<n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSort(int arr[], int left, int right)
{
	int mid = left + (right-left)/2;
	if(left<right)
	{
		mergeSort(arr,left,mid);
		mergeSort(arr,mid+1,right);
		merge(arr,left,mid,right);
	}
}
void printResult(int arr[], int size)
{
	for(int i=0;i<size;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}
int main()
{
	int arr[10] = {20,19,8,7,6,5,4,3,2,1};
	mergeSort(arr, 0, sizeof(arr)/sizeof(arr[0])-1);
	printResult(arr,sizeof(arr)/sizeof(arr[0]));
}