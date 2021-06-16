#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

struct Edge {
    uint32_t send;  // 发送站点
    uint32_t recv;  // 接受站点
    uint32_t dist;  // 距离
};

using Route = vector<int>;
struct ListNode {
    int num;
    bool isSatellite;
    vector<ListNode*> next;
    unordered_map<int, int> dist;  //到端点key的距离value
};
class Init {
private:
    void Creat_map(uint32_t N);
    void Init_list(uint32_t N, uint32_t E, const vector<bool>& typeVec, const vector<Edge>& edgeVec);
public:
    vector<Route> Process(uint32_t N, uint32_t C, uint32_t D, uint32_t PS,
                       const vector<bool>& typeVec, const vector<Edge>& edgeVec);
};