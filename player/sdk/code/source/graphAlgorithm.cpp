#include "graphAlgorithm.h"

void DijkstraSP::relax(EdgeWeightedGraph G, int v) {
    for (Edge* e : G.getAdj(v)) {
        int w = e->other(v);
        if (distTo[w] > distTo[v] + e->getWeight()) {
            distTo[w] = distTo[v] + e->getWeight();
            edgeTo[w] = e;
            if (pq.contains(w)) pq.change(w, distTo[w]);
            else pq.insert(w, distTo[w]);
        }
    }
}
DijkstraSP::DijkstraSP(EdgeWeightedGraph G, int s) {
    edgeTo.resize(G.getV());
    distTo.resize(G.getV());
    pq = IndexMinPQ(G.getV());
    for (int v = 0; v < G.getV(); ++v) {
        distTo[v] = INT_MAX;
    }
    distTo[s] = 0;
    pq.insert(s, 0);
    while (!pq.isEmpty()) {
        relax(G, pq.delMin());
    }
}
vector<Edge*> DijkstraSP::pathTo(int v) {
    vector<Edge*> route;
    if (!hasPathTo(v)) return route;
    stack<Edge*> path;
    for (Edge* e = edgeTo[v]; e != nullptr; e = edgeTo[e->other(v)]) {
        path.push(e);
    }
    while (!path.empty()) {
        route.push_back(path.top());
        path.pop();
    }
    return route;
}