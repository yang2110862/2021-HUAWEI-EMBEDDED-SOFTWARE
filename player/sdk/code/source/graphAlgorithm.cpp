#include "graphAlgorithm.h"

void DijkstraSP::relax(EdgeWeightedGraph& G, int v) {
    for (Edge* e : G.getAdj(v)) {
        if (e->hasUsed) continue;
        int w = e->other(v);
        int temp = distTo[v] + e->getWeight();
        if (temp <= maxLen && distTo[w] > temp) {
            distTo[w] = temp;
            edgeTo[w] = e;
            if (pq.contains(w)) pq.change(w, distTo[w]);
            else pq.insert(w, distTo[w]);
        }
    }
}
DijkstraSP::DijkstraSP(EdgeWeightedGraph& G, int s, int D) {
    begin = s;
    maxLen = D;
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
    if (distTo[v] == INT_MAX) return route;
    stack<Edge*> path;
    int end = v;
    if (edgeTo[v] == nullptr) return route;
    int beg = edgeTo[v]->other(end);
    for (Edge* e = edgeTo[v]; e != nullptr; e = edgeTo[end]) {
        path.push(e);
        end = beg;
        if (edgeTo[end] != nullptr) {
            beg = edgeTo[end]->other(end);
        }
    }
    while (!path.empty()) {
        route.push_back(path.top());
        path.pop();
    }
    return route;
}
bool DijkstraSP::hasPathTo(EdgeWeightedGraph& G, int v) {
    auto path = this->pathTo(v);
    if (this->distanceTo(v) == INT_MAX) return false;
    int leftDistance = this->maxLen;
    int n = path.size();
    if (n == 0) return true;
    int beg = this->begin;
    int end = path[0]->other(begin);
    leftDistance = min(leftDistance - path[0]->getWeight(), G.getNode(end)->leftDist);
    for (int i = 1; i < n; ++i) {
        beg = end;
        end = path[i]->other(beg);
        leftDistance = min(leftDistance - path[i]->getWeight(), G.getNode(end)->leftDist);
    }
    return leftDistance >= 0;
}