/*
Author: Atul Balaji (EE16B002)
Date: 11-11-2018
Q4: Finding shortest tour from map of TN
*/

/*
In this question, we are required to find the shortest tour of a set of K cities in the Tamil Nadu roads dataset.
For this, first I have read the graph information from the "tn_graph.txt" file, using graph.h provided.
The graph is then converted to an adjacency list representation which can be used by Dijkstra's algorithm.
Dijkstra's algorithm is implemented using a min-heap representation, which results in a complexity of O(ElogV).
In the function which implements Dijkstra's, another array called parent is passed,
which is used to store the parent of each node v which is being visited.
The minimum distances are found between every city and the next city (as given in the input sequence).
The path taken (intermediate nodes) are printed using backtracking from destination node to source node using the parent array.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include"graph.h"

// A structure to represent a node in adjacency list 
struct Vertex 
{ 
	int dst; 						// Destination vertex for this vertex in the adjacency list
	double weight;					// Weight of the edge
	struct Vertex* next;		    // Pointer to next node
}; 

// A structure to represent an adjacency list 
struct AdjList 
{ 
	struct Vertex *head; 		// pointer to head node of list 
}; 

// A structure to represent a graph. A graph is an array of adjacency lists. 
// Size of array will be V (number of vertices in graph) 
struct DGraph 
{ 
	int V; 
	struct AdjList* array; 
}; 

// Function to create a new adjacency list node 
struct Vertex* CreateVertex(int dst, double weight) 
{ 
	struct Vertex* newVertex = (struct Vertex*) malloc(sizeof(struct Vertex)); 
	newVertex->dst = dst; 
	newVertex->weight = weight; 
	newVertex->next = NULL; 
	return newVertex;
} 

// A utility function that creates a graph of V vertices 
struct DGraph* createGraph(int V) 
{ 
	struct DGraph* dgraph = (struct DGraph*) malloc(sizeof(struct DGraph)); 
	dgraph->V = V; 

	// Create an array of adjacency lists. Size of array will be V 
	dgraph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList)); 

	// Initialize each adjacency list as empty by making head as NULL 
	for (int i = 0; i < V; ++i) 
		dgraph->array[i].head = NULL; 

	return dgraph; 
} 

// Adds an edge to an undirected graph 
void addEdge(struct DGraph* dgraph, int src, int dst, double weight) 
{ 
	// Add an edge from vertex src to vertex dst. A new node is added to the adjacency list of src. 
    // The node is added at the begining.
	struct Vertex* newVertex = CreateVertex(dst, weight); 
	newVertex->next = dgraph->array[src].head; 
	dgraph->array[src].head = newVertex; 

	// Since the graph is undirected, add an edge from dst to src as well.
	newVertex = CreateVertex(src, weight); 
	newVertex->next = dgraph->array[dst].head; 
	dgraph->array[dst].head = newVertex; 
} 

// Structure to represent a node in a min-heap
struct MinHeapNode
{ 
	int v; 
	double dist; 
}; 

// Structure to represent a min heap 
struct MinHeap 
{ 
	int size;	 					// Number of heap nodes present currently 
	int capacity; 					// Capacity of min heap 
	int *pos;
	struct MinHeapNode **array;
}; 

// Function to create a new node in a min heap
struct MinHeapNode* newMinHeapNode(int v, double dist) 
{ 
	struct MinHeapNode* minHeapNode = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode)); 
	minHeapNode->v = v; 
	minHeapNode->dist = dist;
	return minHeapNode; 
} 

// Function to create a Min Heap 
struct MinHeap* createMinHeap(int capacity) 
{ 
	struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap)); 
	minHeap->pos = (int *)malloc(capacity * sizeof(int)); 
	minHeap->size = 0; 
	minHeap->capacity = capacity; 
	minHeap->array = (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*)); 
	return minHeap; 
} 

// Function to swap two nodes of min heap.
void swapNode(struct MinHeapNode** a, struct MinHeapNode** b) 
{ 
	struct MinHeapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 

// Function to heapify at given index. Also updates position of nodes when they are swapped. 
void minHeapify(struct MinHeap* minHeap, int idx) 
{ 
	int smallest, left, right; 
	smallest = idx; 
	left = 2 * idx + 1; 
	right = 2 * idx + 2; 

	if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist ) 
	    smallest = left; 

	if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist ) 
	    smallest = right; 

	if (smallest != idx) 
	{ 
		// The nodes to be swapped in min heap 
		MinHeapNode *smallestNode = minHeap->array[smallest]; 
		MinHeapNode *idxNode = minHeap->array[idx]; 

		// Swap positions 
		minHeap->pos[smallestNode->v] = idx; 
		minHeap->pos[idxNode->v] = smallest; 

		// Swap nodes 
		swapNode(&minHeap->array[smallest], &minHeap->array[idx]); 
		minHeapify(minHeap, smallest); 
	} 
} 

// Function to check if the given Min Heap is empty
int isEmpty(struct MinHeap* minHeap) 
{ 
	return minHeap->size == 0; 
} 

// Function to extract minimum node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
{ 
	if (isEmpty(minHeap)) 
		return NULL; 

	// Store the root node 
	struct MinHeapNode* root = minHeap->array[0]; 

	// Replace root node with last node 
	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; 
	minHeap->array[0] = lastNode; 

	// Update position of last node 
	minHeap->pos[root->v] = minHeap->size-1; 
	minHeap->pos[lastNode->v] = 0; 

	// Reduce heap size and heapify root 
	--minHeap->size; 
	minHeapify(minHeap, 0); 

	return root; 
} 

// Function to decrease dist value of a given vertex v. 
// It uses pos[] of min heap to get the current index of node in the heap.
void decreaseKey(struct MinHeap* minHeap, int v, double dist) 
{ 
	// Get the index of v in heap array 
	int i = minHeap->pos[v]; 

	// Get the node and update its dist value 
	minHeap->array[i]->dist = dist; 

	// Travel up while the complete tree is not heapified. 
	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) 
	{ 
		// Swap this node with its parent 
		minHeap->pos[minHeap->array[i]->v] = (i-1)/2; 
		minHeap->pos[minHeap->array[(i-1)/2]->v] = i; 
		swapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]); 

		// move to parent index 
		i = (i - 1) / 2; 
	} 
} 

// A utility function to check if a given vertex 'v' is in the heap 
bool isPresent(struct MinHeap *minHeap, int v) 
{ 
    if (minHeap->pos[v] < minHeap->size) 
	    return true;
    else
        return false; 
} 

// The function that calulates distances of shortest path using Dijkstra's algorithm. 
void dijkstra(struct DGraph* dgraph, int src, double* dist, int* parent) 
{ 
	int V = dgraph->V;					// Get the number of vertices in dgraph

	// Create heap 
	struct MinHeap* minHeap = createMinHeap(V); 

	// Initialize min heap with all vertices. Assign distance of all vertices as infinity.
	for (int v = 0; v < V; ++v) 
	{ 
		dist[v] = INT_MAX; 
		minHeap->array[v] = newMinHeapNode(v, dist[v]); 
		minHeap->pos[v] = v; 
	} 

	// Make distance of src vertex as 0 so that it is extracted first 
	minHeap->array[src] = newMinHeapNode(src, dist[src]); 
	minHeap->pos[src] = src; 
	dist[src] = 0; 
	decreaseKey(minHeap, src, dist[src]); 

	// Initially size of min heap is equal to V 
	minHeap->size = V; 

	// In the following loop, min heap contains all nodes which have not been visited. 
	while (!isEmpty(minHeap)) 
	{ 
		// Extract the vertex with minimum distance 
		struct MinHeapNode* minHeapNode = extractMin(minHeap); 
		int u = minHeapNode->v;                                             // Store the extracted vertex number 

		// Traverse through adjacency list (array) of u (extracted vertex) and update their distance values 
		struct Vertex* temp = dgraph->array[u].head; 
		while (temp != NULL)
		{ 
			int v = temp->dst; 
			// If shortest distance to v is not finalized yet, and distance to v through u is less than previously calculated value
			if (isPresent(minHeap, v) && dist[u] != INT_MAX && temp->weight + dist[u] < dist[v]) 
			{ 
				dist[v] = dist[u] + temp->weight;
                parent[v] = u;                                              // assign parent
				decreaseKey(minHeap, v, dist[v]);                           // update distance in min heap
			} 
			temp = temp->next; 
		} 
	} 
} 

int main()
{
    Graph tn_graph;                                 // Create graph using graph.h library after reading data
    tn_graph.read_graph("./tn_graph.txt");

    int num_cities, v, ct;
    int n_node = tn_graph.no_nodes;
    int n_edge = tn_graph.no_edges;
    int *parent = new int[n_node];                  // Parent array to store the parent of each vertex in the graph
    int *child = new int[n_node];                   // Used to print the nodes in specified order
    double *dist = new double[n_node];              // Distance array to be passed to Dijkstra's

    for (int k=0;k<n_node;k++)
        parent[k] = -1;

    scanf("%d",&num_cities);                        // Read in the no.of cities
    
    int *city_ids = new int[num_cities];            // Array of node ids of the cities
    for (int i=0;i<num_cities;i++)
        scanf("%d",&city_ids[i]);

    // Create graph in Adjacency list format, so that it can be made use of
    struct DGraph* dgraph = createGraph(n_node);
    for (int i=0;i<n_edge;i++)
        addEdge(dgraph,tn_graph.edges[i].nodes[0],tn_graph.edges[i].nodes[1],tn_graph.edges[i].distance);

    for (int j=0;j<num_cities;j++)
    {   
        // Find Dijkstra distances for each node from the city given by city_ids[j]
        dijkstra(dgraph,city_ids[j],dist,parent);
        ct = 0;
        // Do backtracking to find the path from destination vertex to source vertex, using the parent array
        for (v = city_ids[(j+1) % num_cities];v != city_ids[j];v = parent[v])
            child[ct++] = parent[v];
        // Print the path in required format
        for (int l = ct-1;l >= 0;l--)
            printf("%d\n",child[l]);
        if (j == num_cities-1)
            printf("%d\n",city_ids[0]);
    }
    return 0;
}


