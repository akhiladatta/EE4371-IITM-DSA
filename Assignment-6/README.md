# Pre-emptive Task Scheduling

Consider a set of tasks to be executed on a processor - K1, K2. Each task has 3 parameters to be taken into while scheduling - release time, duration and deadline. Release time(R) is the earliest possible start time of the task. Duration(T) is the amount of time taken for the execution of the task. And, deadline(D) is the latest possible finish time of the task.

|    |   R    |   T   |   D   |
|----|:-------|:------|:------|
| K1 |   2    |   3   |   6   |
| K2 |   4    |   2   |   8   |

The above tasks can be scheduled in the following way.

|  Time  |  Task  |
|--------|:-------|
|  2-5   |   K1   |
|  5-7   |   K2   |

Consider a third task K3 is also on the list.

|    |   R    |   T   |   D   |
|----|:-------|:------|:------|
| K1 |   2    |   3   |   6   |
| K2 |   4    |   2   |   8   |
| K3 |   1    |   2   |   6   |

The above tasks can not be scheduled as done earlier. The answer is preemptive scheduling, where the execution of a task can be suspended and resumed later. The tasks can be scheduled using preemption as follows.

|  Time  |  Task  |
|--------|:-------|
|  1-2   |   K3   |
|  2-5   |   K1   |
|  5-6   |   K3   |
|  6-8   |   K2   |

Now, consider a fourth task K4 is also on the list.

|    |   R    |   T   |   D   |
|----|:-------|:------|:------|
| K1 |   2    |   3   |   6   |
| K2 |   4    |   2   |   8   |
| K3 |   1    |   2   |   6   |
| K4 |   6    |   4   |   11   |

The schedule will be -

|  Time  |  Task  |
|--------|:-------|
|  1-2   |   K3   |
|  2-5   |   K1   |
|  5-6   |   K3   |
|  6-8   |   K2   |
|  8-12  |   K4   |

However, there is a violation of deadline on the last task.  
These four tasks can not be scheduled without a violation on a single processor system.

## PROBLEM STATEMENT

Write an algorithm for preemptively scheduling tasks on a single processor system that minimizes the number of deadline violations. The input file will be in the following format.

------------input.in------------------

4

2   3   5

4   2   8

1   2   6

6   4   11

--------------------------------------

The first line is the number of tasks and the remaining lines are the parameters of each task. The output file should contain the start and finish times and the task number.

------------output.out----------------

1   2   3

2   5   1

5   6   3

6   8   2

8   1   4

--------------------------------------

## Approach

1. Maintain a structure for each task that contains the release time, duration, deadline and progress.
2. Build a min-heap using the tasks ordered by release time.
3. Start the simulation and keep it running as long as heapsize > 0. First execute the task with minimum release time.
4. After that, make a list of the eligible tasks which can be executed at the current time (tasks with release time <= current time).
5. To select from these eligible tasks, determine if any task has no slack (deadline - current time - (duration - progress)). If yes, execute it.
6. Else, execute the task with earliest deadline.
