#include <iostream>
using namespace std;
class Node {
private:
    int x;
public:
    int get_x() {return x + 1;}
    Node() = default;
    Node(int x) : x(x + 1) {};
};

int main() {
    Node* node = new Node(3);
    cout << node->get_x();
    return 0;
}