# Problem statement

While visiting Lakshadweep, you get to know that every island in the place has not just many towns and villages, but also a capital.  Now these are relatively small islands without much infrastructure, so everyone gets around by walking on roads, and everyone in the country walks at exactly the same speed.  Also, people there value their time, so when traveling from one town to another, they always go by the route that will get them there in the least time.  

Since everyone needs to go to the capital once in a while, the capital is defined as the town that, on average, can be reached in the least amount of time from every other town.  If more than one town satisfies this condition, then the town with the first name in alphabetical order is declared the capital of that island.

However, instead of a map, you are just given a list of roads joining towns, and the lengths of these roads.  To make it worse, you don't know how many islands are there either, or which towns are on which island.

Your job now is to use this information to find all the capitals.

## Input

For each test case, you are given a list of roads, one per row. The first line has two numbers - the first number is the total number of towns, and the second is the total number of roads.  

Each row after the first has two names: one for the starting town, one for the ending town, and a number that gives the distance between the towns. The names of towns are all in lower case letters, with no letters or special characters, and can be up to 20 characters long.  The distance between the towns is an integer (0 < d < 1000).  

Also, unlike the inaptly named Lakshadweep that actually has only 36 islands, 10 of which are inhabited, you may actually find yourself in a place with up to a 1000 islands, each of which may have up to a 1000 towns in it.  

## Output

Print out the names of the capital towns, in alphabetical order.

## Example

For example, if this were in some other part of the world, you might find the following list of roads -

Input:

    9 8
    sainteanne fortdefrance 12
    bassepointe latrinite 5
    bridgetown jackmans 10
    fortdefrance ducos 4
    holetown bridgetown 12
    shanty bridgetown 25
    fortdefrance bassepointe 15
    jackmans shanty 26

Output:

bridgetown
fortdefrance

Bonus question for no marks: the names above are not from Lakshadweep, but from a real place somewhere on Earth. Where?

## Approach

1. Structures are used for edge and node of the graph - towns being nodes, and edges containing distances between towns.
2. Nodes and edges are added when reading from file. A distance matrix is created with distances between every pair of towns.
3. Depth first search is used to obtain the connected components for a particular node.
4. Floyd Warshall algorithm is used to compute all pairs shortest paths. Hereby, distance matrix is updated.
5. For each connected component (island), the town with minimum sum of distances to all other towns is the capital.