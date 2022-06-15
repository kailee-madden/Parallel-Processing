#ifndef TESTS
#define TESTS
#include <random>
#include <string>
#include <list>
#include <unordered_map>
#include <iostream>
using namespace std;

string random_generator(const int size){
    static const char alphanum[] = 
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string str;
    str.reserve(size);

    for(int i=0; i<size; i++){
        str += alphanum[rand() % (sizeof(alphanum)-1)];
    }

    return str;
}

/* Generates a random adjacency list for an undirected graph
Takes in the number of nodes and the length of string for generation of the nodes */
unordered_map<string, list<string> > adjacency_list_generator(const int num_nodes, const int size){
    unordered_map<string, list<string> > adjList;
    vector<string> nodes;
    random_device rd;
    mt19937 gen(rd());
    bernoulli_distribution d(.9);
    list<string> empty;
    adjList["A"] = empty;

    for(int i=0; i<num_nodes; i++){ // generate all the random strings for the nodes
        nodes.push_back(random_generator(size));
    }

    for(int j=0; j<num_nodes; j++){ // generate the connections between nodes
        if(j==0){ adjList[nodes[j]] = empty; }
        for(int k=0; k<num_nodes; k++){
            if(j==k+1){ // ensure this is a fully connected graph
                adjList[nodes[j]].push_back(nodes[k]); 
                adjList[nodes[k]].push_back(nodes[j]); 
            } 
            if(d(gen)){ // if true (will be with 10% likelihood) then add this node as a connection
                adjList[nodes[j]].push_back(nodes[k]); 
                adjList[nodes[k]].push_back(nodes[j]); // undirected graph so connected on both ends
            } 
        }
    }
    adjList[nodes[num_nodes-1]].push_back("A");
    adjList["A"].push_back(nodes[num_nodes-1]);

    return adjList;
}

unordered_map<string, list<string> > generated_large = adjacency_list_generator(1000, 17);

unordered_map<string, list<string> > extreme_large = adjacency_list_generator(10000, 30);

unordered_map<string, list<string> > small =
{
    {"A", {"B", "C", "E"} },
    {"B", {"A", "C"} },
    {"C", {"A", "B", "E"} },
    {"D", {"E"} },
    {"E", {"A", "C", "D"} } 
}; 

unordered_map<string, list<string> > dense =
{
    {"A", {"A", "1", "B", "C", "D", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9"} },
    {"B", {"A", "2", "B", "C", "D", "E", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9"} },
    {"C", {"A", "B", "C", "D", "E", "F", "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9"} },
    {"D", {"A", "B", "C", "D", "E", "F", "G", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9"} },
    {"E", {"A", "B", "C", "D", "E", "F", "G", "H", "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9"} },
    {"F", {"A", "B", "C", "D", "E", "F", "G", "H", "I", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9"} },
    {"G", {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"H", {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"I", {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"J", {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"K", {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"L", {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"M", {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"N", {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"O", {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"P", {"Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"Q", {"Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"R", {"Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"S", {"S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"T", {"U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"U", {"W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g","h", "i", "j", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"V", {"Y", "Z", "a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"W", {"Z", "a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"X", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"Y", {"c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"Z", {"e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"a", {"g","h", "i", "j", "k", "l", "m", "n", "o", "p", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"b", {"i", "j", "k", "l", "m", "n", "o", "p", "q", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"c", {"k", "l", "m", "n", "o", "p", "q", "r", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"d", {"m", "n", "o", "p", "q", "r", "s", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"e", {"o", "p", "q", "r", "s", "t", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9"} },
    {"f", {"q", "r", "s", "t", "u", "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9"} },
    {"g", {"s", "t", "u", "v", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9"} },
    {"h", {"u", "v", "w", "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9"} },
    {"i", {"w", "x", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9"} },
    {"j", {"y", "z", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "g1", "k1", "j9"} },
    {"k", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"l", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"m", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"n", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"o", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"p", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"q", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"r", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"s", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"t", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"u", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"v", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"w", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"x", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"y", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"z", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"1", {"a1", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"2", {"i1", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"3", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"4", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"5", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"6", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"7", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"8", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"9", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"a1", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"a2", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"a3", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"a4", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"a5", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"a6", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"a7", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"a8", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"a9", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"b1", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"b2", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"b3", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"b4", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"b5", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"b6", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"b7", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"b8", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"b9", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"c1", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"c2", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"c3", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"c4", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"c5", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"c6", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"c7", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"c8", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"c9", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"d1", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"d2", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"d3", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"d4", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"d5", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"d6", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"d7", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"d8", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"d9", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"e1", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"e2", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"e3", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"e4", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"e5", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"e6", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"e7", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"e8", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"e9", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"f1", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"f2", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"f3", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"f4", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"f5", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"} },
    {"f6", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"f7", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"f8", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"f9", {"a", "b", "c", "d", "e", "f", "g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9"} },
    {"g1", {"a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8", "g9", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"g2", {"g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8", "g9", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"g3", {"f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8", "g9", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"g4", {"g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8", "g9", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"g5", {"g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8", "g9", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"g6", {"g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8", "g9", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"g7", {"g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8", "g9", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"g8", {"g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8", "g9", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"g9", {"g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8", "g9", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"h1", {"g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8", "g9", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"h2", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"h3", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"h4", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"h5", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"h6", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"h7", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"h8", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"h9", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"i1", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"i2", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"i3", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"i4", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"i5", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"i6", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"i7", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"i8", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"i9", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"j1", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"j2", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"j3", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"j4", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"j5", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"j6", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"j7", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"j8", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"j9", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} },
    {"k1", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9"} },
    {"k2", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9"} },
    {"k3", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9"} },
    {"k4", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9"} },
    {"k5", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9"} },
    {"k6", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9"} },
    {"k7", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9"} },
    {"k8", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9"} },
    {"k9", {"j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9"} }
}; 

unordered_map<string, list<string> > sparse =
{
    {"A", {"B", "Z"} },
    {"B", {"C", "z"} },
    {"C", {"D", "a"} },
    {"D", {"E", "A"} },
    {"E", {"F", "m"} },
    {"F", {"G", "M"} },
    {"G", {"H"} },
    {"H", {"I"} },
    {"I", {"J"} }, 
    {"J", {"K"} },
    {"K", {"L"} },
    {"L", {"M"} },
    {"M", {"N"} },
    {"N", {"O"} },
    {"O", {"P"} },
    {"P", {"Q"} },
    {"Q", {"R"} },
    {"R", {"S"} },
    {"S", {"T", "B"} },
    {"T", {"U"} },
    {"U", {"V"} },
    {"V", {"W"} },
    {"W", {"X"} },
    {"X", {"Y"} },
    {"Y", {"Z"} },
    {"Z", {"a"} },
    {"a", {"b"} },
    {"b", {"c"} },
    {"c", {"d"} },
    {"d", {"e"} },
    {"e", {"f"} },
    {"f", {"g"} },
    {"g", {"h"} },
    {"h", {"i"} },
    {"i", {"j"} },
    {"j", {"k"} },
    {"k", {"l"} },
    {"l", {"m"} },
    {"m", {"n"} },
    {"n", {"o"} },
    {"o", {"p"} },
    {"p", {"q", "b"} },
    {"q", {"r"} },
    {"r", {"s"} },
    {"s", {"t"} },
    {"t", {"u"} },
    {"u", {"v"} },
    {"v", {"w"} },
    {"w", {"x"} },
    {"x", {"y"} },
    {"y", {"z"} },
    {"z", {"A"} },
}; 

#endif
