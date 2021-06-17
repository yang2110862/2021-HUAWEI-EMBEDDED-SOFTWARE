#include "data.h"

unordered_map<int, ListNode*> numToEntity;
unordered_map<int, int> frequency;  //能连接到卫星key的基站数value
vector<int> base_station;
void Init::Creat_map(uint32_t N) {
    for (int i = 0; i < N; ++i) {      
        ListNode* node = new ListNode;
        node->num = i;
        numToEntity[i] = node;
    }
}

void Init::Init_list(uint32_t N, uint32_t E, const vector<bool>& typeVec, const vector<Edge>& edgeVec) {
    Creat_map(N);
    for (int i = 0; i < N; ++i) {
        numToEntity[i]->isSatellite = typeVec[i];
        if (!typeVec[i]) base_station.push_back(i);
    }
    for (int i = 0; i < E; ++i) {
        int send = edgeVec[i].send;
        int recv = edgeVec[i].recv;
        int dist = edgeVec[i].dist;
        numToEntity[send]->dist[recv] = dist;
        numToEntity[recv]->dist[send] = dist;
        
        numToEntity[send]->next.emplace_back(numToEntity[recv]);
        numToEntity[recv]->next.emplace_back(numToEntity[send]);

        if (!typeVec[send]) frequency[send]++;
        if (!typeVec[recv]) frequency[send]++;
    }
}

vector<Route> Init::Process(uint32_t N, uint32_t C, uint32_t D, uint32_t PS,
                       const vector<bool>& typeVec, const vector<Edge>& edgeVec) {
    uint32_t E = edgeVec.size();
    Init_list(N, E, typeVec, edgeVec);
    vector<Route> sol;
    for (int i = 0; i < base_station.size(); ++i) {
        // int min_dist = INT_MAX;
        // int num;
        // auto base = numToEntity[base_station[i]];
        // for (auto x : base->dist) {
        //     if (x.second < min_dist) {
        //         min_dist = x.second;
        //         num = x.first;
        //     }
        // }
        auto base = numToEntity[base_station[i]];
        int max_frequency = 0;
        for (auto x : base->dist) {
            if (x.first > max_frequency && x.second <= D) {
                max_frequency = x.first;
            }
        }
        Route temp = {base_station[i], max_frequency};
        sol.emplace_back(temp);
    }
    return sol;
}