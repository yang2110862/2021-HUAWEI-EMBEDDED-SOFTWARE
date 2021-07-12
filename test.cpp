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
    vector<int*> test;
    test.resize(3);
    if (test[2] == nullptr) {
        cout << "y";
    } else {
        cout << "n";
    }
    return 0;
}