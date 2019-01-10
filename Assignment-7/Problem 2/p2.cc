/*
Author: Atul Balaji (EE16B002)
Date: 3-12-2018
Assignment-9
Reference for implementation of Dinic's Algorithm: https://www.geeksforgeeks.org
Note: I have modified the graph.h file given in the question and am using graphback.h where I have added road capacity in the graph.
*/

#include<iostream>
#include<vector>
#include<list>
#include<limits.h>
#include"graphback.h"
using namespace std;

// Structure to store edge information
struct edge
{
    int src;
    int dst;
    int edge_id;
    double dist;
    int flow;
};

// Path structure
struct path
{
    vector<edge> parts;
};

vector<edge> flows;

// Function to perform breadth first search and compute level array
bool BFS(Graph tngraph, int s, int t, int *level) 
{ 
    for (int i = 0 ; i < tngraph.no_nodes ; i++) 
        level[i] = -1; 
  
    level[s] = 0;  // Level of source vertex 
  
    // Create a queue, enqueue source vertex and mark source vertex as visited.
    list< int > q; 
    q.push_back(s); 

    while (!q.empty()) 
    { 
        int u = q.front(); 
        q.pop_front(); 
        for (int i = 0; i != tngraph.nodes[u].adj.size(); i++) 
        {  

            if (level[tngraph.nodes[u].adj[i]->id] < 0  && tngraph.nodes[u].adj[i]->flow < tngraph.nodes[u].adj[i]->C) 
            { 
                // Level of current vertex is, level of parent + 1 
                level[tngraph.nodes[u].adj[i]->id] = level[u] + 1; 
                q.push_back(tngraph.nodes[u].adj[i]->id); 
            } 
        } 
    } 
  
    // If we cannot reach the sink, return false 
    return level[t] < 0 ? false : true ; 
} 

// Find individual paths
vector<path> extract_paths(vector<int> &p_len, vector<edge> f, int src)
{
    vector<path> paths;
    for (int i = 0; i < f.size(); ++i)
    {
        double dist = 0;
        int j = i;
        path p;

        while(f[j].src != src)
        {
            dist += f[j].dist;
            p.parts.push_back(f[j]);
            j++;
        }

        dist += f[j].dist;
        p.parts.push_back(f[j]);
        i = j;
        paths.push_back(p);
        p_len.push_back(dist);
    }
    return paths;
}

// u     : Current vertex 
// flow  : Current flow send by parent function call 
// t     : Sink 
// start : To keep track of next edge to be explored. Start[i] stores count of edges explored from i. 
int sendFlow(Graph tngraph, int u, int flow, int t, int start[], int * level) 
{ 
    if (u == t) 
        return flow; 
  
    // Traverse all adjacent edges one -by - one. 
    for (;start[u] < tngraph.nodes[u].adj.size();start[u]++) 
    { 
        // Pick next edge from adjacency list of u 
        AdjNode* e = tngraph.nodes[u].adj[start[u]];  
                                      
        if (level[e->id] == level[u]+1 && e->flow < e->C) 
        { 
            // find minimum flow from u to t 
            int curr_flow = min(flow, e->C - e->flow); 
            int temp_flow = sendFlow(tngraph, e->id, curr_flow, t, start, level); 
  
            // flow is greater than zero 
            if (temp_flow > 0) 
            { 
                // add flow  to current edge 
                tngraph.nodes[u].adj[start[u]]->flow += temp_flow; 
                edge f;
                f.src = u;
                f.dst = tngraph.nodes[u].adj[start[u]]->id;
                f.edge_id = tngraph.nodes[u].adj[start[u]]->edge_id;
                f.dist = tngraph.nodes[u].adj[start[u]]->dist;
                f.flow = temp_flow;
                flows.push_back(f);

                // subtract flow from reverse edge of current edge 
                for (int i = 0;i < tngraph.nodes[e->id].adj.size();++i)
                {
                    if(u == tngraph.nodes[e->id].adj[i]->id)
                    {
                        tngraph.nodes[e->id].adj[i]->flow -= temp_flow;
                        break;
                    }
                }
                return temp_flow; 
            } 
        } 
    } 
  
    return 0; 
} 

// Returns maximum flow in graph 
int DinicMaxflow(Graph tngraph, int s, int t, int *level) 
{ 
    if (s == t) 
        return -1; 
  
    int total = 0;  // Initialize result 
  
    // Augment the flow while there is path from source to sink 
    while (BFS(tngraph, s, t, level) == true) 
    { 
        int *start = new int[tngraph.no_nodes+1]; 
        // while flow is not zero
        while (int flow = sendFlow(tngraph, s, INT_MAX, t, start, level)) 
        {
            // Add path flow to overall flow 
            total += flow; 
        }
    } 
  
    // return maximum flow 
    return total; 
} 

int main()
{
    Graph tn_graph;
    tn_graph.read_graph("tn_graph.txt");
    int E = tn_graph.no_edges;
    int V = tn_graph.no_nodes;

    int* level = new int[V];

    int src_city, dst_city, X;
    scanf("%d",&src_city);
    scanf("%d",&dst_city);
    scanf("%d",&X);

    // Create adjacency list
    for (int i = 0; i < E; ++i)
    {
        int a = tn_graph.edges[i].nodes[0];
        int b = tn_graph.edges[i].nodes[1];
        
        AdjNode* tempa = new AdjNode;
        AdjNode* tempb = new AdjNode;

        tempa->id = a;
        tempa->dist = tn_graph.edges[i].distance;
        tempa->edge_id = i;
        tempa->C = tn_graph.edges[i].capacity;
        tempa->flow = 0;
        tempa->rev = b;

        tempb->id = b;
        tempb->dist = tn_graph.edges[i].distance; 
        tempb->edge_id = i;
        tempb->C = tn_graph.edges[i].capacity;
        tempb->flow = 0;
        tempb->rev = a;

        tn_graph.nodes[a].adj.push_back(tempb);
        tn_graph.nodes[b].adj.push_back(tempa);        
    }

    // Call Dinic function
    DinicMaxflow(tn_graph, src_city, dst_city, level);

    vector<int> ed_flow(E);
    vector<int> p_len;
    vector<path> paths = extract_paths(p_len, flows, src_city);

    int flow, sent = 0;
    while(sent < X)
    {
        // pick the minimum path length
        int minlen = INT_MAX;
        int min_id = 0;

        for (int i = 0; i < p_len.size(); ++i)
        {
            if(p_len[i] != -1 && p_len[i] < minlen)
            {
                minlen = p_len[i];
                min_id = i;
            }
        }

        flow = paths[min_id].parts[0].flow;
        p_len[min_id] = -1;
        if(flow >= (X - sent))
            flow = X - sent;

        // update the flows in each edge
        for (int i = 0; i < paths[min_id].parts.size(); ++i)
        {
            tn_graph.edges[paths[min_id].parts[i].edge_id].nodes[0] = paths[min_id].parts[i].src;
            tn_graph.edges[paths[min_id].parts[i].edge_id].nodes[1] = paths[min_id].parts[i].dst;
            ed_flow[paths[min_id].parts[i].edge_id] += flow;
        }
        sent += flow;
    }

    // Print flow in each edge
    for (int i=0;i<E;++i)
    {
        if(ed_flow[i] > 0)
        {
            cout << tn_graph.edges[i].nodes[0] << " " << tn_graph.edges[i].nodes[1] << " " << ed_flow[i] << endl;  
        }
    }

    return 0;
}
