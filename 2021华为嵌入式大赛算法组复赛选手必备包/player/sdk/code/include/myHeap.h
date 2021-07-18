#pragma once
#include "data.h"
/*索引优先队用一个整数和对象进行关联，当我们需要更新该对象的值时，可以通这个整数进行快速索引,
然后对对象的值进行更新。当然更新后的对象在优先队列中的位置可能发生变化，这样以保证整个队列还是一个优先队列。*/

class IndexMinPQ {
private:
    int maxN; //PQ中的最大元素数量
    int N; //PQ中的元素数量
    vector<int> pq;//索引二叉堆，由1开始
    vector<int> qp;//逆序：qp[pr[i]] = pq[qp[i]] = i
    vector<int> keys;//有优先级之分的元素
private:
    bool less(int i, int j);
    void exch(int i, int j);
    void swim(int k);
    void sink(int k);
public:
    IndexMinPQ() = default;
    IndexMinPQ(int maxN);
    bool isEmpty() {return N == 0;}
    bool contains(int k) {return qp[k] != -1;}
    void insert(int k, int key);
    void change(int k, int key);
    int min() {return keys[pq[1]];}
    int delMin();
    int size() {return N;}
};
