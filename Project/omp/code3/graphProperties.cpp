#include "graphProperties.h"

Graph::Graph(const unordered_map<string, list<string> > & givenNodeMap){
    NumEdges = 0;

    for(const auto &kv: givenNodeMap){
        NodeSet.insert(kv.first);
        
        list<string> vect;
        for(const string &n : kv.second){
            NodeSet.insert(n);
            vect.push_back(n);
            NumEdges += 1;
        }
        NodeMap[kv.first] = vect;
    }
}

unsigned int Graph::num_nodes(){
    return NodeSet.size();
}

list<string> Graph::nodes(){
    list<string> NodeVector(NodeSet.begin(), NodeSet.end());
    return NodeVector;
}

unsigned int Graph::num_edges(){
    return NumEdges;
}

unsigned int Graph::num_neighbors(string const & node_label){
    return NodeMap[node_label].size();
}

vector<string> Graph::neighbors(string const & node_label){
    vector<string> N;
    for(string & n: NodeMap[node_label]){
        N.push_back(n);
    }
    return N;
}
