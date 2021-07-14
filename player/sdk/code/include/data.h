#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <climits>
#include <queue>
#include <stack>
using namespace std;

using Route = vector<uint32_t>;
class Node {
private:
    int num;
    bool Satellite;
public:
    bool isHead = false;
    Node* next = nullptr;
    int leftDist;
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
    bool hasUsed = false;//是否已经用过
public:
    Edge(int v, int w, int weigh);
    int either() {return v;}  //返回边的一个点
    int other(int vertex);//返回边中不是vertex的另一个点
    int getWeight() {return weight;}
    int compareTo(Edge* that);
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
    EdgeWeightedGraph(int N, int E, const vector<Edge*>& edgeVec, 
        const vector<bool>& typeVce);
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
