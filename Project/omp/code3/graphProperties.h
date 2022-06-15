#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

/** 
 * Class to implement an unweighted undirected graph
 * Will create a graph given an adjacency list representing one
 * Implements functions to create graph, return number of nodes, return list of nodes, 
 * return number of edges, return number of neighbors, and return all neighbors of a node
*/

class Graph {
    public:
        unordered_map<string, list<string> > NodeMap;
        unordered_set<string> NodeSet;
        unsigned int NumEdges;
        //Initialize graph object 
        Graph(const unordered_map<string, list<string> > & givenNodeMap);

        //Return number of nodes in graph
        unsigned int num_nodes();

        //Return list of all node labels in graph
        list<string> nodes();

        //Return number of edges in the graph
        unsigned int num_edges();

        //Return number of neighbors of a given node
        unsigned int num_neighbors(string const & node_label);

        //Return vector of neighbors of a given node
        vector<string> neighbors(string const & node_label);
    };

#endif
