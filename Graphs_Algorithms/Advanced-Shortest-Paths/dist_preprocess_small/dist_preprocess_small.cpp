#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <iostream>
#include <memory>
#include <cassert>
#include <unordered_map>
#include <fstream>

using namespace std;

//using Adj = vector<vector<Edge>>; 
using distMap = unordered_map<int, int> ;
static constexpr int INF = numeric_limits<int>::max() / 2;

class Graph {

public:
Graph() {
    read_stdin();
}

int get_n() { return N;}

//vector<Edge>& get_adjacent(int v, bool forward = true) {
//    if (forward) {
//        return outgoing_edges[v];
//    } else {
//        return incoming_edges[v];
//    }
//}

void preprocess() {
    //printEdges();
    initializeVertex();

    // Priority queue will store vertex and its importance with the least important node in the head
    StlHeap impQ;
    //Initialize impQ with default priorities
    for (int i = 0; i < N; ++i) {
        impQ.push(i, vertices[i].importance);
    }

    //impQ.print();

    while(!impQ.empty()) {
        int current = impQ.pop().vertex;
        vertices[current].edgeRank = cntRank++;
        vertices[current].contracted = true;

        //Find maximum incoming edge
        int inMax = 0;
        for (int i = 0; i < incoming_edges[current].size(); ++i) {
            if (incoming_edges[current][i].cost > inMax) 
                inMax = incoming_edges[current][i].cost;
        }

        //Find maximum outgoing edge
        int outMax = 0;
        for (int i = 0; i < outgoing_edges[current].size(); ++i) {
            if (outgoing_edges[current][i].cost > outMax) 
                outMax = outgoing_edges[current][i].cost;
        }

        
        //cout << "Vertex: " << current << " inMax, outMax: " << inMax << "," << outMax << endl;

        //Contract each of the incoming edges of current vertex;
        for (int i = 0; i < incoming_edges[current].size(); ++i) {
            int next = incoming_edges[current][i].vertex;
            if (vertices[next].contracted) continue;
            int nextDist = incoming_edges[current][i].cost;
            vector<Shortcut> shortcuts = simulateContraction(next, nextDist, current, inMax + outMax);
            do_shortcut(shortcuts);
        }
    }

    //printEdges();
    //cout << "----Incoming Edges----" << endl;
    //printEdgesR();
    
}

// Returns distance from s to t in the graph
int query(int s, int t) {
    clear();
    
    return biDijkstra(s, t);
}

private:
typedef int Distance;
typedef int Vertex;

struct Edge {
    int vertex{};
    int cost{};
    Edge() {};
    Edge(int v, int c) : vertex(v), cost(c) {}
};

struct compare {
    bool operator()(const Edge& e1, const Edge& e2) {
        return e1.cost > e2.cost;
    }
};

// Number of nodes
int N;
// Source and target
int s, t;
// Lists of edges outgoing from each node
vector<vector<Edge>> outgoing_edges;
// Lists of edges incoming to each node
vector<vector<Edge>> incoming_edges;

// Ranks of nodes - positions in the node ordering
//vector<int> edgeRank;
int cntRank = 0;

// Store distances in Bidirectional Dijkstra's
vector<Distance> distF;
vector<Distance> distR;

// Wrapper around STL priority_queue
class StlHeap {
    public:
    using Queue = priority_queue<Edge, vector<Edge>, compare>;
    
    StlHeap() {
        queue.reset(new Queue());
    }
    
    bool empty() const {
        return queue->empty();
    }
    
    void push(Vertex v, Distance c) {
        queue->push(Edge(v, c));
    }
    
    void clear() {
        queue.reset(new Queue());
    }
    
    Edge top() {
        return queue->top();
    }
    
    Edge pop() {
        Edge top = queue->top();
        queue->pop();
        return top;
    }
    
    void print() {
        auto pq = queue;
        while (!pq->empty()) {
            auto e = pq->top();
            pq->pop();
            cout << "V: " << e.vertex << " Imp: " << e.cost << endl;
        }
    }

