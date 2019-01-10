/*
Author: Atul Balaji (EE16B002)
Assignment 4: Event Driven Simulation
Date: 22/09/2018
*/

/*
Given an input file with number of tasks, start time and duration of each task,
this program returns the time till all tasks complete, max. no.of active tasks at a given time and average no.of active tasks at any given time.
This problem has been solved as a min-heap
*/

#include "stdio.h"
#include "stdlib.h"
#define MAX_TASKS 1000000

// Function prototypes  
void minheapify(long int *, int, int);
long int* buildminheap(long int *, int);
void popmin(long int *,int);

// Main function
int main()
{
    long int num_tasks;
    long int maxtime = 0;													// Time when all tasks end
    int active_tasks = 0;
    int duration;
    int j;
    scanf("%ld",&num_tasks);												// Number of tasks (read from file)
    long int *start_array = calloc(MAX_TASKS, sizeof(long int));			// Array of start times
    long int *end_array = calloc(MAX_TASKS, sizeof(long int));				// Array of end times
    long int *start_heap = calloc(MAX_TASKS, sizeof(long int));				// Heap of start times
    long int *end_heap = calloc(MAX_TASKS, sizeof(long int));				// Heap of end times
    for (int i=0;i<num_tasks;i++)
    {   
        scanf("%ld %d",&start_array[i],&duration);
        end_array[i] = start_array[i] + duration;
        if (end_array[i] > maxtime)
        {
            maxtime = end_array[i];
            j = i;
        }
    }
    start_heap = buildminheap(start_array,num_tasks);
    end_heap = buildminheap(end_array,num_tasks);
    long int start_heapsize = num_tasks;									// Size of start times heap
    long int end_heapsize = num_tasks;										// Size of end times heap
    int max_parallel = 0;													// Maximum tasks which run in parallel
    int sum = 0;
    long int prev_time = 0;

	/*
	The minimum value in the start time heap is compared with minimum value in end time heap.
	If the former is smaller, it means that a new task has started. If the latter is smaller, a task has finished.
	*/
    while (start_heapsize > 0)
    {
        if (start_heap[0] < end_heap[0])
        {   
            sum += active_tasks*(start_heap[0] - prev_time);				// Used to compute average active tasks
            prev_time = start_heap[0];										// Previous start time (root value) is used for finding the interval length
            popmin(start_heap,start_heapsize--);
            active_tasks++;
            if (active_tasks > max_parallel) max_parallel = active_tasks;
        }
        else if (end_heap[0] < start_heap[0])
        {   
            sum += active_tasks*(end_heap[0] - prev_time);
            prev_time = end_heap[0];
            popmin(end_heap,end_heapsize--);
            active_tasks--;
            if (active_tasks > max_parallel) max_parallel = active_tasks;
        }
        else
        {
            popmin(start_heap,start_heapsize--);
            popmin(end_heap,end_heapsize--);
        }
    }
    
	// After start heap becomes empty, we will remove tasks from the end heap as they finish.
    while (end_heapsize > 0)
    {   
        sum += active_tasks*(end_heap[0] - prev_time);
        prev_time = end_heap[0];
        popmin(end_heap,end_heapsize--);
        active_tasks--;
    }
    float avg = (float)sum/maxtime;
    printf("%ld\n",maxtime);
    printf("%d\n",max_parallel);
    printf("%.4f\n",avg);
}

// Build the min-heap from given array
long int* buildminheap(long int a[], int n)
{
    int heapsize = n;
    int j;
    for (j = n/2 - 1; j >= 0; j--) 
    {
        minheapify(a, j, heapsize);
    }
    return a;
}

// Swap two numbers
void swap(long int *a,long int *b)
{
    long int t = *a;
    *a = *b;
    *b = t;
}

// Given a heap a and index i, we restore minheap property for the sub-heap with a[i] as root. 
void minheapify(long int a[], int i, int heapsize)
{
    int smallest, left, right, k;
    left = 2*i+1;									// Left child
    right = 2*i+2;									// Right child
    if (left >= heapsize)
        return;
    else 
    {
        if (left < (heapsize) && a[left] < a[i]) 
            smallest = left;
        else
            smallest = i;
        if (right < (heapsize) && a[right] < a[smallest])  
            smallest = right;
        if (smallest != i) 
        {
            swap(&a[i],&a[smallest]);
            minheapify(a,smallest,heapsize);
        }
    }
}

// Remove the minimum element (root) from the heap
void popmin(long int a[],int heapsize)
{
    if (heapsize <= 0)
        printf("Heap underflow!");
    if (heapsize == 1)
        heapsize--;
    a[0] = a[heapsize-1];
    heapsize--;
    minheapify(a,0,heapsize);
}