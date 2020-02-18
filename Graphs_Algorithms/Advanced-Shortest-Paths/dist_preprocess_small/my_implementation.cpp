#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <iostream>
#include <memory>
#include <cassert>

using namespace std;
class Edge {
    public:
    int vertex{};
    int cost{};
    int 

};

class Vertex {
    public:
    int numSC = 0;
    bool isContracted = false;
    int shortC = 0;
    int level = 0;
    long long importance = 0;

    Node() {};
    int numInEdges(

};

    vector<Edge> outEdges;
    vector<Edge> inEdges;



//The method to correctly calculate shortcover is sighlty complicated. Need a parameter in each vertex to know if it has an new shortcut edge from/to.
//Then we calculate the number of neighbours of a vertex who have these parameter set.
    int calculateImportance(int v, int numShortcuts) {
        int edgeDiff = numSC + numShortcuts - outgoing_edges[v].size() - incoming_edges[v].size();
        int contractedNeighbours = 0;
        for (int i = 0; i < outgoing_edges[v].size(); ++i) {
            int neighbour = outgoing_edges[v][i].second;
            if (contracted[neighbour])
                contractedNeighbours++;
        }

        for (int i = 0; i < incoming_edges[v].size(); ++i) {
            int neighbour = incoming_edges[v][i].second;
            if (contracted[neighbour])
                contractedNeighbours++;
        }

        int shortCover = 0;
        int importance = edgeDiff + 10 * contractedNeighbours + shortCover;
        return importance;
    }
    
    void setImportance(int v, int numShortcuts, int imp) {
        importance = imp;
        shortC += numShortcuts;
        numSC += numShortcuts;
    }


