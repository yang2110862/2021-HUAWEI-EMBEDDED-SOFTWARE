#include "data.h"

Edge::Edge(int v, int w, int weigh) {
    this->v = v;
    this->w = w;
    this->weight = weigh;
}
int Edge::other(int vertex) {
    if (vertex == v) return w;
    else if (vertex == w) return v;
    else throw domain_error("logic error : The result value corresponding to the parameter does not exist");
}
int Edge::compareTo(Edge* that) {
    if (this->weight < that->weight) return -1;
    else if (this->weight > that->weight) return 1;
    else return 0;
}


EdgeWeightedGraph::EdgeWeightedGraph(int N, int E, const vector<Edge*>& edgeVec, const vector<bool>& typeVce) { 
    this->V = N;
    this->E = E;
    adj.resize(N);
    for (int v = 0; v < V; ++v) {
        Node* node = new Node(v, typeVce[v]);
        mp[v] = node;
        if (typeVce[v]) satellite.push_back(v);
        else base.push_back(v);
    }
    for (auto edge : edgeVec) {
        int v = edge->either(), w = edge->other(v);
        adj[v].insert(edge);
        adj[w].insert(edge);
    }
}