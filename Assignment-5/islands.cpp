/*
Author: Atul Balaji (EE16B002)
Assignment 5: Finding Island Capitals
Date: 10/11/2018
Reference for Floyd Warshall Algorithm: geeksforgeeks.org
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define WORDLEN 30
#define INF 1000000

// Structure to store an edge
struct edge
{
    int weight;
    struct node *next_node;
    struct edge *next;
};

// Structure to store node
struct node
{
    int id;
    int visited;
    char town_name[WORDLEN];     // Name of town
    struct edge *e;
};

// Perform depth-first search
void DFS(node &src,int &idx, int id_array[])
{
    src.visited = 1;
    edge* e = src.e;
    id_array[idx] = src.id;
    idx++;
    while (e !=NULL)
    {   
        if (!e->next_node->visited) 
            DFS(*e->next_node,idx,id_array);
        e = e->next;
    }
}

// Add a new node, edge to the graph
void new_node(node* currentnode, node* nextnode, int weight)
{
    edge *new_edge = new edge;
    new_edge->weight = weight;
    new_edge->next_node = nextnode;
    new_edge->next = currentnode->e;
    currentnode->e = new_edge;
}

// Get node id given the node name
int get_node(node nodes[],char string [],int &ct)
{
    int i;
    for(i=0;i<ct;i++)
    {
        if(!strcmp(string,nodes[i].town_name))
            return i;
    }
    ct++;
    strcpy(nodes[i].town_name,string);
    nodes[i].id = i;
    return i;
}

// String comparison function for quicksort
int cmpstringp(const void *p1, const void *p2)
{
    return strcmp(* (char * const *) p1, * (char * const *) p2);
}

int main()
{
    int n_vert,n_edge;
    int min_sum, sum, components = 0;
    int idx,weight,ct=0;
    int id1, id2;

    // Read in no.of vertices, edges
    scanf("%d %d",&n_vert,&n_edge);

    int **distance = new int*[n_vert];
    int *id_arr = new int[n_vert];

    node *nodes = new node[n_vert];
    node *v;

    // Initialize distance matrix
    for(int i=0;i<n_vert;i++)
    {
        distance[i] = new int[n_vert];
        for(int j=0;j<n_vert;j++)
        {   
            if (j == i)
                distance[i][j] = 0;
            else
                distance[i][j] = INF;
        }
    }

    char first_string[WORDLEN];
    char second_string[WORDLEN];

    for(int i=0;i<n_edge;i++)
    {
        scanf("%s %s %d",first_string,second_string,&weight);
        id1 = get_node(nodes,first_string,ct);
        id2 = get_node(nodes,second_string,ct);
        new_node(&nodes[id1],&nodes[id2],weight);
        new_node(&nodes[id2],&nodes[id1],weight);
        distance[id2][id1] = weight;
        distance[id1][id2] = weight;    
    }

    // Array of strings containing the name of capitals
    char **capitals = new char*[n_vert];
    char capital_name[WORDLEN];

    for(int i=0;i<n_vert;i++)
        capitals[i] = new char[WORDLEN];
    
    for(int k=0;k<n_vert;k++) 
    {   
        idx = 0;
        if (nodes[k].visited == 0)
            DFS(nodes[k],idx,id_arr);
        if (idx >0)
        {   
            // Floyd Warshall Algorithm
            for (int x1=0;x1<idx;x1++) 
            {   
                for (int x2=0;x2<idx;x2++) 
                {  
                    for (int x3=0;x3<idx;x3++) 
                    {   
                        // Relaxation step
                        if (distance[id_arr[x2]][id_arr[x1]] + distance[id_arr[x1]][id_arr[x3]] < distance[id_arr[x2]][id_arr[x3]]) 
                            distance[id_arr[x2]][id_arr[x3]] = distance[id_arr[x2]][id_arr[x1]] + distance[id_arr[x1]][id_arr[x3]];
                    } 
                } 
            }
            min_sum = INF;
            bool b1,b2;
            for (int a=0;a<idx;a++) 
            {    
                sum = 0;
                for (int b=0;b<idx;b++) 
                    sum += distance[id_arr[a]][id_arr[b]];
                if (sum < min_sum)
                {
                    strcpy(capital_name,nodes[id_arr[a]].town_name);
                    min_sum = sum;
                }
                // Tie-breaker condition of alphabetical order
                else if ((strcmp(capital_name,nodes[id_arr[a]].town_name)>0) && (sum == min_sum))
                    strcpy(capital_name,nodes[id_arr[a]].town_name);
            }
            strcpy(capitals[components],capital_name);
            components++;
        }
    }

    // Sort the capitals in alphabetical order and print them
    qsort(capitals,components,sizeof(char *),cmpstringp);
    for (int i=0;i<components;i++)
        printf("%s\n",capitals[i]);
    return 0;    
}