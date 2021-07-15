#pragma once
#include "data.h"
#include "myHeap.h"
//最短路径的Dijkstra算法(带距离约束和路径不冲突约束)
class DijkstraSP {
private:
    vector<Edge*> edgeTo; //由顶点索引的Edge对象的数组，其中edgeTo[v]为连接v和它的父节点的边
    vector<int> distTo; //distTo[w]是从s到w的最短路径的长度
    IndexMinPQ pq;
    int maxLen;
private:
    void relax(EdgeWeightedGraph& G, int v);
public:
    DijkstraSP() = default;
    DijkstraSP(EdgeWeightedGraph& G, int s, int D);
    int distanceTo(int v) {return distTo[v];} //从顶点s到v的距离，如果不存在则路径为无穷大
    bool hasPathTo(EdgeWeightedGraph& G, int v); //是否有从顶点s到v的路径
    vector<Edge*> pathTo(int v);//从顶点s到v的路径
};