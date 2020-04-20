#include <iostream>

using namespace std;

class DisjointSet{
public:
    int numOfNode;
    int* parent; // parent nodes
    DisjointSet(int x);
    int findSet(int node);
    int findSet_v2(int x);
    void printDS();
};

int main()
{
    DisjointSet mySet(5);
    cout << "original tree: " << endl;
    mySet.printDS();
    cout << "v1, the root node is " << mySet.findSet(4) << endl;
    cout << "after v1: " << endl;
    mySet.printDS();
    cout << "v2, the root node is " << mySet.findSet_v2(4) << endl;
    cout << "after v2: " << endl;
    mySet.printDS();
    return 0;
}

DisjointSet::DisjointSet(int x) {
    numOfNode = x;
    parent = new int[numOfNode];
    parent[0] = 0;
    for (int i = 1; i < numOfNode; i++) {
        parent[i] = i - 1;
    }
}

void DisjointSet::printDS() {
    for (int i = 0; i < numOfNode; i++) {
        cout << parent[i] << "\n";
    }
}

DisjointSet::findSet(int node) {
    if (parent[node] != node) {
        return DisjointSet::findSet(parent[node]);
    } else {
        return parent[node];
    }
}

DisjointSet::findSet_v2(int x) {
    if (parent[x] !=  x) {
        parent[x] = findSet_v2(parent[x]);
    }
    return parent[x];
}
