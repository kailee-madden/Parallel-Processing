#include <iostream>
#include <queue>
#include <random>
#include "graphProperties.h"
#include "testGraphs.cpp"
#include "timer.h"
using namespace std;

/**
 * Sequential breadth-first search traversal implementation 
 * Prints a list of nodes ordered based on the BFS traversal
 * use -std=c++11 flag when compiling
*/ 
void BFStraversal(Graph & graph, const string & startingNode){
    queue<string> myqueue;
    unordered_map<string, bool> visited;
    string currentNode;

    for(string node: graph.NodeSet){
        visited[node] = false;
    }

    myqueue.push(startingNode);
    visited[startingNode] = true;

    while(!myqueue.empty()){
        currentNode = myqueue.front();
        //cout << currentNode << " ";
        myqueue.pop();
        for(string const & neighbor: graph.neighbors(currentNode)){
            if(!visited[neighbor]){
                myqueue.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

int main(){

    extern unordered_map<string, list<string> > small;
    Graph g(small);

    string A = "A";
    cout << "Following is Breadth First Traversal " << "(starting from vertex " << A << ") \n";
    StartTimer();
    BFStraversal(g, A);

    float runtime = GetTimer();
    cout << " total: " << runtime / 1000 << " s" << endl;
    return 0;
}

