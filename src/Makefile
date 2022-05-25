EXENAME = main
OBJS = main.o graph.o node.o edge.o pagerank.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp graph.cpp graph.h
	$(CXX) $(CXXFLAGS) main.cpp	

graph.o: graph.h graph.cpp node.cpp node.h edge.h edge.cpp pagerank.h pagerank.cpp
	$(CXX) $(CXXFLAGS) graph.cpp

node.o: node.cpp node.h
	$(CXX) $(CXXFLAGS) node.cpp

edge.o: edge.cpp edge.h
	$(CXX) $(CXXFLAGS) edge.cpp

pagerank.o: pagerank.cpp pagerank.h
	$(CXX) $(CXXFLAGS) pagerank.cpp

ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1'. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

output_msg: ; $(CLANG_VERSION_MSG)

test: output_msg ../catch/catchmain.cpp ../tests/graph_tests.cpp graph.cpp node.cpp edge.cpp pagerank.cpp
		$(LD) ../catch/catchmain.cpp ../tests/graph_tests.cpp graph.cpp node.cpp edge.cpp pagerank.cpp $(LDFLAGS) -o test

.PHONY: output_msg

clean :
	-rm -f *.o .txt $(EXENAME) test