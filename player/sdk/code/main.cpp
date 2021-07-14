#include <iostream>
#include <vector>
#include "graphAlgorithm.h"
#include "data.h"
#include "myHeap.h"
using namespace std;

class Solution {
public:
    vector<Route> Plan(uint32_t N, uint32_t E, uint32_t C, uint32_t D, uint32_t PS,
                       const vector<bool>& typeVec, const vector<Edge*>& edgeVec)
    {
        vector<Route> retRouteVec;
        EdgeWeightedGraph G(N, E, edgeVec, typeVec);
        vector<int> baseSet = G.getBaseSet();
        vector<int> satelliteSet = G.getSatellitSet();

        set<int> headSet;//头节点集合
        for (int base : baseSet) {
            headSet.insert(base);
            G.getNode(base)->leftDist = D;
        }
        //路径初始化
        for (int base : baseSet) {
            Node* node = G.getNode(base); 
            Edge* edge = const_cast<Edge*>(*G.getAdj(base).begin());
            Node* next = G.getNode(edge->other(base));
            node->next = next;
            //更新点、边、集合信息
            next->leftDist = node->leftDist - edge->getWeight();
            edge->hasUsed = true;
            headSet.erase(base);
            headSet.insert(next->getNum());
        }

        //保存所有路径
        for (int base : baseSet) {
            Route temp;
            Node* node = G.getNode(base);
            temp.push_back(node->getNum());
            while (node->next != nullptr) {
                node = node->next;
                temp.push_back(node->getNum());
            }
            retRouteVec.push_back(temp);
        }
        return retRouteVec;
    }
};
int main(int argc, char *argv[])
{
    uint32_t N;             // 表示所有卫星和发射基站的总数
    uint32_t E;             // 表示网络中可使用的路径总数
    uint32_t C;             // 表示路径距离L与功耗P的系数，传输功耗计算公式为：P=C*L
    uint32_t D;             // 表示全网最大路径长度限制。
    uint32_t PS;            // 表示接收卫星所需要的站点功耗
    vector<bool> typeVec;   // 下标为i的值代表ID为i的站点身份，卫星为true，发射基站为false
    // vector<Edge> edgeVec;   // 包含E条边
    vector<Edge*> edgeVec;

    cin >> N >> E >> C >> D >> PS;
    typeVec = vector<bool>(N);
    for (uint32_t i = 0; i < N; i++) {
        bool type;
        cin >> type;
        typeVec[i] = type;
    }
    for (int i = 0; i < E; ++i) {
        int v, w, weight;
        cin >> v >> w >> weight;
        edgeVec.push_back(new Edge(v, w, weight));
    }
    
    Solution solution;
    vector<Route> retRouteVec = solution.Plan(N, E, C, D, PS, typeVec, edgeVec);
    for (const auto& route : retRouteVec) {
        for (const auto& siteId : route) {
            cout << siteId << " ";
        }
        cout << "\n";
    }
    return 0;
}