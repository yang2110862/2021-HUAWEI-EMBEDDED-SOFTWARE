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
    vector<Node*> node;
    cout << node.size();
    return 0;
}