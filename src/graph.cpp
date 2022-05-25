/**
 * @file graph.cpp
 * Implementation of a graph class.
 */

#include "graph.h"
#include "pagerank.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

Graph::Graph() {
    //initialize nodeCount to 0, create empty node vector and adjacency matrix
    vector<vector<int>> adj;
    vector<Node> nodes1;
    vector<Edge> edges1;
    adjMatrix = adj;
    nodes = nodes1;
    edgeList = edges1;
    nodeCount = 0;
}

Graph::Graph(string nodeFile, string edgeFile) {
    //initialize nodeCount to zero
    nodeCount = 0;

    //put the list of nodes into myNodeFile
    ifstream myNodeFile;
    myNodeFile.open(nodeFile);
    
    //initialize nodes vector with each node in nodeFile, initialize the IDmap and stringMap with proper ID number/IATA code pairs
    while (myNodeFile.good()) {
        string line;
        getline(myNodeFile, line);
        Node newNode(line);
        newNode.ID = nodeCount;
        nodes.push_back(newNode);
        IDmap.insert(std::pair<string, int>(line, nodeCount));
        stringMap.insert(std::pair<int, string>(nodeCount, line));
        nodeCount++;
    }
    
    //initialize square adjacency matrix, every cell initialized with -1 to indicate no edge between nodes
    for (int i = 0; i < nodeCount; i++) {
        vector<int> newb(nodeCount, -1);
        adjMatrix.push_back(newb);
    }
    
    //put list of edges into myEdgeFile
    ifstream myEdgeFile;
    myEdgeFile.open(edgeFile);
    
    while(myEdgeFile.good()) {

        //load each line of edge file into variable line
        string line;
        getline(myEdgeFile, line);
        
        
        //check for bad data, extract the code for source node, code for destination node, and the stop count (weight) from the line
        if (line.length() != 7) {
            continue;
        }
        string source = line.substr(0, 3);
        string destination = line.substr(3, 3);
        string weightString = line.substr(6, 1);

        //convert the weightString to int stored in weight
        stringstream spoop(weightString);
        int weight = 0;
        spoop >> weight;
        
        //find the ID number of the two nodes in the edge. The ID number corresponds to the indices of each node within the adjacency matrix
        int sourceID = Graph::stringToID(source);
        int destID = Graph::stringToID(destination);

       
        
        
        //set value of cell of adjacency matrix to equal number of stops (0 or 1), indicating an edge between the two nodes
        //first index of adj. matrix always source, second index always destination
        //note that we do not also set adjMatrix[destID][sourceID] because graph is directed
        adjMatrix[sourceID][destID] = weight;   
        
        Edge edgy(source, destination, weight);
        edgeList.push_back(edgy);
        
    }
    //close the files
    myEdgeFile.close();
    myNodeFile.close();
}


bool Graph::isAdjacent(std::string source, std::string dest) {
   //find the ID number of the two nodes. The ID number corresponds to the indices of each node within the adjacency matrix
    int sourceID = Graph::stringToID(source);
    int destID = Graph::stringToID(dest);

    //use the ID numbers to check the adjacency matrix to see if an edge exists from the source to the destination
    if (adjMatrix[sourceID][destID] != -1) {
        return true;
    }
    return false;
}


vector<Edge> Graph::incidentEdges(string source) {
    int sourceID = Graph::stringToID(source);
    string destName;
    vector<Edge> incidentEdgeList;
    int count = 0;

    //for each cell in the source's column in the adj Matrix, if there is a 0 or a 1, add edge to vector
    //in other words, for each node in the graph, if there is an edge to it from the source, add the edge to the vector
    for (int integer : adjMatrix[sourceID]) {
        
        if (integer != -1) {
            destName = IDtoString(count);
            Edge toAdd(source, destName, integer);
            incidentEdgeList.push_back(toAdd);
        }
        count++;
    }
    return incidentEdgeList;
}


void Graph::insertEdge(string source, string dest, int weight) {
    //find IDs of input codes, use the IDs to update adjacency matrix, add edge to the edge list
    int sourceID = Graph::stringToID(source);
    int destID = Graph::stringToID(dest);
    adjMatrix[sourceID][destID] = weight;
    Edge toAdd(source, dest, weight);
    edgeList.push_back(toAdd);
}


