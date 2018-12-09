
City Tour
=============

Refer 'Final Exam Question paper', Question 4.b for the problem statement.
You can assume that all nodes are reachable from each other.

Note: For a given list of cities: city1, city2, city3, city4
	  You may visit one of the given city(say city3) on your way to another city(say city2).
	  This does not violate the sequence, provided you are visiting city3 again after city2.

Input and output will be read and written to standard input and output as usual.

Input
-----
1st line: Number of cities to cover (say N)
2nd to (N+1)th line: Cities in order

Output
------
Nodes in sequence (start node to end node)

The included input1.txt shows a case where we want to visit 3 cities.  The output1.txt for this involves passing through about 900 nodes.
The checker script will go through the nodes and look for correctness, and compute the total distance traversed. 
It will not check whether the tour is optimal in any way, only whether it violates any of the graph edge constraints.
