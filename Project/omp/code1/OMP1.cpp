#include <iostream>
#include <set>
#include <vector>
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


    set<string> myset;
    set<string> new_set;
    unordered_map<string, int> visited;

    for(string node: graph.NodeSet){
        visited[node] = 0;
    }

    myset.insert(startingNode);
    visited[startingNode] = 1;

    while(!myset.empty()){

        #pragma omp parallel // start the parallel region
        #pragma omp single // using single means that each place the iterator points to will only be executed once
        {
            for(set<string>::iterator it=myset.begin(); it!=myset.end(); ++it){ // create the iterator for our set
                #pragma omp task firstprivate(it) // every task gets its private copy
                {
		    //cout << (*it);
                    vector<string> local_list;
                    for(auto n: graph.neighbors(*it)){ // loop through the neighbors for that node
                        if(visited[n]==0){
                            #pragma atomic capture
                            {
                                visited[n] = 1;
                            }
                            local_list.push_back(n);
                        }
                    }
                    #pragma omp critical // combine all the local lists
                    {
                        for(const auto& node: local_list){
                            new_set.insert(node);
                        }
                    }
                }
            }
        }
        myset = new_set;
        new_set.clear();
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

