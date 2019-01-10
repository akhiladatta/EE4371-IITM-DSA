/*               TEMPLATE HEADER FILE FOR GRAPH (EE4731)                  */
/* Data structure for graph, and function to read in format 
*  as specified in problem statement on Moodle.
*/


#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>


using namespace std;

struct AdjNode{
	int id;
	double dist;
	int flow ;
    int C;
    int rev;
    int edge_id;
};

struct Node {
    double lat;
    double lon;
	vector<AdjNode*> adj;
};


struct Edge {
    char type;
	int capacity;
    unsigned long nodes[2];
    double distance;
};


struct Graph {
    Edge *edges;
    Node *nodes;
    unsigned long no_nodes;
    unsigned long no_edges;
    int *level;
    vector< Edge > *adj; 

    bool read_graph(const char *file_name) 
	{
		ifstream file;

		/* Read nodes of the graph */
		file.open(file_name);
		if (file) 
		{
			file >> no_nodes;
		} 
		else 
		{
			cout << "[!] Nodes input file is empty" << endl;
			exit(0);
		}
		nodes = (Node *) malloc(sizeof(Node) * no_nodes);
		for (unsigned i = 0; i < no_nodes; ++i) 
		{
			file >> nodes[i].lat;
			file >> nodes[i].lon;
		}
		file >> no_edges;
		edges = (Edge *) malloc(sizeof(Edge) * no_edges);
		for (unsigned i = 0; i < no_edges; ++i) 
		{
			file >> edges[i].nodes[0];
			file >> edges[i].nodes[1];
			file >> edges[i].type;
			file >> edges[i].distance;
			switch (edges[i].type)
			{
				case 'p': edges[i].capacity = 100;
						  break;
				case 's': edges[i].capacity = 50;
						  break;
				case 't': edges[i].capacity = 20;
						  break;
				default: printf("Wrong type");
						 break;
			}
		}
		file.close();
    }


    void print_nodes() 
	{
		for (int i = 0; i < no_nodes; ++i) 
		{
			cout << i << "  " << nodes[i].lat << "  " << nodes[i].
			lon << "  " << endl;
		}
    }

    void print_edges() 
	{
		for (int i = 0; i < no_edges; ++i) 
		{
	    	cout << edges[i].nodes[0] << "  " << edges[i].nodes[1] << "  "
			<< edges[i].type << "  " << edges[i].distance << endl;
		}
    }

    void destructor() 
	{
		free(this->nodes);
		free(this->edges);
    }
};
