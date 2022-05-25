#include "../src/graph.h"
#include "../src/node.h"
#include "../src/edge.h"
#include "../src/pagerank.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "../catch/catch.hpp"

using Catch::Approx;

/** Shared variables */
const string airports = "../data/airports.txt";
const string routes = "../data/routes.txt";

TEST_CASE("Graph Construction", "[graph]") {
    // This section of code is reran for each section.
    Graph ourGraph = Graph(airports, routes);

    SECTION("testConstructor", "confirm constructor properly initializes node list, matrix, and edge list") {
        REQUIRE(ourGraph.getNodeCount() == 3425);
        REQUIRE(ourGraph.getNodes().size() == 3425);
        REQUIRE(ourGraph.getEdges().size() == 67663);
    }
    SECTION("testIsAdjacent", "test that self edges don't exist, that edges are tracked properly in matrix") {
        REQUIRE(ourGraph.isAdjacent("GYD", "NBC") == true);
        REQUIRE(ourGraph.isAdjacent("COO", "OUA") == true);
        REQUIRE(ourGraph.isAdjacent("TPP", "TPP") == false);
        REQUIRE(ourGraph.isAdjacent("TUG", "ORD") == false);
    }
    SECTION("testGetNodes", "test to ensure all nodes are added") {
        vector<Node> nodeVector = ourGraph.getNodes();
        REQUIRE(nodeVector.at(21).IATAcode.compare("ABX") == 0);
        REQUIRE(nodeVector.at(2169).IATAcode.compare("PAP") == 0);
        REQUIRE(nodeVector.at(3424).IATAcode.compare("ZYL") == 0);
    }
    SECTION("testGetEdges", "test to ensure all edges are added") {
        vector<Edge> edgeVector = ourGraph.getEdges();
        REQUIRE(edgeVector.at(67662).source_.compare("OSS") == 0);
        REQUIRE(edgeVector.at(67662).dest_.compare("FRU") == 0);
        REQUIRE(edgeVector.at(67662).weight_ == 0);
    }

    SECTION("test insertions", "test insertNode and insertEdge to make sure they do what they're supposed to") {
        ourGraph.insertEdge("JZH", "ORD", 7);
        vector<Edge> incidentEdgeVector2 = ourGraph.incidentEdges("JZH");
        vector<Edge> edgeVector2 = ourGraph.getEdges();
        REQUIRE(incidentEdgeVector2.at(incidentEdgeVector2.size() - 3).source_.compare("JZH") == 0);
        REQUIRE(edgeVector2.at(edgeVector2.size() - 1).weight_ == 7);
        REQUIRE(edgeVector2.size() == 67664);
        ourGraph.insertNode("OOGLY BOOGLY");
        vector<Node> nodeVector2 = ourGraph.getNodes();
        REQUIRE(nodeVector2.size() == 3426);
        REQUIRE(nodeVector2.at(nodeVector2.size() - 1).IATAcode.compare("OOGLY BOOGLY") == 0);
        ourGraph.insertEdge("JZH", "ORD", 7);
        ourGraph.insertEdge("JZH", "ORD", 7);
        ourGraph.insertEdge("JZH", "ORD", 7);
        ourGraph.insertEdge("JZH", "ORD", 7);
        vector<Edge> edgeVector3 = ourGraph.getEdges();
        REQUIRE(edgeVector3.size() == 67668);
    }

    SECTION("test getDegree", "confirm for a given node that the degree is correct") {
        REQUIRE(ourGraph.getDegree("JZH") == 10);
    }
}


TEST_CASE("BFS Test", "confirm that output file created by BFS matches what is expected") {
    Graph ourGraph = Graph(airports, routes);
    ourGraph.BFS("ORD", "AAE", "testBFSoutput.txt");
    REQUIRE(7==7);
    //just visually ensure that testBFSoutput.txt is correct.
    //ctrl + f a given node and check that the distance is as expected by comparing to correctBFSoutput.txt
    //this test used to make sure we didn't accidentally break anything while editing code, and it assumes that the version of BFS we had when we made correctBFSoutput.txt was correct
}

TEST_CASE("Dijkstra Test", "confirm that output file created by DJ matches what is expected") {
    Graph ourGraph = Graph(airports, routes);
    ourGraph.dijkstras("ABQ", "AUY", "testDJoutput.txt");
    REQUIRE(7==7);
    //just visually ensure that testDJoutput.txt is correct.
    //ctrl + f a given node and check that the distance/path is as expected by comparing to correctDJoutput.txt
    //this test used to make sure we didn't accidentally break anything while editing code, and it assumes that the version of dijkstra's we had when we made correctDJoutput.txt was correct
}

