#include "data.h"

unordered_map<int, ListNode*> numToSatellite;
vector<int> base_station;
void Init::Creat_map(uint32_t N) {
    for (int i = 0; i < N; ++i) {      
        ListNode* node = new ListNode;
        node->num = i;
        numToSatellite[i] = node;
    }
}

void Init::Init_list(uint32_t N, uint32_t E, const vector<bool>& typeVec, const vector<Edge>& edgeVec) {
    Creat_map(N);
    for (int i = 0; i < N; ++i) {
        numToSatellite[i]->isSatellite = typeVec[i];
        if (!typeVec[i]) base_station.push_back(i);
    }
    for (int i = 0; i < E; ++i) {
        int send = edgeVec[i].send;
        int recv = edgeVec[i].recv;
        int dist = edgeVec[i].dist;
        numToSatellite[send]->dist[recv] = dist;
        numToSatellite[recv]->dist[send] = dist;

        numToSatellite[send]->next.emplace_back(numToSatellite[recv]);
        numToSatellite[recv]->next.emplace_back(numToSatellite[send]);
    }
}

vector<Route> Init::Process(uint32_t N, uint32_t C, uint32_t D, uint32_t PS,
                       const vector<bool>& typeVec, const vector<Edge>& edgeVec) {
    uint32_t E = edgeVec.size();
    Init_list(N, E, typeVec, edgeVec);
    vector<Route> sol;
    for (int i = 0; i < base_station.size(); ++i) {
        Route temp = {base_station[i], numToSatellite[base_station[i]]->next[0]->num};
        sol.emplace_back(temp);
    }
    return sol;
}