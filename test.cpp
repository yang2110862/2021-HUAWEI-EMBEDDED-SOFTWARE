#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;
class Node {
public:
    int x;
public:
    int get_x() {return x;}
    Node() = default;
    Node(int x) : x(x) {};
};
int main() {
    set<int> s{1,2,3,4,5};
    for (auto x : s) {
        cout << x;
        s.erase(x);
    }
    return 0;
}