void Graph::insertNode(string code) {
    //assign new node an ID number and insert the ID/code pair into the node vector and maps
    Node newNode = Node(code);
    newNode.ID = nodeCount;
    nodes.push_back(newNode);
    IDmap.insert(std::pair<string, int>(code, nodeCount));
    stringMap.insert(std::pair<int, string>(nodeCount, code));
    nodeCount++;

    //add new vector to end of adjacency list, increasing that dimension by 1
    vector<int> newb(nodeCount - 1, -1);
    adjMatrix.push_back(newb);

    //add -1 to end of every vector, increasing other dimension by 1
    for (int i = 0; i < nodeCount; i++) {
        adjMatrix[i].push_back(-1);
    }   

    //we have now successfully increased each dimension of the adjacency matrix by 1 so that it matches the new number of nodes
}


 vector<Node> Graph::getNodes() {
     return nodes;
 }
 
 int Graph::getNodeCount() {
     return nodeCount;
 }

vector<Edge> Graph::getEdges() {
    return edgeList;
}

int Graph::getDegree(string source) {
    int count = 0;
    int sourceID = Graph::stringToID(source);
    //check adjacency matrix for incoming and outgoing edges
    for (int i = 0; i < nodeCount; i++) {
        if (adjMatrix[sourceID][i] != -1) {
            count++;
        }
        if (adjMatrix[i][sourceID] != -1) {
            count++;
        }
    }
    return count;
}

 bool Graph::nodeExists(string code) {
     //if the code doesn't have a corresponding ID then it is not in the graph
     if (IDmap.find(code) == IDmap.end()) {
         return false;
     } else {
         return true;
     }
 }

void Graph::BFS(string source, string dest, string BFSFile) {
    //initialize vectors that contain info on nodes - whether they've been visited, their distance from source, and who their parent node is
    vector<bool> beenVisited(nodeCount, false);
    vector<string> searchNodes;
    searchNodes.push_back(source);
    vector<int> distances(nodeCount, -1);
    vector<string> parents(nodeCount, "node not visited");

    //open output file that we plan to write to
    std::ofstream outputFile;
    outputFile.open(BFSFile);
    outputFile << "Results of BFS Traversal" << endl;
    outputFile << "Below is printed the unweighted distance of every node from source " << source << ", found using a BFS Traversal." << endl;
    beenVisited[stringToID(source)] = true;
    parents[stringToID(source)] = "source";
    distances[stringToID(source)] = 0;
    string current; 
    
    //the meat of the BFS search. This is the algorithm discussed in class. Each node is printed to the BFSFile along with its distance from the source.
    while (!searchNodes.empty()) {
        current = searchNodes[0];
        searchNodes.erase(searchNodes.begin());
        outputFile << current << " is a distance of " << distances[stringToID(current)] << " from the source airport " << source << endl;

        for (int i = 0; i < nodeCount; i++) {
            if (adjMatrix[stringToID(current)][i] != -1 && (!beenVisited[i])) {
                searchNodes.push_back(IDtoString(i));
                beenVisited[i] = true;
                distances[i] = distances[stringToID(current)] + 1;
                parents[i] = current;
            }
        }
    }
    //we print the shortest unweighted path between source and destination to terminal, or we declare no such path exists.
    if (distances[stringToID(dest)] != -1) {
        cout << "The destination airport " << dest << " is an unweighted distance of " << distances[stringToID(dest)] << " from the source airport " << source << "." << endl;
        cout << "To get from the source airport to the destination airport in the least amount of flights, take the following path in reverse:" << endl;
        string cur = dest;
        while (parents[stringToID(cur)].compare("source") != 0) {
            cout << cur << ", ";
            cur = parents[stringToID(cur)];
        }
        cout << source << "." << endl;
    } else {
        cout << "The destination airport " << dest << " cannot be reached from the source airport " << source << ". Consider a boat." << endl;
    }
    

    outputFile << endl;
    outputFile << "The following airports are not reachable from the source airport " << source << ":" << endl;
    outputFile << endl;

    //traverse all nodes that haven't yet been visited
    for (int i = 0; i < nodeCount; i++) {
        if (!beenVisited[i]) {
            searchNodes.push_back(IDtoString(i));
            beenVisited[i] = true;
            distances[i] = 0;
            
            while (!searchNodes.empty()) {
                current = searchNodes[0];
                searchNodes.erase(searchNodes.begin());
                outputFile << current << endl;

                for (int j = 0; j < nodeCount; j++) {
                    if (adjMatrix[stringToID(current)][j] != -1 && (!beenVisited[j])) {
                        searchNodes.push_back(IDtoString(j));
                        beenVisited[j] = true;
                        distances[j] = distances[stringToID(current)] + 1;
                        parents[j] = current;
                    }
                }
            }
            outputFile << endl;
        }
        
    }


    outputFile.close();
    
}