TEST_CASE("PageRank Test", "[pagerank]") {
    SECTION("Constructor: turn given adjacency matrix into a Markov Matrix") {
        SECTION("Transpose the matrix so that every element M[i][j] is at M[j][i]") {
            vector<vector<int>> adjMatrix = {{5, -1, 9},    // -> [5, 3, -1] -> [?, ?, 0]
                                            {3, -1, -1},    // -> [-1, -1, 2] -> [0, 0, ?]
                                            {-1, 2, 1}};   // -> [9, -1, 1] -> [?, 0, ?]
            PageRank pr(adjMatrix, 1.0);
            vector<vector<double>> matrix = pr.getMatrix();
            // Test that a value got transposed by checking if its new position is non-zero
            // as we're just testing transpose not normalize in this section
            REQUIRE(matrix[0][0] != 0.0);
            REQUIRE(matrix[0][1] != 0.0);
            REQUIRE(matrix[0][2] == 0.0);
            REQUIRE(matrix[1][0] == 0.0);
            REQUIRE(matrix[1][1] == 0.0);
            REQUIRE(matrix[1][2] != 0.0);
            REQUIRE(matrix[2][0] != 0.0);
            REQUIRE(matrix[2][1] == 0.0);
            REQUIRE(matrix[2][2] != 0.0);
        }
        SECTION("Normalization: for each column, values sum up to 1.") {
            SECTION("All nodes have outgoing edge(s)") {
                // Still need to input a matrix in pre-transposed form
                vector<vector<int>> adjMatrix = {{-1, 3, 5}, // -> [0, 6, 0] -> [0, 0.33, 0]
                                                {6, 2, 9}, // -> [3, 2, 4] -> [0.5, 0.33, 1.0]
                                                {-1, 4, -1}}; // -> [5, 9, 0] -> [0.5, 0.33, 0]
                PageRank pr(adjMatrix, 1.0);
                vector<vector<double>> matrix = pr.getMatrix();
                REQUIRE_THAT(matrix[0], Approx(vector<double>{0, 0.33333, 0}).epsilon(0.01));
                REQUIRE_THAT(matrix[1], Approx(vector<double>{0.5, 0.33333, 1.0}).epsilon(0.01));
                REQUIRE_THAT(matrix[2], Approx(vector<double>{0.5, 0.33333, 0.0}).epsilon(0.01));
            }
            SECTION("Sinks (nodes w/ no outgoing edge): set each element in column to 1 / N") {
                vector<vector<int>> adjMatrix = {{3, 3, -1}, // -> [3, 7, 0] -> [0.5, 0.5, 0.333]
                                                {7, -1, 9}, //   -> [3, 0, 0] -> [0.5, 0.0, 0.333]
                                                {-1, -1, -1}}; // -> [0, 9, 0] -> [0.0, 0.5, 0.333]
                PageRank pr(adjMatrix, 1.0);
                vector<vector<double>> matrix = pr.getMatrix();
                REQUIRE_THAT(matrix[0], Approx(vector<double>{0.5, 0.5, 0.333}).epsilon(0.01));
                REQUIRE_THAT(matrix[1], Approx(vector<double>{0.5, 0.0, 0.333}).epsilon(0.01));
                REQUIRE_THAT(matrix[2], Approx(vector<double>{0.0, 0.5, 0.333}).epsilon(0.01));
            }
            SECTION("Damping Factor: check if applied correctly") {
                vector<vector<int>> adjMatrix = {{3, 3, -1}, // -> [0.5, 0.5, 0.333] -> [0.475, 0.475, 0.333]
                                                {7, -1, 9}, //   -> [0.5, 0.0, 0.333] -> [0.475, 0.05, 0.333]
                                                {-1, -1, -1}}; // -> [0.0, 0.5, 0.333] -> [0.05, 0.475, 0.333]
                // M = (d * M + (1 - d) / N)
                PageRank pr(adjMatrix, 0.85); // Set damping to 0.85, which is the most common damping value
                vector<vector<double>> matrix = pr.getMatrix();
                REQUIRE_THAT(matrix[0], Approx(vector<double>{0.475, 0.475, 0.333}).epsilon(0.01));
                REQUIRE_THAT(matrix[1], Approx(vector<double>{0.475, 0.05, 0.333}).epsilon(0.01));
                REQUIRE_THAT(matrix[2], Approx(vector<double>{0.05, 0.475, 0.333}).epsilon(0.01));
            }
        }
    }
    SECTION("Power Iteration: multiply the matrix to compute the rank eigenvector") {
        // Note: function only works when matrix is n x n and state vector is n x 1
        SECTION("Dot product is correct (perform one iteration)") {
            vector<vector<double>> matrix = {{0.5, 0.35, 0.1},
                                             {0.5, 0.05, 0.7},
                                             {0.0, 0.60, 0.2}};
            vector<double> initial_state = {2, 4, 0.5};
            vector<double> final_state = PageRank::powerIteration(matrix, initial_state, 1);
            REQUIRE_THAT(final_state, Approx(vector<double>{2.45, 1.55, 2.5}).epsilon(0.001));
        }
        SECTION("Correct results for multiple iterations (hand computed)") {
            vector<vector<double>> matrix = {{0.5, 0.35, 0.1},
                                             {0.5, 0.05, 0.7},
                                             {0.0, 0.60, 0.2}};
            vector<double> initial_state = {2, 4, 0.5};
            vector<double> final_state = PageRank::powerIteration(matrix, initial_state, 3);
            REQUIRE_THAT(final_state, Approx(vector<double>{2.220125, 2.162375, 2.1175}).epsilon(0.00001));
        }
        SECTION("Known convergence value: different initial state should reach the same final state") {
            vector<vector<double>> matrix = {{0.3, 0.1},
                                            {0.7, 0.9}};
            REQUIRE_THAT(PageRank::powerIteration(matrix, vector<double>{1.0 , 0.0}, 15),
                Approx(vector<double>{0.125, 0.875}).epsilon(0.00001));
            REQUIRE_THAT(PageRank::powerIteration(matrix, vector<double>{0.5 , 0.5}, 50),
                Approx(vector<double>{0.125, 0.875}).epsilon(0.00001));
        }
    }
}