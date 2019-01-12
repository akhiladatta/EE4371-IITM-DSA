/*
Author: Atul Balaji (EE16B002)
Date: 11-11-2018
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/*
In this question, we are asked to schedule a tournament between N teams, over (N-1) days, with N/2 games per day, 
such that one team can play exactly one game in a day. For this problem, I have used the approach Round Robin scheduling.
An array (arr) of N-1 elements is constructed, with elements 1 to N-1. This is used to plan the fixtures of the first day. 
The team 1 will play team N (not part of the array), team 2 will play team N-1 and so on.
For the array for subsequent elements, this array is rotated to the right for every subsequent day.
The team at the first index is paired with team N and for other teams, team arr[i] is paired with arr[N-i-1].
*/

// Function to rotate given array to the right once
void rotateArr(int arr[],int n)
{
    int x = arr[n - 1], i; 
    for (i = n - 1; i > 0; i--) 
        arr[i] = arr[i - 1];  
    arr[0] = x; 
}

int main()
{
    int N;
    int M;
    scanf("%d",&N);
    scanf("%d",&M);
    int *arr = new int[N-1];

    // Initialize array
    for (int x=0;x<N-1;x++)
        arr[x] = x+1;
    
    // Update array after rotation and print the pairs of teams who play each other 
    for (int day=0;day<M;day++)
    {   
        printf("%d %d\n",arr[0],N);
        for (int i=1;i<N-i-1;i++)
        {   
            printf("%d %d\n",arr[i],arr[N-i-1]);
        }
        rotateArr(arr,N-1);
    }

    return 0;
}