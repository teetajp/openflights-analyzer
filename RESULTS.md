**CS 225 Team Scallywags Project Results**

**Teetajp2-swg3-eliww2-zanew2**

# Summary

We have managed to successfully implement a graph data structure using an adjacency matrix that can read properly formatted data, load said data into a graph, and run BFS traversals, Dijkstra's algorithm, and the PageRank algorithm on the graph. We used this program in order to analyze the OpenFlights dataset by creating a weighted directed graph where the nodes represent airports, the edges represent flights between the airports, and the weights represent the number of stops for each flight. 

In running our program on the OpenFlights dataset, we were able to determine the routes between airports that minimize both layovers and stops; in addition, with the help of PageRank, we were able to determine which airports act as hubs and allow for the greatest ease of travel through their number of flights and their connections to other busy airports. This information is useful not only for optimizing flights, but because it gives us insights into the areas surrounding the airports. Higher PageRank rankings and shorter paths indicate that the area surrounding an airport is very likely to be metropolitan, while lower PageRank rankings and longer paths are a likely sign of airports either being underfunded or in places that don't recieve much traffic for one reason or another.

Overall, we are very happy with the results of our project. Our program is very easy to use, and offers useful insight into how individual airports relate to each other and to the worldwide network of airports they are a part of.

# Our Results 

Our graph implementation takes two data files - one for nodes and one for edges - as input, and initializes a graph using the two files.     
Our BFS traversal takes a source node and destination node as input, as well as a file to which the full traversal is written. Through this algorithm, we are able to find the shortest unweighted path between any two airports provided such a path exists. This information is useful for minimizing layovers, as it tells you the route from one airport to another with the lowest amount of flights. In addition, the full traversal (found in BFS.txt) allows one to take a look at the number of flights between the source airport and every other airport, which is a nice visualization of how close the source is to the rest of the airports. We were pleased with our BFS implementation, as it runs quite effciently (though, due to our use of the adjacency matrix implementation, it does not run as fast as theoretically possible).    
Our implementation of Dijkstra's algorithm takes a source node and a destination node as input as well, as well as a file to which the shortest weighted path between the source and every other airport can be found (in DJ.txt). The weighted distance as well as the shortest weighted path between the source and destination is printed to terminal. This algorithm is useful for minimizing the amount of stops in a series of flights; unfortunately, however, most of the flights in our OpenFlights data file had 0 stops, so the output was quite similar to the output of BFS. In general, especially on a data set with more weightings, this algorithm can be quite useful to minimize stops on flight routes. This implementation ran efficiently as well, though again it was slower than is theoretically possible if we were to use a different graph implementation.    
Finally, our implementation of PageRank took only a file to write output to as its input. This algorithm does not need specific nodes as input because it runs on the entire set of nodes. The results of this algorithm were useful for seeing which airports are the busiest/most "important". The results were as we expected, with Hartsfield-Jackson (ATL) and O'Hare (ORD) being in the top three. We were happy with the efficiency of this implementation; all three of our algorithms ran in under 40 seconds, which for a graph of over 3000 nodes and 60000 edges we were quite happy with. The complete ranking of airport can be found in PageRank.txt for reference.


# Testing and proving results

To confirm that we successfully created the graph and algorithms, follow the instructions in the readme file in order to run and test our program. 

# Conclusion and Discoveries

We believe we were able to hit all of our goals on runtime with the longest being potentially O(N^2). It 
was interesting to learn about the differences in these algorithms and how they traverse the graph and
this led us to do more research on different ways to achieve a goal. One thing that we discovered was 
that since few of the edges were weighted more than by one, that our results were very similar which 
shows how much different a similar looking graph can look but if it has different edge weights it can 
yield extremely different results. In the end we were able to accomplish all of our goals put forward in 
the beginning as well as go on to learn more about traverals and graphs that we can find useful in the 
future.
