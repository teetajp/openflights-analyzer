# CS225 Team Scallywags Final Project - Graph Implementation and Algorithms with OpenFlights
Group:    
Spencer Gallagher - swg3    
TJ Pavaritpong - teetajp2    
Zane Weinglass - zanedw2    
Eli Wagner - eliww2    

# Code Location    
      
https://github-dev.cs.illinois.edu/cs225-fa21/swg3-teetajp2-zanedw2-eliww2       
   
Our code base can be found at the above link (if you are reading this file, you are likely currently there). Our development log, project goals, results, presentation, and team contract can be found in this repository. The catch and test folders contain all the files related to testing our code. The data folder contains the code we used for preprocessing, as well as the airports.txt and routes.txt files that are used to construct our graph. The src folder contains the graph implementation. Within graph.h and graph.cpp are both the graph implementation and the implementation of the three graph algorithms (BFS, Dijkstra's, and PageRank). The node and edge helper classes can be found within src as well. The Makefile is in src, and is used to convert main.cpp into an executable which is used to demonstrate the implemented graph algorithms. The results of the algorithms are both written to txt files contained within src and outputted to terminal.
    
# Building and Running the Project on EWS
    
1. Clone our repository to your EWS and navigate to the cloned directory
2. Navigate to the src folder using "cd src" on the terminal
3. Type the following commands into terminal:
    
```
$ make        
$ ./main      
```  
      
4. You will be prompted to enter a source airport and a destination airport. See airports.txt within the data folder for a list of IATA codes you can enter.
5. BFS will be run using the inputted source and destination airports. The results of the traversal will be written to src/BFS.txt. The information on the shortest unweighted
path between the source and destination airport will be outputted to terminal. Next, Dijkstra's will be run on the two airports, with info on the shortest weighted path between source and destination being outputted to terminal, and a list of shortest unweighted paths between the source and every airport being written to src/DJ.txt. Finally, PageRank will run, though this algorithm does not use the source and destination codes inputted; rather, it always runs on the graph, and prints to terminal the ten most important airports. A complete list of the airports sorted by importance can be found in src/PageRank.txt.
6. To run our code with data of your own (that is formatted as specified in PROJECT GOALS.md), add your txt files to the repository, open main.cpp, and replace     
```   
string airports = "../data/airports.txt";   
string routes = "../data/routes.txt";   
```  
with
```   
string airports = "../data/YOURNODEFILE.txt";   
string routes = "../data/YOUREDGEFILE.txt";   
```   
# Running the Test Suite
To run our test suite, type the following commands into terminal:
      
```
$ make test      
$ ./test      
```
      
This test suite runs tests ensuring that our graph implementation works as expected, and runs tests to confirms the output of each of the three algorithms is as expected.

https://youtu.be/glYbJgCGHRk
