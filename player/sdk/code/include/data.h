#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

// struct Edge {
//     uint32_t send;  // 发送站点
//     uint32_t recv;  // 接受站点
//     uint32_t dist;  // 距离
// };

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
        else throw domain_error("logc error : The result value corresponding to the parameter does not exist");
    }
    int compareTo(Edge* that) {
        if (this->weight < that->weight) return -1;
        else if (this->weight > that->weight) return 1;
        else return 0;
    }
};

class EdgeWeightedGraph {
public:
    int V;//顶点总数
    int E;//边的总数
    vector<set<int>> adj;//邻接表
    unordered_map<int, Node*> mp;//索引->节点
public:
    EdgeWeightedGraph(int N, int E, vector<Edge*>& edgeVec, vector<bool>& typeVce) { 
        this->V = N;
        this->E = E;
        adj.resize(N);
        for (int v = 0; v < V; ++v) {
            Node* node = new Node(v, typeVce[v]);
            mp[v] = node;
        }
        for (auto edge : edgeVec) {
            int v = edge->either(), w = edge->other(v);
            adj[v].insert(w);
            adj[w].insert(v);
        }
    }
    Node* getNode(int index) {
        if (mp.count(index)) return mp[index];
        else throw range_error("out of range");
    }
};