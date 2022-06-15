#include <iostream>
#include <omp.h>
#include "graphProperties.h"
#include "testGraphs.cpp"
#include "timer.h"
using namespace std;

/**
 * OpenMP breadth-first search traversal implementation 
 * Prints a list of nodes ordered based on the BFS traversal
 * use -std=c++11 flag when compiling
*/ 
void BFStraversal(Graph & graph, const string & startingNode){
    vector<string> frontier;
    vector<string> new_frontier;
    unordered_map<string, int> visited;

    for(string node: graph.NodeSet){
        visited[node] = 0; // represents false
    }

    frontier.push_back(startingNode);
    visited[startingNode] = true;

    while(1){
        #pragma omp parallel
        {
            int tid = omp_get_thread_num();
            int numthreads = omp_get_num_threads();
            vector<string> local_new_frontier;
            string currentNode;
            int check;

            // traverse the frontier, jumping based on tid and numthreads 
            // (ex. tid 1 accesses frontier[1] then accesses frontier[1+numthreads] and so on)
            for(int i=tid; i<frontier.size(); i+=numthreads){
                currentNode = frontier[i];
                //cout << currentNode;

                // check all the nodes neighbors
                for(string const & neighbor: graph.neighbors(currentNode)){
                    if(visited[neighbor]==0){ // this is where we could use a critical section but it would be slow
                        #pragma omp atomic capture 
                        {
                            check = visited[neighbor]; // only one thread will have check = 0
                            visited[neighbor] = 1; 
                        }
                        if(check==0){
                            local_new_frontier.push_back(neighbor);
                        }
                    }
                }
            }

            #pragma omp critical // now we use a critical region to join all the local new frontiers
            {
                new_frontier.insert(end(new_frontier), begin(local_new_frontier), end(local_new_frontier));
            }
        }
        if(new_frontier.size()==0){
            break;
        }
        else{
            frontier.clear();
            frontier = new_frontier;
            new_frontier.clear();
        }

    }

}

int main(){
    extern unordered_map<string, list<string> > extreme_large;

    Graph g(extreme_large);

    string A = "A";
    cout << "Following is Breadth First Traversal " << "(starting from vertex " << A << ") \n";
    StartTimer();
    BFStraversal(g, A);

    float runtime = GetTimer();
    cout << " total: " << runtime / 1000 << " s" << endl;
    return 0;
}