void Graph::dijkstras(string source, string dest, string DJFile) {
     vector<bool> spt(nodeCount, false);
     vector<int> distances(nodeCount, INT_MAX);

     //parents vector used to determine shortest path from source to node
     vector<string> parents(nodeCount, "node not visited");

     distances[stringToID(source)] = 0;
     parents[stringToID(source)] = "source";

     //add each node to SPT in order of weighted distance from the source
     for (int i = 0; i < nodeCount; i++) {
         string toAdd = getMinimumNode(spt, distances);
         spt[stringToID(toAdd)] = true;

        //update distance and shortest path for every other node
        for (int j = 0; j < nodeCount; j++) {
            if(adjMatrix[stringToID(toAdd)][j] != -1) {
                if (!spt[j] && adjMatrix[stringToID(toAdd)][j] != INT_MAX) {
                    int newDist = adjMatrix[stringToID(toAdd)][j] + 1 + distances[stringToID(toAdd)];

                    if (newDist < distances[j]) {
                        distances[j] = newDist;
                        parents[j] = toAdd;
                    }
                }
            }
        }
     }
     //print the shortest path from source to dest to the terminal
     cout << "The destination airport " << dest << " is a weighted distance of " << distances[stringToID(dest)] << " from the source airport " << source << "." << endl;
     cout << "To get from the source airport to the destination airport in the least amount of stops, take the following path in reverse:" << endl;
    string cur = dest;
    while (parents[stringToID(cur)].compare("source") != 0) {
        cout << cur << ", ";
        cur = parents[stringToID(cur)];
    }
    cout << source << "." << endl;
     printDijkstra(source, distances, DJFile, parents);
 }

void Graph::pagerank(string output_path) {
    PageRank pr(adjMatrix);
    unsigned int t = 100; // number of iterations
    unsigned int num_to_print = 10; // number of airports to print on console
    vector<double> ranks = pr.computePageRank(t);

    vector<int> node_indexes(nodeCount);
    size_t n(0);
    // Put the values 0...nodeCount into node_indexes
    generate(begin(node_indexes), end(node_indexes), [&]{ return n++; });
    // Sort the indexes by descending order
    sort(begin(node_indexes), end(node_indexes),
        [&](int i1, int i2) { return ranks[i1] > ranks[i2]; } );

    cout << "The top 10 airports in descending order are: " << endl;
    for (size_t i = 0; i < num_to_print; i++) {
        cout << IDtoString(node_indexes[i]);
        if (i < num_to_print - 1) {
            cout << ", ";
        } else {
            cout << "." << endl;
        }
    }

    std::ofstream outputFile;
    outputFile.open(output_path);
    outputFile << "Results of PageRank (" << t << " power iterations)" << endl << endl << "Below is the list of airports sorted according to their importance determined by PageRank" << endl << endl;
    for (auto node_idx : node_indexes) {
        outputFile << "Rank of " << IDtoString(node_idx) << ": " << ranks[node_idx] << endl;
    }
}

int Graph::stringToID(string code) {
    return IDmap[code];
}

string Graph::IDtoString(int ID) {
    return stringMap[ID];
}

string Graph::getMinimumNode(vector<bool> spt, vector<int> distances) {
    int minDist = INT_MAX;
    string node = "";

    //find the node not currently in the shortest path tree that is closest to the source node.
    for (int i = 0; i < nodeCount; i++) {
        if (!spt[i] && distances[i] < minDist) {
            minDist = distances[i];
            node = IDtoString(i);
        }
    }
    return node;
}

 

 void Graph::printDijkstra(string source, vector<int> distances, string DJFile, vector<string> parents) {
    std::ofstream outputFile;
    outputFile.open(DJFile);
    outputFile << "Results of Dijkstra's Algorithm" << endl;
    outputFile << endl;
    outputFile << "Below is the weighted distance of each node from source " << source << ", found using Dijkstra's Algorithm." << endl;
    outputFile << endl;

    // Print weighted distance and path from source to node for each node to output file. If node is unconnected, state it is unconnected and move to next node.
    for (int i = 0; i < nodeCount; i++) {
        if (distances[i] == INT_MAX) {
            outputFile << source << " and " << IDtoString(i) << " are unconnected." << endl;
        } else {
            outputFile << "The weighted distance from " << source << " to " << IDtoString(i) << " is " << distances[i] << ". A flight from "  << source << " to " << IDtoString(i) << " has " << distances[i] << " stops."<< endl; 
            outputFile << "To minimize stops between " << source << " and " << IDtoString(i) << ", take the following path in reverse: ";
            string cur = IDtoString(i);
            while (parents[stringToID(cur)].compare("source") != 0) {
                outputFile << cur << ", ";
                cur = parents[stringToID(cur)];
            }
            outputFile << source << "." << endl;
        }
        
    }
 }