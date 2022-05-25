#pragma once
#include <string>

using std::string;

//class used for maintaining a vector of all the edges in the graph

class Edge {
    public:
        //default constructor
        Edge();

        //constructs an edge from source to dest with the given weight
        Edge(string source, string dest, int weight);

        //member variables to identify the edge
        string source_;
        string dest_;
        int weight_;

};