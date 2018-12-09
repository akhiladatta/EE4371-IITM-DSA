/*
Author: Atul Balaji (EE16B002)
Assignment 6: Task Scheduling
Date: 2/12/2018
*/

#include <iostream>
#include <set>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#define MAX_TASKS 10000

// Structure to represent task
struct task
{   
    int tid;
    int rel_time;
    int duration;
    int deadline;
    int progress;
    int slack;
} t[MAX_TASKS];

// Swap two tasks
void swap(struct task *a,struct task *b)
{
    struct task t = *a;
    *a = *b;
    *b = t;
}

// Given a heap t and index i, we restore minheap property for the sub-heap with t[i] as root. 
void minheapify(struct task *t, int i, int heapsize)
{
    int smallest, left, right, k;
    left = 2*i+1;									// Left child
    right = 2*i+2;									// Right child
    // Duration and deadline are used as tie-breakers
    if (left >= heapsize)
        return;
    else 
    {
        if (left < (heapsize) && t[left].rel_time <= t[i].rel_time)
        {   
            smallest = left;
            if (t[left].rel_time == t[i].rel_time)
            {
                if (t[left].deadline <= t[i].deadline)
                {
                    smallest = left;
                    if (t[left].deadline == t[i].deadline)
                    {
                        if (t[left].duration <= t[i].duration)
                            smallest = left;
                        else 
                            smallest = i;
                    }
                }
                else
                    smallest = i;
            }
        } 
        
        else
            smallest = i;
        if (right < (heapsize) && t[right].rel_time <= t[smallest].rel_time)
        {   
            if (t[right].rel_time < t[smallest].rel_time)
                smallest = right;
            else
            {
                if (t[right].deadline <= t[smallest].deadline)
                {
                    if (t[right].deadline < t[smallest].deadline)
                        smallest = right;
                    else
                    {
                        if (t[right].duration <= t[smallest].duration)
                            smallest = right;
                    }
                }
            }
        }

        if (smallest != i) 
        {
            swap(&t[i],&t[smallest]);
            minheapify(t,smallest,heapsize);
        }
    }
}

// Build the min-heap from given array
struct task* buildminheap(struct task *t, int n)
{
    int heapsize = n;
    int j;
    for (j = n/2 - 1; j >= 0; j--) 
    {
        minheapify(t, j, heapsize);
    }
    return t;
}

// Remove the minimum element (root) from the heap
void popmin(struct task *t, int &heapsize)
{
    if (heapsize <= 0)
    {
        printf("Heap underflow!\n");
        return;
    }
    if (heapsize == 1)
        heapsize = heapsize - 1;
    t[0] = t[heapsize-1];
    heapsize = heapsize - 1;
    minheapify(t,0,heapsize);
}

// Get the element with minimum rel_time from heap
struct task extractmin(struct task *t, int &heapsize, int &monitor)
{   
    struct task ret = t[0];
    t[0].progress += 1;
    // If progress is complete, pop it
    if (t[0].progress == t[0].duration)
    {
        if (heapsize > 0)
        {
            popmin(t,heapsize);
            monitor = 1;
        }
    }
    return ret;
}

// Parent index in heap
int parent(int i)
{
    return (i-1)/2;
}

// Delete element at given position from heap
void deleteKey(struct task* t, int &heapsize, int pos)
{
    t[pos].rel_time = -1;
    while (pos != 0 && t[parent(pos)].rel_time > t[pos].rel_time) 
    { 
       swap(&t[pos], &t[parent(pos)]); 
       pos = parent(pos); 
    }
    popmin(t, heapsize);
}

// Find all tasks with rel_time <= curr_time
void findEligibleTasks(struct task* t, int curr_time, int &heapsize, int pos, struct task *arr, int &count, int *posarray)
{
    if (pos >= heapsize) 
        return; 
  
    else if (t[pos].rel_time > curr_time) 
        return; 

    // append to arrays
    arr[count] = t[pos];
    posarray[count] = pos;
    count = count + 1; 

    findEligibleTasks(t, curr_time, heapsize, 2*pos+1, arr, count, posarray); 
    findEligibleTasks(t, curr_time, heapsize, 2*pos+2, arr, count, posarray); 
}

