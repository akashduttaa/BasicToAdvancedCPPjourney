#include<stdio.h>
void swap(int a[],int left,int right)
{
int temp;
temp= a[left];
a[left]=a[right];
a[right]=temp;
}
void quicksort(int a[],int low,int high)
{
    int pivot;
    if(high>low)
{
    pivot=partition(a,low,high);
    quicksort(a,low,pivot-1);
    quicksort(a,pivot+1,high);
   }
}


