#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <climits>
#include <queue>
using namespace std;

using Route = vector<uint32_t>;
class Node {
private:
    int num;
    bool Satellite;
public:
    Node(int num, bool flag) : num(num), Satellite(flag) {}
    int getNum() {return num;}
    bool isSatellite() {return Satellite;}
};


/*该数据结构提供了either()和other()两个方法。在已知一个顶点v时，用例可以使用other(v)来得到
边的另一个顶点。当两个顶点都是未知的时候，用例可以使用惯用代码v = e.ther(), w = e.other(v);
来访问一个Edge对象e的两个顶点。*/
class Edge {
private:
    int v;//顶点之一
    int w;//另一个顶点
    int weight;//边的权重
public:
    Edge(int v, int w, int weigh) {
        this->v = v;
        this->w = w;
        this->weight = weigh;
    }
    int either() {return v;}
    int other(int vertex) {
        if (vertex == v) return w;
        else if (vertex == w) return v;
        else throw domain_error("logic error : The result value corresponding to the parameter does not exist");
    }
    int getWeight() {return weight;}
    int compareTo(Edge* that) {
        if (this->weight < that->weight) return -1;
        else if (this->weight > that->weight) return 1;
        else return 0;
    }
};

class EdgeWeightedGraph {
private:
    int V;//顶点总数
    int E;//边的总数
    vector<set<Edge*>> adj;//邻接表
    unordered_map<int, Node*> mp;//索引->节点
    vector<int> base;
    vector<int> satellite;
public:
    EdgeWeightedGraph(int N, int E, const vector<Edge*>& edgeVec, const vector<bool>& typeVce) { 
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
    Node* getNode(int index) {
        if (mp.count(index)) return mp[index];
        else throw range_error("out of range");
    }
    set<Edge*> getAdj(int v) {return adj[v];}
    int getV() {return V;}
    int getE() {return E;}
    vector<int> getBaseSet() {return base;}
    vector<int> getSatellitSet() {return satellite;}
};

//最短路径的Dijkstra算法
class DijkstraSP {
private:
    struct cmp_edge_dist{
        
    };
private:
    vector<Edge*> edgeTo; //由顶点索引的Edge对象的数组，其中edgeTo[v]为连接v和它的父节点的边
    vector<int> distTo; //distTo[w]是从s到w的最短路径的长度
    priority_queue<pair<int, int>, vector<pair<int, int>>, 
        greater<pair<int ,int>>> pq;
    void relax(EdgeWeightedGraph G, int v) {
        for (Edge* e : G.getAdj(v)) {
            int w = e->other(v);
            if (distTo[w] > distTo[v] + e->getWeight()) {
                distTo[w] = distTo[v] + e->getWeight();
                edgeTo[w] = e;
                // if (pq.)
            }
        }
    }
public:
    DijkstraSP(EdgeWeightedGraph G, int s) {
        edgeTo.resize(G.getV());
        distTo.resize(G.getV());
        for (int v = 0; v < G.getV(); ++v) {
            distTo[v] = INT_MAX;
        }
        distTo[s] = 0;
        pq.push(make_pair(0, s));
        while (!pq.empty()) {
            auto temp = pq.top();
            pq.pop();
            relax(G, temp.second);
        }
    }
};