    private:
    shared_ptr<Queue> queue;
};

// Priority queues for forward and backward searches
StlHeap minpqF;
StlHeap minpqR;

struct Shortcut {
    int from;
    int to;
    int cost;
    Shortcut( int from_, int to_, int cost_) : from(from_), to(to_), cost(cost_) {};
};

struct VertexMap {
    int numSC{};
    bool contracted{};
    int shortC{};
    int level{};
    int edgeRank{};
    int importance{};

    bool operator <(const VertexMap& v) {
        return importance < v.importance;
    }
};

vector<VertexMap> vertices;

void initializeVertex () {
    vertices.resize(N);
    for (int i = 0; i < N; ++i) {
        vertices[i].numSC = 0;
        vertices[i].contracted = false;
        vertices[i].shortC = 0;
        vertices[i].level = 0;
        vertices[i].edgeRank = 0;
        vertices[i].importance = incoming_edges[i].size() * outgoing_edges[i].size();
    }
}

distMap dijkstra (int s, int maxD) {
    distMap distM;
    distM[s] = 0;
    StlHeap minPQ;
    minPQ.push(s, 0);
    int hops = -1;

    while (!minPQ.empty()) {
        auto current = minPQ.pop().vertex;
        hops += 1;
        if (hops > 3 || distM[current] >= maxD) break;

        for (int i = 0; i < outgoing_edges[current].size(); ++i) {
            int next = outgoing_edges[current][i].vertex;
            int edge_cost = outgoing_edges[current][i].cost;
            if (vertices[next].contracted) continue;

            int next_cost = distM[current] + edge_cost;
            if (!distM.count(next) || next_cost < distM[next]) {
                distM[next] = next_cost;
                minPQ.push(next, next_cost);
            }
        }
    }
    return distM;
}

vector<Shortcut> simulateContraction (int s, int inDist, int v, int maxD) {
    vector<Shortcut> shortcuts;
    distMap distM = dijkstra (s, maxD);
    for (int i = 0; i < outgoing_edges[v].size(); ++i) {
        int next = outgoing_edges[v][i].vertex;
        int outDist = outgoing_edges[v][i].cost;
        if (!distM.count(next) || (inDist + outDist) < distM[next]) {
            shortcuts.emplace_back( Shortcut( s, next, inDist + outDist) );
            //vertices[v].contracted = true;
        }
    }

    return shortcuts;
}


void do_shortcut(vector<Shortcut>& shortcuts) {
    for (int i = 0; i < shortcuts.size(); ++i) {
        add_edge( shortcuts[i].from, shortcuts[i].to, shortcuts[i].cost);
    }
}

bool checkRelaxCond (int current, int next, const vector<Distance>& cost_so_far, int new_cost) {
    bool nodeRank = vertices[next].edgeRank > vertices[current].edgeRank;
    bool cost = (cost_so_far[next] == INF) || (new_cost < cost_so_far[next]);
    //cout << "nodeRank: " << nodeRank << " cost: " << cost << endl;
    return nodeRank && cost;
}

void relaxEdge(int v, string direction) {
    if (direction == "forward") {

        for (int i = 0; i < outgoing_edges[v].size(); ++i) {
            int next = outgoing_edges[v][i].vertex;
            if (visitedF[next]) continue;

            int edge_cost = outgoing_edges[v][i].cost;
            int new_cost = distF[v] + edge_cost;

            if (checkRelaxCond(v, next, distF, new_cost)) {
                distF[next] = new_cost;
                minpqF.push(next, new_cost);
            }
        }

    } else if (direction == "reverse") {

        for (int i = 0; i < incoming_edges[v].size(); ++i) {
            int next = incoming_edges[v][i].vertex;
            if (visitedR[next]) continue;

            int edge_cost = incoming_edges[v][i].cost;
            int new_cost = distR[v] + edge_cost;
            if (checkRelaxCond(v, next, distR, new_cost)) {
                distR[next] = new_cost;
                minpqR.push(next, new_cost);
                //cout << "Next: " << next << " new_cost: " << new_cost << endl;
            }
        }

    }
}

int biDijkstra (int s, int t) {
    minpqF.push(s, 0);
    distF[s] = 0;

    minpqR.push(t, 0);
    distR[t] = 0;
    
    // Estimate of the distance from s to t
    int estimate = INF;
    
    int currentF, currentR;
    while (!minpqF.empty() && !minpqR.empty()) {
        currentF = minpqF.pop().vertex;
        visitedF[currentF] = true;
        currentR = minpqR.pop().vertex;
        visitedR[currentR] = true;
        if (distF[currentF] >= estimate) break;
        if (distR[currentR] >= estimate) break;
        
        relaxEdge(currentF, "forward");
        relaxEdge(currentR, "reverse");
        
        //cout << "Front: " << currentF << " : " << estimate << endl;
        
        if (visitedR[currentF] && distF[currentF] + distR[currentF] < estimate) {
            estimate = distF[currentF] + distR[currentF];
        }

        
        
        //cout << "Reverse: " << currentR << " : " << estimate << endl;
        
        if (visitedF[currentR] && distF[currentR] + distR[currentR] < estimate) {
            estimate = distF[currentR] + distR[currentR];
        }
        
    }

    if (estimate == INF) return -1;
    return estimate;
}


void set_n(int n) {
    N = n;
    outgoing_edges.resize(n);
    incoming_edges.resize(n);
}

void add_edge_to_list(vector<Edge>& elist, int v, int c) {
    for (int i = 0; i < elist.size(); ++i) {
        Edge& p = elist[i];
        if (p.vertex == v) {
            if (p.cost > c) {
                p.cost = c;
            }
            return;
        }
    }
    elist.push_back(Edge(v, c));
}

void add_directed_edge(int u, int v, int c) {
    add_edge_to_list(outgoing_edges[u], v, c);
    add_edge_to_list(incoming_edges[v], u, c);
}

void add_edge(int u, int v, int c) {
    add_directed_edge(u, v, c);
}

void finalize() {
    // initialize dist vectors for bidirectional dijkstra
    distF.resize(N, INF);
    distR.resize(N, INF);
    visitedF.resize(N, false);
    visitedR.resize(N, false);
}

vector<bool> visitedF;
vector<bool> visitedR;

void clear() {
    for (int i = 0; i < N; ++i) {
        distF[i] = INF;
        distR[i] = INF;
        visitedF[i] =false;
        visitedR[i] = false;
    }

    minpqF.clear();
    minpqR.clear();
}

void printEdges () {
    for (int i = 0; i < N; ++i) {
        cout << i << " :: " ;
        for (int j = 0; j < outgoing_edges[i].size(); ++j) 
            cout << i << "->" << outgoing_edges[i][j].vertex << ":" << outgoing_edges[i][j].cost << " , ";
        cout << "\n";
    }
}

void printEdgesR () {
    for (int i = 0; i < N; ++i) {
        cout << i << " :: " ;
        for (int j = 0; j < incoming_edges[i].size(); ++j) 
            cout << i << "->" << incoming_edges[i][j].vertex << ":" << incoming_edges[i][j].cost << " , ";
        cout << "\n";
    }
}

/*
bool read_stdin() {
    int u,v,c,n,m;
    ifstream test("test3.txt");
    test >> n >> m;
    set_n(n);
    for (int i = 0; i < m; ++i) {
        test >> u >> v >> c;
        add_edge(u-1, v-1, c);
    }
    finalize();
    return true;
}
};

int main() {
    std::ios::sync_with_stdio(false);
    Graph g;
    g.preprocess();
    cout << "Ready" << endl;

    ifstream test("test3.txt");
    int u,v,c,n,m;
    test >> n >> m;
    cout << n << " " << m << endl;
    for (int i = 0; i < m; ++i) {
        test >> u >> v >> c;
    //    cout << u << " " << v << " " << c << endl;
    }
    int t;
    test >> t;
    for (int i = 0; i < t; ++i) {
        int u, v;
        test >> u >> v;
        cout << g.query(u-1, v-1) << "\n";
    }
}
*/


bool read_stdin() {
    int u,v,c,n,m;
    cin >> n >> m;
    set_n(n);
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> c;
        add_edge(u-1, v-1, c);
    }
    finalize();
    return true;
}
};


int main() {
    std::ios::sync_with_stdio(false);
    Graph g;
    g.preprocess();
    cout << "Ready" << endl;

    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int u, v;
        cin >> u >> v;
        cout << g.query(u-1, v-1) << "\n";
    }
}



