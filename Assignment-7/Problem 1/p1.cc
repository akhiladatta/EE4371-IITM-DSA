/*
Author: Atul Balaji
Date: 28-11-18
Assignment 8: Supply delivery optimization part 1
*/

#include<bits/stdc++.h> 
#include"graphback.h"
using namespace std; 

// A structure to represent a edge between two vertex 
struct REdge 
{ 
	int v ; 	// Vertex v (or "to" vertex) of a directed REdge u-v. 
				// "From" vertex u can be obtained using index in adjacent array. 
	int flow ;	// flow of data in REdge 
	int C; 	  	// capacity 
	int rev ; 	// To store index of reverse REdge 
			  	// in adjacency list so that we can quickly find it. 
}; 

// Residual Graph 
class RGraph 
{ 
	int V; 								// number of vertices 
	int *level ; 						// stores level of a node 
	vector< REdge > *adj; 				// adjacency lists
	public: 
		RGraph(int V) 
		{ 
			adj = new vector<REdge>[V]; 
			this->V = V; 
			level = new int[V]; 
		} 

		// add edge to the RGraph 
		void addREdge(int u, int v, int C) 
		{ 
			// Forward edge : 0 flow and C capacity 
			REdge a{v, 0, C, adj[v].size()}; 

			// Back edge : 0 flow and 0 capacity 
			REdge b{u, 0, 0, adj[u].size()}; 
			
			// Add edge from u to v and v to u
			adj[u].push_back(a);
			adj[v].push_back(b);
		} 

		bool BFS(int s, int t); 
		int sendFlow(int s, int flow, int t, int ptr[]); 
		int DinicMaxflow(int s, int t); 
}; 

// Finds if more flow can be sent from s to t. Also assigns levels to nodes. 
bool RGraph::BFS(int s, int t) 
{ 
	for (int i = 0 ; i < V ; i++) 
		level[i] = -1; 

	level[s] = 0; // Level of source vertex 

	// Create a queue, enqueue source vertex and mark source vertex as visited. 
	list< int > q; 
	q.push_back(s); 


	vector<REdge>::iterator i; 
	while (!q.empty()) 
	{ 
		int u = q.front(); 
		q.pop_front(); 
		for (i = adj[u].begin(); i != adj[u].end(); i++) 
		{ 
			REdge &e = *i; 
			if (level[e.v] < 0 && e.flow < e.C) 
			{ 
				// Level of current vertex = level of parent + 1 
				level[e.v] = level[u] + 1; 

				q.push_back(e.v); 
			} 
		} 
	} 

	// If we can not reach the sink we return false 
	return level[t] < 0 ? false : true ; 
} 

// u     : Current vertex 
// flow  : Current flow send by parent function call 
// t     : Sink 
// start : To keep track of next edge to be explored. Start[i] stores count of edges explored from i. 
int RGraph::sendFlow(int u, int flow, int t, int start[]) 
{ 
	// Sink reached 
	if (u == t) 
		return flow; 

	// Traverse all adjacent edges one -by - one. 
	for ( ; start[u] < adj[u].size(); start[u]++) 
	{ 
		// Pick next edge from adjacency list of u 
		REdge &e = adj[u][start[u]]; 
									
		if (level[e.v] == level[u] + 1 && e.flow < e.C) 
		{ 
			// find minimum flow from u to t 
			int curr_flow = min(flow, e.C - e.flow); 
			int temp_flow = sendFlow(e.v, curr_flow, t, start); 
			// flow is greater than zero 
			if (temp_flow > 0) 
			{ 
				// add flow to current edge 
				e.flow += temp_flow; 

				// subtract flow from reverse edge of current edge 
				adj[e.v][e.rev].flow -= temp_flow; 
				return temp_flow; 
			} 
		} 
	} 
	return 0; 
} 

// Returns maximum flow in RGraph 
int RGraph::DinicMaxflow(int s, int t) 
{ 
	// Corner case 
	if (s == t) 
		return -1; 

	int total = 0; // Initialize result 

	// Augment the flow while there is path from source to sink 
	while (BFS(s, t) == true) 
	{ 
		// store how many edges are visited from V { 0 to V } 
		int *start = new int[V+1]; 

		// while flow is not zero in RGraph from s to t 
		while (int flow = sendFlow(s, INT_MAX, t, start)) 
		{
			// Add path flow to overall flow 
			total += flow; 
		}
	} 

	for (int i=0;i<V;i++)
    {
        for (int j=0;j<adj[i].size();j++)
        {   
            if (adj[i][j].flow > 0)
                cout << i << " " << adj[i][j].v << " " << adj[i][j].flow << endl;
        }
    }

	// return maximum flow 
	return total; 
} 

int main() 
{ 
	// Create graph from text file
	Graph tn_graph;
    tn_graph.read_graph("./tn_graph.txt");

	// Read input city nodes
    int src_city, dst_city;
    scanf("%d",&src_city);
    scanf("%d",&dst_city);

	int V = tn_graph.no_nodes;
    int E = tn_graph.no_edges;

	// Create residual graph and add edges
	RGraph g(V);
	for (int i=0;i<E;i++)
	{
		g.addREdge(tn_graph.edges[i].nodes[0],tn_graph.edges[i].nodes[1],tn_graph.edges[i].capacity);
	}

	// Compute maxflow and path
	int max_flow = g.DinicMaxflow(src_city, dst_city);
	// cout << "Maximum flow is " << max_flow << endl; 

	return 0; 
} 
