#pragma once

#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct Edge {
    uint32_t send;  // 发送站点
    uint32_t recv;  // 接受站点
    uint32_t dist;  // 距离
};

using Route = vector<uint32_t>;

//顶点
class Vertex {
public:
    int num;
};
//邻接表表示
class Graph {
private:
    int v;
    int e;
    vector<set<int>> adj; //是否要用set
public:
    Graph(int v);
    Graph(iostream& in);
    int V();
    int E();
    void add_edge(int v, int w);
    vector<Vertex*> adj(int v);
    string to_string();
};
//图处理算法
class Search {
public:
    Search(Graph G,int s);//找到和起点s相连的所有顶点
    bool marked(int v); //v和s是连通的吗
    int count(); //与s连通的顶点总数
};
//dfs（解决连通性问题以及单点路径问题）
class DepthFirstSearch {
private:
    vector<int> marked;
    int count;
    void dfs(Graph G, int s);
public:
    DepthFirstSearch(Graph G, int s); //找到和起点s相连的所有顶点
    bool marked(int w) {    //v和s是连通的吗
        return marked[w];
    }
    int count() {return count;}; //与s连通的顶点总数
};
//使用dfs搜索查找图中的路径
class DepthFirstPaths {
private:
    vector<int> marked;
    vector<int> edge_to;
    int s;
    void dfs(Graph G, int s);
public:
    DepthFirstPaths(Graph G, int s); //找到和起点s相连的所有顶点
    bool has_path_to(int v);
    vector<int> path_to(int v);
};
class Paths {
public:
    Paths(Graph G, int s);      //在G中找出所有起点为s的路径
    bool has_path_to(int v); //是否存在从s到v的路径
    vector<int> path_to(int v); //s到v的路径，如果不存在返回空
};

//bfs （找最短路径）
class BreadthFirstPaths {
private:
    vector<int> marked;
    vector<int> edgeTo;
    int s;
    void bfs(Graph G, int s);
public:
    BreadthFirstPaths(Graph G, int s);
    bool has_path_to(int v);
    vector<int> path_to(int v);
};
