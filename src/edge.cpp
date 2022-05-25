#include "edge.h"

Edge::Edge() {
    source_ = "";
    dest_ = "";
    weight_ = -1;
}

 Edge::Edge(string source, string dest, int weight) {
    source_ = source;
    dest_ = dest;
    weight_ = weight;
 }