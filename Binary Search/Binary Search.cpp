#include <stdio.h>
int binarySearch(int arr[], int left, int right, int target)
{
	int mid = left + (right-left) / 2;
	if(arr[mid] == target)
	{
		printf("%d is Found at Index: %d",target,mid);
		return mid;
	}
	else if(target > arr[mid])
	{
		//Search in the Right Half of the Array
		binarySearch(arr,mid+1,right,target);
	}
	else
	{
		//Search in the Left Half of the Array
		binarySearch(arr,left,mid-1,target);
	}
}
int main()
{
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	binarySearch(arr,0,sizeof(arr)/sizeof(arr[0]),7);
}