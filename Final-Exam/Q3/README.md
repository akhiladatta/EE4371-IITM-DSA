# Q3 - Tournament Scheduling

The input file consists of an even number input N, and a number of days M. The output file needs to have a set of (M)*(N/2) lines.  
Each line has the two players for a single match. One day comprises N/2 lines, i.e, day 0 is lines 0 to N/2-1, day 1 is lines N/2 to N-1, and so on.

## RULES FOR THE CHECKER

No player should be involved in more than one match per day. All players should have played all other players after (N-1) days are done.

## SAMPLE INPUT FILE

6  
5

## SAMPLE OUTPUT FILE

1 5  
6 4  
2 3  
1 4  
5 3  
6 2  
1 3  
4 2  
5 6  
1 2  
3 6  
4 5  
1 6  
2 5  
3 4

## Approach

1. In this question, we are asked to schedule a tournament between N teams, over (N-1) days, with N/2 games per day, such that a team can play exactly one game in a day. For this problem, I have used the principle of **Round Robin scheduling**.
2. An array of N-1 elements is constructed, with elements 1 to N-1. This is used to plan the fixtures of the first day. The team 1 will play team N (not part of the array), team 2 will play team N-1 and so on.
3. For the subsequent days, this array is rotated to the right. The team at the first index is paired with team N and for other teams, team `array[i]` is paired with `array[N-i-1]`.