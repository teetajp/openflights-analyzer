#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "graph.h"

using namespace std;




/* All methods and tests can be run using simple command line arguments,
    which include the ability to alter or adjust the input data and output location
*/

//  This will run with "./main <src airport> <dest airport> <output filename>" or just "./main"
//  However it can take just 1, 2, 3, or all 4 arguments and ask for the rest
int main (int argc, char *argv[]) {
    string airports = "../data/airports.txt";
    string routes = "../data/routes.txt";
    Graph ourGraph = Graph(airports, routes);

    string source = (argc > 1) ? argv[1] : "";
    string dest = (argc > 2) ? argv[2] : "";
    
    while (!ourGraph.nodeExists(source)) {
        cout << "Source airport: ";
        cin >> source;
        
        if (source.length() != 3 || !ourGraph.nodeExists(source)) {
            cout << "Please input a valid IATA code. Check airports.txt for a list of valid IATA codes. Codes must be entered in uppercase." << endl;
        }
    }
    
    while (!ourGraph.nodeExists(dest)) {
        cout << "Destination airport: ";
        cin >> dest;

        if (dest.length() != 3 || !ourGraph.nodeExists(dest)) {
            cout << "Please input a valid IATA code. Check airports.txt for a list of valid IATA codes. Codes must be entered in uppercase." << endl;
        }
    }


    cout << "You have selected " << source << " as your source airport and " << dest << " as your destination airport." << endl << endl;
    cout << "Now running a BFS traversal to determine the unweighted distance and shortest unweighted path between source and destination." << endl;
    
    if (argc > 3) {
        ourGraph.BFS(source, dest, argv[3]);
        cout << "BFS has finished. Please open " << argv[3] << " to see the results of the traversal." << endl << endl;

        cout << "Now running Dijkstra's Algorithm to determine the shortest weighted path between source and destination." << endl;
        ourGraph.dijkstras(source, dest, "DJ.txt");
        cout << "Dijkstra's Algorithm has finished. Please open " << argv[3] << " to see the path with the least amount of stops from " << source << " to each airport." << endl << endl;

        cout << "Now running PageRank to determine the most importance airports." << endl;
        ourGraph.pagerank("PageRank.txt");
        cout << "PageRank has finished. Please open " << argv[3] << " to see airport codes along with their PageRank score in descending order." << endl; 
    } else {
        ourGraph.BFS(source, dest, "BFS.txt");
        cout << "BFS has finished. Please open BFS.txt to see the results of the traversal." << endl << endl;

        cout << "Now running Dijkstra's Algorithm to determine the shortest weighted path between source and destination." << endl;
        ourGraph.dijkstras(source, dest, "DJ.txt");
        cout << "Dijkstra's Algorithm has finished. Please open DJ.txt to see the path with the least amount of stops from " << source << " to each airport." << endl << endl;

        cout << "Now running PageRank to determine which airports are the largest hubs (in terms of their importance determined by PageRank)." << endl;
        ourGraph.pagerank("PageRank.txt");
        cout << "PageRank has finished. Please open PageRank.txt to see airport codes along with their PageRank score in descending order." << endl; 
    }
    return 0;
}