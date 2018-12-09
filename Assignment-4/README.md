# Problem: Event simulation

You need to simulate the execution of a set of tasks that are given to you.
Assume that there are an infinite number of processors available, so that each task starts as soon as it becomes ready.  
This means that you need to keep track of which tasks are active at any given point in time, and remove them from the active list as they finish.

Assume that the input consists of a set of tasks given in increasing order of start time, and each task has a certain duration associated.
The first line of the file is number of tasks.

For example,  
3  
2 5  
4 23  
7 4  
means there are 3 tasks. The first one starts at time 2, and ends at 7 (2+5). Second starts at 4, ends at 27. Third starts at 7, ends at 11.
We assume each task starts as soon as it is ready, and does not need to wait for a processor or anything else to free up.

This means we can keep track of number of active tasks:  
|  Time    |  #tasks |
|----------|:--------|
|  0 - 2   |     0   |
|  2 - 4   |     1   |
|  4 - 7   |     2   |
|  7 - 11  |     2   |
|  11 - 27 |     1   |

The simulation ends at T=27. Of course, above we could have just written 4-11 #tasks = 2, but I broke it up for clarity.  
This is not part of the output anyway.

Expected output is 3 numbers:

* End of simulation time.
* Max number of active tasks at any given time
* Average number of active tasks over the entire duration, printed to 4 decimal places (use printf("%.4f"))

So expected output for the above inputs is:  
27  
2  
1.1852  

Average active tasks over entire duration is computed here as :
[ 0x(2-0) + 1x(4-2) + 2x(11-4) + 1x(27-11) ] / 27

Assume number of tasks can be up to 1e6, min duration of a task is 1 (all durations and start times integers) and max duration of a task is 1000.
Earliest possible start time is 0.
