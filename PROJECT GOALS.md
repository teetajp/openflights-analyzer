**CS 225 Team Scallywags Project Goals**

**Teetajp2-swg3-eliww2-zanew2**

Say you currently live somewhere far away from any major airline hubs, but you’ve just taken a job that lets you live anywhere but requires you to travel a lot. You hate layovers, and don’t want to make several connections every time you have to travel, so you decide to move to a city with a major airport so that you can minimize the amount of layovers you’ll have when travelling. Assuming you live in the year 2014, we can determine which cities/airports act as airline hubs by implementing the PageRank algorithm on the OpenFlights dataset. In addition to this, we can also determine the minimum number of flights it takes to get to every airport in the world from a given airport, as well as the set of flights from said airport to every airport in the world with the least number of total stops, by implementing a breadth-first search and shortest path algorithm on the dataset, which allows one to minimize either layovers or stops. The graph constructed from the dataset will be directed and weighted, with airports acting as nodes and flights acting as directed edges which are weighted by the number of stops. However, only the shortest path algorithm will need to take into account the weighting of the flights/edges. This is because PageRank and BFS are only concerned with the number of flights going in/out of airports, rather than the number of stops of each flight, while the shortest path algorithm must determine the route with minimum stops from one airport to another. Therefore, we must construct a directed and weighted graph from the dataset, and then implement all three algorithms to work with this graph, although two of the three will not need to take into account the weights of the edges.

**Dataset Acquisition & Processing**

We are using the OpenFlights/Airline Route Mapper Route Database. We will download routes.dat, the file in which the route data is contained, as a csv file and import it into StataBE, the software we are using for preprocessing. Each line of data corresponds to a certain flight and has eight comma separated values: the airline, airline ID, source airport, source airport ID, destination airport, destination airport ID, codeshare value, number of stops, and equipment. For example, here are some sample data entries:

[

BA,1355,SIN,3316,LHR,507,,0,744 777

BA,1355,SIN,3316,MEL,3339,Y,0,744

TOM,5013,ACE,1055,BFS,465,,0,320

]

We are only interested in three of these variables: source airport, destination airport, and number of stops. We will drop the variables deemed unnecessary using the “drop varlist” command in Stata. The meaning of the three variables of note is as follows:


|**Variable**|**Meaning**|
| :- | :- |
|Source Airport|The identifying code for the source airport of the flight|
|Destination Airport|The identifying code for the destination airport of the flight|
|Number of Stops|The number of stops on the flight (“0” if direct flight)|

After deleting the unnecessary variables, we will run the “misstable summarize” command to identify any missing values and either use the “fill varlist, forward/baseline” command if the variable containing the missing values is enduring (can be determined by previous or future values) or the “replace” command (replacing with null) otherwise. We will then export the file as a json and access it in a C++ text editor. Each line of data will be seven characeters, with chars 0-2 being the code for the source airport, chars 3-5 being the code for the destination airport, and char 6 being the number of stops. From this routes.txt file we will also construct an airports.txt file consisting of every airport that has a flight going into/out of it, and use this file in order to initialize and maintain a list of the nodes for our graph. Each line of this file will be three chars, with each line corresponding to the code for an airport.

To construct a graph from this dataset, we will use the source and destination airports as nodes. A source and destination airport will be connected by a directed edge if there is a route (line of data) between the two airports. The direction of the edge is determined by which airport is the source and which is the destination. Each edge will be weighted by the number of stops. We plan on using the adjacency matrix representation for our graph.


**Algorithms**

We plan to implement a breadth-first search algorithm on the OpenFlights dataset, as well as Dijkstra’s algorithm and the PageRank algorithm.

For the BFS algorithm, the input will be the airport from which you want to find the distance of all other airports, with “distance” in our case indicating the number of flights it would take to get from the input airport to a destination airport. With the airports acting as nodes, and the flights between airports acting as edges, our algorithm will begin at the chosen airport and traverse the graph while noting the distance of each traversed node (airport) from the starting node (airport). Though our graph will be directed rather than undirected, because a flight explicitly goes from one airport to another, this will not be an issue for two reasons. The first is that in the vast majority of cases, if there is a flight from one airport to another, there is a flight back, and the second is that if the BFS algorithm is correctly implemented for an undirected graph, it takes very little modification to make it work for a directed graph. From the spanning tree determined by the BFS traversal, we can determine a shortest path from each airport to the starting airport, as well as the distance between each airport and the starting airport. Our target benchmark is O(F), where F is the number of flights. BFS algorithms run in O(V + E) time, where V is the number of vertices and E is the number of edges, but because there are so many more flights than there are airports, O (A + F), where A is the number of airports, simplifies to O(F).

For Dijkstra’s algorithm, the input will be the two airports between which you would like to find the shortest path, with the shortest path representing the flight or series of flights with the lowest number of total stops. Similarly to the BFS implementation, the fact that the graph is directed will only have minor effects on our implementation of Dijkstra’s algorithm. Unlike the BFS implementation, however, this implementation needs to take into account the weighting of the graph. The output will be a list of edges that constitute the shortest weighted path between two nodes, which corresponds to the route from one airport to another that minimizes the number of stops. The output will be a list of the edges that constitute the shortest path between the two airports. Our target benchmark is O(F \* log(A)), because Dijkstra’s algorithm runs in O(A \* log(A) + F \* log(A)) time, which, because A << F, simplifies to O(F \* log(A)).

For the PageRank algorithm, the inputs are a list of the nodes (airports) and corresponding edges (flight routes to/from those airports). Each route is directional. The output is a probability distribution where the higher the probability/rank an airport is assigned, the more “important” the airport is. The rank of each airport is determined by how many flights come into it and the rank of the airports from which the flights originate. One important note is that this algorithm only takes into consideration flights going into an airport, rather than flights going out of it. However, because the majority of flights going into an airport have corresponding flights going out of an airport, this will have a negligible effect on determining which airports act as hubs. The running time is O(A + F) where A is the number of nodes (airports) and F is the number of edges (flight routes), but because there are so many more flights than there are airports, this simplifies to O(F).

**Timeline**

November 28th - Finish project proposal, begin data processing

December 2nd - Finish data processing and implementing BFS algorithm

December 8th - Finish implementing Dijkstra’s algorithm

December 10th - Finish implementing PageRank algorithm

December 12th - Finish writing development and results, and work on final presentation

December 13th - Finish and record final presentation
