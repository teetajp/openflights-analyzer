#pragma once
#include <string>

using std::string;

//class used for maintaining a vector of all the nodes in the graph

class Node {
    public:
        //default constructor
        Node();

        //constructs a node with the given code
        Node(string code);

        //member variables
        string IATAcode;
        int ID; //each airport will be assigned a number from 1 to 3425
};