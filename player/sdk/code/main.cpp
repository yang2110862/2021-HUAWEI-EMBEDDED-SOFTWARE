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
        EdgeWeightedGraph G(N, E, edgeVec, typeVec, D);
        vector<int> baseSet = G.getBaseSet();
        vector<int> satelliteSet = G.getSatellitSet();
        unordered_map<Node*, vector<Node*>> routes;
        set<int> headSet;//头节点集合
        set<int> recSatellite_candidated;//候选接受卫星集合
        for (int base : baseSet) {
            headSet.insert(base);
            G.getNode(base)->leftDist = D;
        }
        for (int satellite : satelliteSet) {
            recSatellite_candidated.insert(satellite);
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
        for (auto head : headSet) {
            Node* node = G.getNode(head);
            DijkstraSP dijk(G, head, node->leftDist);
        }
        //自上而下，合并路径
        while (true) {
            int targetSatellite;//本轮选到的接收卫星
            unordered_map<int, int> cnt;//记录不同接收卫星所收到的投票
            unordered_map<int, DijkstraSP> mp_dijk;//为了复用已经算过的dijkstra算法
            int maxVoter = 0;//记录最大投票数
            //找到本轮能连接到最多头节点的接受卫星作为本轮的接收卫星
            for (auto head : headSet) {
                Node* node = G.getNode(head);
                DijkstraSP dijk(G, head, node->leftDist);
                mp_dijk[head] = dijk;
                for (auto recSatellite : recSatellite_candidated) {
                    if (dijk.hasPathTo(G, recSatellite)) {
                        ++cnt[recSatellite];
                        if (cnt[recSatellite] > maxVoter) {
                            maxVoter = cnt[recSatellite];
                            targetSatellite = recSatellite;
                        }
                    }
                }
            } 
            //只有自己给自己投票时，不能再合并
            if (maxVoter == 1) break; 
            //开始合并，并更新点、边、集合的信息
            set<int> deled_head;
            for (auto head : headSet) {
                Node* node = G.getNode(head);
                DijkstraSP dijk = mp_dijk[head];
                //更新路径
                if (dijk.hasPathTo(G, targetSatellite)) {
                    deled_head.insert(head);
                    auto route = dijk.pathTo(targetSatellite);
                    for (auto edge : route) {
                        Node* next = G.getNode(edge->other(node->getNum()));
                        routes[node].emplace_back(next);
                        node->next = next;
                        next->leftDist = min(node->leftDist - edge->getWeight(), next->leftDist);
                        edge->hasUsed = true;
                        node = next;
                    }
                }
            }
            for (auto node : deled_head) {
                headSet.erase(node);
            }
            headSet.insert(targetSatellite);
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
        for (int base : baseSet) {
            Route temp;
            Node* node = G.getNode(base);
            temp.push_back(node->getNum());
            Node* next = node->next;
            temp.push_back(next->getNum());
            for (auto node : routes[next]) {
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