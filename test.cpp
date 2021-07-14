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
    set<int> arr{1,3,5};
    arr.erase(1);
    for (auto x : arr) {
        cout << x;
    }
    return 0;
}