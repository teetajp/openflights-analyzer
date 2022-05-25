/**
 * @file graph.h
 * @brief Definition of a graph class.
 */

#pragma once

#include <vector>
#include "node.h"
#include "edge.h"
#include "pagerank.h"
#include <map>
using namespace std;
/**
 * Adjacency Matrix Graph: An adjacency matrix implementation of the graph data structure.
 *
 * @author team scallywags
 * @date Fall 2021
 */


class Graph
{
public:

  /**
   * @brief default constructor
   */
  Graph();


  /**
   * @brief constructs graph from list of nodes and list of weighted edges, formatted as specified in PROJECT GOALS.md
   * 
   * @param nodeFile - file containing each node to be added to graph (needs to match the nodes used in edgeFile)
   * @param edgeFile - file containing each weighted edge to be added to graph
   */
  Graph(string nodeFile, string edgeFile);


  /**
   * @brief check if two nodes (airports) are adjacent using their IATA codes
   * 
   * @param source - the IATA code of the source airport.
   * @param dest - the IATA code of the destination airport.
   * @return true if there is an edge going out of the source node and into the destination node
   * @return false if there is no such edge
   */
  bool isAdjacent(string source, string dest);


  /**
   * @brief retrieve all the outgoing edges from a specific node
   * 
   * @param source - the IATA code of the source airport.
   * @return a vector filled with Edge objects, which contains every edge going out of the source node. 
   * These objects contain the IATA codes for the source and destination airports
   * as well as the weight of the edge. The member variables are publically accessible.
   */
  vector<Edge> incidentEdges(string source);


  /**
   * @brief inserts and/or overwrites an edge into the graph
   * 
   * @param source - the IATA code of the source airport.
   * @param dest - the IATA code of the destination airport.
   * @param weight - the weight of the edge to be added
   */
  void insertEdge(string source, string dest, int weight);


  /**
   * @brief inserts a node into the graph
   * 
   * @param code - IATA code for the airport to be added to the graph
   */ 
  void insertNode(string code);


  /**
   * @brief retrieve every node in the graph
   * 
   * @return a vector filled with Node objects, which contains every node in the graph. These objects contain the 
   * IATA code for the airport and the ID number of the airport.
   * The ID number of the airport is used to access the proper index in the adjacency matrix.
   * The member variable are publically accessible.
   */
  vector<Node> getNodes();


  /**
   * @brief find the number of nodes in the graph
   * 
   * @return nodeCount
   */
  int getNodeCount();

  
  /**
   * @brief retrieve every edge in the graph
   * 
   * @return a vector filled with Edge objects, as described above, and which contains every edge in the graph
   */
  vector<Edge> getEdges();


  /**
   * @brief find the sum of the indegree and the outdegree of a given node
   * 
   * @param source - the IATA code of the source airport.
   * @return the number of edges directed into or out of the source airport
   */
  int getDegree(string source);


  /**
   * @brief check whether the inputted code corresponds to an existing node
   * 
   * @param source - the IATA code of the source airport.
   * @return true if the code corresponds to a node with the graph
   * @return false otherwise
   */
  bool nodeExists(string code);
  

  /**
   * @brief Traverse graph using BFS and find the shortest unweighted path between the source and destination airports
   * 
   * @param source - the IATA code of the source airport.
   * @param dest - the IATA code of the destination airport.
   * @param BFSFile - the file to which the traversal will be printed
   */
  void BFS(string source, string dest, string BFSFile);


  /**
   * @brief Find the shortest weighted path between the source and every airport using Dijkstra's algorithm (shortest path tree). Prints out the shortest path between
   * source and dest.
   * 
   * @param source - the IATA code of the source airport.
   * @param dest - the IATA code of the destination airport.
   * @param DJFile - the file to which the shortest weighted path for each node will be printed.
   */
  void dijkstras(string source, string dest, string DJFile);

  /**
   * @brief Rank airports by their importance based on the number of incoming flights
   *  using the PageRank algorithm
   * 
   * @param PRFile - the file to which the ranked airports will be printed
   */
  void pagerank(string PRFile);
  
private:

  //a vector containing every node in the graph
  vector<Node> nodes;

  //the adjacency matrix used to track whether edges are adjacent and what the weight of each edge is
  vector<vector<int>> adjMatrix;

  //keeps track of the number of nodes in the graph
  int nodeCount;

  //a vector containing every edge in the graph
  vector<Edge> edgeList;

  //converts IATA code to ID number
  int stringToID(string code);

  //converts ID number to IATA code
  string IDtoString(int ID);

  //maps IATA codes to ID numbers
  map<string, int> IDmap;

  //maps ID numbers to IATA codes
  map<int, string> stringMap;

  //Dijkstra helper function
  string getMinimumNode(vector<bool> spt, vector<int> key);

  //Dijkstra helper function
  void printDijkstra(string source, vector<int> distances, string DJFile, vector<string> parents);
};