// Find the best task
struct task getBestTask(struct task *arr, int count, int &flag, int *posarray, int &bestpos, int curr_time)
{
    int i, idx;
    int min_deadline = arr[0].deadline;
    int min_curr_slack = arr[0].duration - arr[0].progress;
    for (i=0;i<count;i++)
    {   
        // If the task has no slack, give it priority
        if (arr[i].deadline - arr[i].duration + arr[i].progress - curr_time == 0)
        {
            flag = 1;
            idx = i;
            break;
        }
        else if (arr[i].deadline - arr[i].duration + arr[i].progress - curr_time > 0)
        {
            if (min_curr_slack > (arr[i].duration - arr[i].progress))
            {
                min_curr_slack = arr[i].duration - arr[i].progress;
                idx = i;
            }
            else
                idx = 0;
        }
        // Else return the one with minimum deadline
        else 
        {
            if (min_deadline > arr[i].deadline)
            {
                min_deadline = arr[i].deadline;
                idx = i;
            }
            else
                idx = 0;
        }
    }
    bestpos = posarray[idx];
    return arr[idx];
}

// Print in required format
void display(int* print_array)
{
    printf("%d\t%d\t%d\n",print_array[0],print_array[1],print_array[2]);
}

int main()
{   
    int num_tasks,i,j,k,maxtime = 0, ct, count = 0, flag = 0;
    int heapsize;
    int print_array[3];

    // Read tasks and save in array
    scanf("%d",&num_tasks);
    for(i=0;i<num_tasks;i++)
    {
        scanf("%d\t%d\t%d\t",&t[i].rel_time,&t[i].duration,&t[i].deadline);
        t[i].tid = i + 1;
        t[i].progress = 0;
        t[i].slack = t[i].deadline - t[i].duration - t[i].rel_time;
        if (maxtime < t[i].deadline)
            maxtime = t[i].deadline;
    }

    struct task* by_start = new struct task[MAX_TASKS]; 
    struct task* buffer = new struct task[MAX_TASKS];
    
    // Min-heap
    heapsize = num_tasks;
    by_start = buildminheap(t,num_tasks);

    // Execute task with earliest release time
    int monitor = 0;
    struct task curr_task;
    curr_task = extractmin(by_start, heapsize, monitor);

    print_array[0] = curr_task.rel_time;
    print_array[1] = curr_task.rel_time + 1;
    print_array[2] = curr_task.tid;

    if (monitor == 1)
        display(print_array);

    int *posarray = new int[MAX_TASKS];
    int *v_array = new int[MAX_TASKS];
    int bestpos = 0;
    int repeat_flag = 0;
    int v = 0;
    int start_time = print_array[0];
    ct = curr_task.rel_time + 1;

    // Loop through time
    while (heapsize > 0)
    {   
        count = 0;
        flag = 0;
        bestpos = 0;
        // Buffer is the array of tasks which have release time <= current time
        findEligibleTasks(by_start, ct, heapsize, 0, buffer, count, posarray);
        if (count) 
        {
            struct task best_task = getBestTask(buffer, count, flag, posarray, bestpos, ct);
            // If task id has changed, display the previous one
            if (best_task.tid != print_array[2])
            {
                display(print_array);
                repeat_flag = 0;
            }
            else
                repeat_flag = 1;

            // If slack = 0, execute till completion
            if (flag == 1)
            {
                print_array[0] = ct;
                print_array[1] = best_task.deadline;
                print_array[2] = best_task.tid;
                ct = best_task.deadline;
                // Pop the element from bystart with this tid
                deleteKey(by_start, heapsize, bestpos);
            }

            // Else, execute task with earliest deadline
            else
            {
                if (repeat_flag == 0)
                {
                    start_time = ct;
                }
                print_array[0] = start_time;
                print_array[1] = ct + 1;
                print_array[2] = best_task.tid;
                if (print_array[1] > best_task.deadline)
                {
                    v_array[v++] = best_task.tid;
                }
                
                // Change progress in bystart also
                by_start[bestpos].progress += 1;
                if (by_start[bestpos].progress == by_start[bestpos].duration)
                {   
                    if (heapsize == 1)
                        display(print_array);
                    deleteKey(by_start, heapsize, bestpos);
                }
                ct++;
            }
            // printf("\n");
        }
        else
            ct++;
    }
    std::set<int> sa(v_array, v_array + v);
    // std::cout << "Number of violations = " << sa.size() << std::endl;
    return 0;
}