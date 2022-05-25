Week of 11/1-11/7
- Created team contract
- Signed team contract

Week of 11/8-11/14
- Resigned team contract w/ our netIDs
- Submitted project proposal (rejected)

Week of 11/15-11/21
- Researched ideas for revised project proposal

Week of 11/22-11/28
- Thanksgiving Break
- Continued to research ideas and revise project proposal

Week of 11/29-12/5
- Submitted revised project proposal (approved)
- Assigned tasks to members
- Began preprocessing

Week of 12/6-12/13 (Deadline)
- Finished preprocessing of routes.dat into routes.txt
- Redid routes preprocessing to make data easily parsable
- added separate file, airports.txt, containing every airport code found in routes.txt for graph initialization purposes
- Added skeleton files and structure to the folder
- Implemented graph data structure using adjacency matrix that can create graphs from files formatted in
the same way as airports.txt and routes.txt
- Wrote test cases to confirm graph implementation works as expected
- Wrote makefile to turn our tests and main.cpp into executables
- Implemented BFS algorithm on graph implementation
- Reworked BFS to take a source and destination airport and write the distance and unweighted shortest path between the two to terminal, in addition to writing the traversal of the graph to BFS.txt
- Wrote functions in main to allow user to input a source and destination airport and recieve a BFS traversal using the source and destination
- Demoed graph implementation and BFS to our TA
- Reworked BFS to ensure that all nodes are traversed, including those not connected to the source node
- Implemented Dijkstra's algorithm to write the shortest weighted path between a source and destination airport to terminal and to write the shortest weighted path between the source and every node in the graph to DJ.txt.
- Added tests for Dijkstra's and updated function in main to utilize Dijkstra's in addition to BFS
- Create function to unweigh, transpose, and normalize this adjacency matrix implementation to make it work for PageRank
- Implemented PageRank algorithm that ranks each of the airport's importance based on the quality and number of incoming flights
- Tested and debugged PageRank using Catch2
- Wrote function to sort the PageRank results and save it to a file 
- Did a final organization of our code base
- Finished report and final presentation