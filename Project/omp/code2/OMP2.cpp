#include <iostream>
#include <set>
#include <vector>
#include <omp.h>
#include "graphProperties.h"
#include "testGraphs.cpp"
#include "timer.h"
using namespace std;

void BFStraversal(Graph & graph, const string & startingNode){
    int nthreads, tid;
    #pragma omp parallel private (nthreads, tid)
    {
        /* Obtain thread number */
        tid = omp_get_thread_num();
    
        /* Only master thread does this */
        if (tid == 0) 
        {
            nthreads = omp_get_num_threads();
        printf("Number of threads = %d\n", nthreads);
        }
    }

    vector<string> nodes;
    set<string> new_nodes;
    unordered_map<string, int> visited;
    string currentNode;
    set<string> local_list;

    for(string node: graph.NodeSet){
        visited[node] = 0;
    }

    nodes.push_back(startingNode);
    visited[startingNode] = 1;

    while(!nodes.empty()){
        int len = nodes.size();
        #pragma omp parallel for private(local_list, tid)
        for(int i=0; i<len; i++){
            cout << nodes[i];
            vector<string> neighbors = graph.neighbors(nodes[i]);
            int len2 = neighbors.size();
            for(int j=0; j<len2; j++){
                if(visited[neighbors[j]]==0){
                    #pragma atomic capture
                    {
                        visited[neighbors[j]] = 1;
                    }
                    local_list.insert(neighbors[j]);
                } 
            }

            #pragma omp critical
            for(string n: local_list){
		new_nodes.insert(n);
	    }
        }
        nodes.clear();
	nodes.assign(new_nodes.begin(), new_nodes.end() );
        new_nodes.clear();
    }
}

int main(){
    extern unordered_map<string, list<string> > generated_large;

    Graph g(generated_large);

    string A = "A";
    cout << "Following is Breadth First Traversal " << "(starting from vertex " << A << ") \n";
    StartTimer();
    BFStraversal(g, A);

    float runtime = GetTimer();
    cout << " total: " << runtime / 1000 << " s" << endl;
    return 0;
}

