#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <iostream>
#include <memory>
#include <cassert>
#include <unordered_set>
#include <unordered_map>

using namespace std;

using Adj = vector<vector<pair<int, int>>>; 
using distMap = unordered_map<int, int> ;

class Graph {

public:
Graph() {
    read_stdin();
    bidistance.resize(2, vector<int>(N, INF));
}

int get_n() { return N;}

vector<pair<int, int>>& get_adjacent(int v, bool forward = true) {
    if (forward) {
        return outgoing_edges[v];
    } else {
        return incoming_edges[v];
    }
}

void preprocess() {
    //distance.resize(N, INF);
    // Priority queue will store pairs of (importance, node) with the least important node in the head
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>>> queue;

    // Implement the rest of the algorithm yourself
}

// Returns distance from s to t in the graph
int query(int u, int w) {
    update(u, 0, true);
    update(w, 0, false);
    s = u; 
    t = w;
    // Implement the rest of the algorithm yourself

    return -1;
}

private:
typedef int Distance;
typedef int Vertex;

// Number of nodes
int N;
// Source and target
int s, t;
// Estimate of the distance from s to t
// int estimate = INF;
// Lists of edges outgoing from each node
vector<vector<pair<int, int>>> outgoing_edges;
// Lists of edges incoming to each node
vector<vector<pair<int, int>>> incoming_edges;

static constexpr int INF = numeric_limits<int>::max() / 2;

// Ranks of nodes - positions in the node ordering
vector<int> rank;

// Distance to node v, bidistance[0][v] - from source in the forward search, bidistance[1][v] - from target
// in the backward search.
vector<vector<Distance>> bidistance;

// Wrapper around STL priority_queue
class StlHeap {
public:
    using T = pair<Distance, Vertex>;
    using Queue = priority_queue<T, vector<T>, greater<T>>;

    StlHeap() {
        queue.reset(new Queue());
    }

    bool empty() const {
        return queue->empty();
    }

    void update(Vertex v, Distance d) {
        queue->push(make_pair(d,v));
    }

    void clear() {
        queue.reset(new Queue());
    }

    pair<Distance, Vertex> top() {
        return queue->top();
    }

    pair<Distance, Vertex> pop() {
        pair<Distance, Vertex> top = queue->top();
        queue->pop();
        return top;
    }
private:
    unique_ptr<Queue> queue;
};

// Priority queues for forward and backward searches
StlHeap diqueue[2];

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
    int importance{};

    bool operator <(const VertexMap& v) {
        return importance < v.importance;
    }
};

vector<VertexMap> vertices;

void initializeVertex (int numVertices) {
    vertices.resize(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        vertices[i].numSC = 0;
        vertices[i].contracted = false;
        vertices[i].shortC = 0;
        vertices[i].level = 0;
        vertices[i].importance = incoming_edges[i].size() * outgoing_edges[i].size();
    }
}

distMap dijkstra (int s, int maxD) {
    distMap distM;
    distM[s] = 0;
    StlHeap minPQ;
    minPQ.update(0, s);
    int hops = -1;

    while (!minPQ.empty()) {
        auto current = minPQ.pop().second;
        hops += 1;
        if (hops > 3 || distM[current] >= maxD) break;

        for (int i = 0; i < outgoing_edges[current].size(); ++i) {
            int next = outgoing_edges[current][i].second;
            int edge_cost = outgoing_edges[current][i].first;
            if (vertices[next].contracted) continue;

            int next_cost = distM[current] + edge_cost;
            if (!distM.count(next) || next_cost < distM[next]) {
                distM[next] = next_cost;
                minPQ.update(next_cost, next);
            }
        }
    }
    return distM;
}

vector<Shortcut> simulateContraction (int s, int inDist, int v, int maxD) {
    vector<Shortcut> shortcuts;
    distMap distM = dijkstra (s, maxD);
    for (int i = 0; i < outgoing_edges[v].size(); ++i) {
        int next = outgoing_edges[v][i].second;
        int outDist = outgoing_edges[v][i].first;
        if (!distM.count(next) || (inDist + outDist) < distM[next]) {
            shortcuts.emplace_back( Shortcut( s, next, inDist + outDist) );
        }
    }

    return shortcuts;
}


void do_shortcut(int v, vector<Shortcut>& shortcuts) {
    for (int i = 0; i < shortcuts.size(); ++i) {
        add_edge( shortcuts[i].from, shortcuts[i].to, shortcuts[i].cost);
    }
}



// Try to relax the node v using distance d either in the forward or in the backward search
void update(int v, int d, bool forward) {
    // Implement this method yourself
}

class VertexSet
{
public:
    VertexSet(int n = 0) : visited(n) {}
    void resize(int n) {
        visited.resize(n);
    }
    void add(int v) {
        if (!visited[v]) {
            vertices.push_back(v);
            visited[v] = true;
        }
    }
    const vector<int>& get() const {
        return vertices;
    }
    const bool has(int v) {
        return visited[v];
    }
    void clear() {
        for (int v : vertices) {
            visited[v] = false;
        }
        vertices.clear();
    }

private:
    vector<int> visited;
    vector<int> vertices;
};
VertexSet visited;

// QEntry = (distance, vertex)
typedef pair<int,int> QEntry;
priority_queue<QEntry, vector<QEntry>, greater<QEntry>> queue;



// Adds all the shortcuts for the case when node v is contracted, and returns the importance of node v
// in this case
int do_shortcut(int v, vector<Shortcut>& shortcuts, int& mylevel) {
    // Implement this method yourself

    // Add neighbors and shortcut cover heuristics
    return (shortcuts.size() - outgoing_edges[v].size() - incoming_edges[v].size()) + mylevel;
}

void set_n(int n) {
    N = n;
    outgoing_edges.resize(n);
    incoming_edges.resize(n);
}


void add_edge_to_list(vector<pair<int,int>>& elist, int w, int c) {
    for (int i = 0; i < elist.size(); ++i) {
        pair<int, int>& p = elist[i];
        if (p.first == w) {
            if (p.second > c) {
                p.second = c;
            }
            return;
        }
    }
    elist.push_back(make_pair(w, c));
}

void add_directed_edge(int u, int v, int c) {
    add_edge_to_list(outgoing_edges[u], v, c);
    add_edge_to_list(incoming_edges[v], u, c);
}

void add_edge(int u, int v, int c) {
    add_directed_edge(u, v, c);
}

void finalize() {
    // Remove unnecessary edges
}

bool read_stdin() {
    int u,v,c,n,m;
    assert(scanf("%d %d", &n, &m) == 2);
    set_n(n);
    for (int i = 0; i < m; ++i) {
        assert(scanf("%d %d %d", &u, &v, &c) == 3);
        add_edge(u-1, v-1, c);
    }
    finalize();
    return true;
}
};

int main() {
    Graph g;
    g.preprocess();
    cout << "Ready" << endl;

    int t;
    assert(scanf("%d", &t) == 1);
    for (int i = 0; i < t; ++i) {
        int u, v;
        assert(scanf("%d %d", &u, &v) == 2);
        printf("%d\n", g.query(u-1, v-1));
    }
}
