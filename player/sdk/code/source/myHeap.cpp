#include "myHeap.h"

bool IndexMinPQ::less(int i, int j) {
    if (keys[pq[i]] < keys[pq[j]]) return true;
    return false;
}
void IndexMinPQ::exch(int i, int j) {
    int temp = pq[i];
    pq[i] = pq[j];
    pq[j] = temp;
    qp[pq[i]] = i;
    qp[pq[j]] = j;
}
void IndexMinPQ::swim(int k) {
    while (k > 1 && less(k, k / 2)) {
        exch(k, k / 2);
        k = k / 2;
    }
}
void IndexMinPQ::sink(int k) {
    while (2 * k <= N) {
        int j = 2 * k;
        if (j < N && less(j + 1, j)) ++j;
        if (!less(j, k)) break;
        exch(k, j);
        k = j;
    }
}
IndexMinPQ::IndexMinPQ(int maxN) {
    this->maxN = maxN;
    keys.resize(maxN + 1);
    pq.resize(maxN + 1);
    qp.resize(maxN + 1);
    for (int i = 0; i <= maxN; ++i) {
        qp[i] = -1;
    }
}
void IndexMinPQ::insert(int k, int key) {
    N++;
    qp[k] = N;
    pq[N] = k;
    keys[k] = key;
    swim(N);
}
int IndexMinPQ::delMin() {
    int indexOfMin = pq[1];
    exch(1, N--);
    sink(1);
    keys[pq[N + 1]] = INT_MAX;
    qp[pq[N + 1]] = -1;
    return indexOfMin;
}
void IndexMinPQ::change(int k, int key) {
    if (k > maxN) range_error("out of range")  ;
    if (!contains(k)) cerr << "don't contain";
    keys[k] = key;
    swim(qp[k]);
    sink(qp[k]);
}