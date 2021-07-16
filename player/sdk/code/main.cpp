#include <iostream>
#include <vector>
#include "graphAlgorithm.h"
#include "data.h"
#include "myHeap.h"
#include <algorithm>
#include <cmath>
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
        unordered_map<int, vector<Node*>> routes;
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
            Edge* edge = nullptr;
            for (auto e : G.getAdj(base)) { //任意找一个满足要求的基站
                if (e->getWeight() <= D) {
                    edge = e;
                    break;
                }
            }
            Node* next = G.getNode(edge->other(base));
            node->next = next;
            //更新点、边、集合信息
            next->leftDist = min(node->leftDist - edge->getWeight(), next->leftDist);
            edge->hasUsed = true;
            headSet.erase(base);
            headSet.insert(next->getNum());
        }
        //自上而下，合并路径
        while (true) {
            int targetSatellite;//本轮选到的接收卫星
            unordered_map<int, double> cnt;//记录不同接收卫星所收到的投票
            unordered_map<int, DijkstraSP> mp_dijk;//为了复用已经算过的dijkstra算法
            double maxVoter = 0;//记录最大投票数
            //找到本轮能连接到最多头节点的接受卫星作为本轮的接收卫星
            for (auto head : headSet) {
                Node* node = G.getNode(head);
                DijkstraSP dijk(G, head, node->leftDist);
                mp_dijk[head] = dijk;
            }
            int n_recSatelliteCandidated = recSatellite_candidated.size(); //所有被投票的卫星数量
            unordered_map<int, int> poll_diffHead;//本轮中不同头节点能投的票数
            for (auto head : headSet) {
                int num_canLink = 0;//该头节点能连接到的卫星数
                DijkstraSP dijk = mp_dijk[head];
                for (auto recSatellite : recSatellite_candidated) {
                    if (dijk.hasPathTo(G, recSatellite)) {
                        ++num_canLink;
                    }
                }
                poll_diffHead[head] = log(1.0 * n_recSatelliteCandidated / num_canLink);
            }
            for (auto head : headSet) {
                Node* node = G.getNode(head);
                DijkstraSP dijk(G, head, node->leftDist);
                mp_dijk[head] = dijk;
                for (auto recSatellite : recSatellite_candidated) {
                    if (dijk.hasPathTo(G, recSatellite)) {
                        cnt[recSatellite] += poll_diffHead[head];
                        if (cnt[recSatellite] > maxVoter) {
                            maxVoter = cnt[recSatellite];
                            targetSatellite = recSatellite;
                        }
                    }
                }
            } 
            //只有自己给自己投票时或全部头节点都已经被选（无人投票了），不能再合并
            if (maxVoter == log(1.0 * n_recSatelliteCandidated / 1) || maxVoter == 0) break;
            recSatellite_candidated.erase(targetSatellite);
            //开始合并，并更新点、边、集合的信息
            set<int> deled_head;
            set<int> deled_recCandidated;
            for (auto head : headSet) {
                Node* node = G.getNode(head);
                DijkstraSP dijk = mp_dijk[head];
                //更新路径
                if (dijk.hasPathTo(G, targetSatellite)) {
                    deled_head.insert(head);
                    deled_recCandidated.insert(head);
                    auto route = dijk.pathTo(targetSatellite);
                    for (auto edge : route) {
                        Node* next = G.getNode(edge->other(node->getNum()));
                        deled_recCandidated.insert(next->getNum());
                        routes[head].emplace_back(next);
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
            for (auto node : deled_recCandidated) {
                recSatellite_candidated.erase(node);
            }
        }

        //保存所有路径
        // set<int> stars;
        for (int base : baseSet) {
            Route temp;
            Node* node = G.getNode(base);
            temp.push_back(node->getNum());
            Node* next = node->next;
            temp.push_back(next->getNum());
            if (routes.count(next->getNum())) {
                for (auto node : routes[next->getNum()]) {
                    temp.push_back(node->getNum());
                }
            }
            // stars.insert(*(temp.end() - 1));
            retRouteVec.push_back(temp);
        }
        // cout << "stars num : " << stars.size() << endl;
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