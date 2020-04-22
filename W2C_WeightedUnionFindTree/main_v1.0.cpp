#include <iostream>
#include <fstream>
//#include <limits>

using namespace std;
const int MY_INT_MAX = 2147483647;

class DisjointSet{
public:
    int seqSize; // number of nodes
    int* parent; // parent nodes
    int* rankArr; // rankArr of each node
    int* weight;
    DisjointSet(int x);
    int findSet(int node);
    int findSetWithPathCompressAndWeight(int x); // findSet() operation with path compression
    void unionByRank(int x, int y, int z);
    bool same(int x, int y); // check whether x and y are in the same set
    void printSet();
};

int main()
{
    // import data from a txt file
    int n; // number of nodes
    int q; // number of queries
    int a, b, c, d;
    ifstream infile("in1.txt");
    infile >> n >> q;
    //cout << n << " " << q << endl;
    DisjointSet mySet(n);
    int output[q];
    int outIdx = 0;
    for (int i = 0; i < q; i++) {
        infile >> a;
        if (a == 0) { // "relate(x,y,z)"
            infile >> b >> c >> d;
            //cout << a << " " <<  b << " " << c << " " << d << endl;
            mySet.unionByRank(b, c, d);
            //mySet.printSet();
        }
        else if (a == 1) { // "dif(x, y)"
            infile >> b >> c;
            //cout << a << " " <<  b << " " << c << endl;
            if (mySet.same(b, c)) { output[outIdx] = mySet.weight[c] - mySet.weight[b]; }
            else { output[outIdx] = INT_MAX; }
            outIdx += 1;
            //mySet.printSet();
        }
    }
    infile.close();

//    // import data from command line
//    int n; // number of nodes
//    int q; // number of queries
//    int a, b, c, d;
//    cin >> n >> q;
//    DisjointSet mySet(n);
//    int output[q];
//    int outIdx = 0;
//    for (int i = 0; i < q; i++) {
//        cin >> a;
//        if (a == 0) { // "relate(x,y,z)"
//            cin >> b >> c >> d;
//            mySet.unionByRank(b, c, d);
//        }
//        else if (a == 1) { // "dif(x, y)"
//            cin >> b >> c;
//            if (mySet.same(b, c)) { output[outIdx] = mySet.weight[c] - mySet.weight[b]; }
//            else { output[outIdx] = MY_INT_MAX; }
//            outIdx += 1;
//        }
//    }

    //print out the output
    for (int i = 0; i < outIdx; i++) {
        if (output[i] != MY_INT_MAX) { cout << output[i] << endl; }
        else { cout << "?\n"; }
    }

    return 0;
}

DisjointSet::DisjointSet(int x) {
    seqSize = x;
    parent = new int[seqSize];
    rankArr = new int[seqSize];
    weight = new int[seqSize];
    for (int i = 0; i < seqSize; i++) {
        parent[i] = i;
        rankArr[i] = 1;
        weight[i] = 0;
    }
}

void DisjointSet::printSet() {
    cout << "n:\t";
    for (int i = 0; i < this->seqSize; i++) {
        cout << i << "\t";
    }
    cout << endl;
    cout << "p:\t";
    for (int i = 0; i < this->seqSize; i++) {
        cout << this->parent[i] << "\t";
    }
    cout << endl;
    cout << "w:\t";
    for (int i = 0; i < this->seqSize; i++) {
        cout << this->weight[i] << "\t";
    }
    cout << endl;
    cout << "r:\t";
    for (int i = 0; i < this->seqSize; i++) {
        cout << this->rankArr[i] << "\t";
    }
    cout << endl;
}

int DisjointSet::findSet(int node) {
    if (parent[node] != node) {
        return findSet(parent[node]);
    } else {
        return parent[node];
    }
}

//int DisjointSet::findSetWithPathCompressAndWeight(int x) {
//    if (parent[x] !=  x) {
//        weight[x] += weight[parent[x]]; // update weight of node x
//        parent[x] = findSetWithPathCompressAndWeight(parent[x]);
//    }
//    weight[x] += weight[parent[x]]; // update weight of node x
//    return parent[x];
//}

int DisjointSet::findSetWithPathCompressAndWeight(int x) {
    if (parent[x] !=  x) {
        weight[x] += weight[parent[x]]; // update weight of node x
        parent[x] = findSetWithPathCompressAndWeight(parent[x]);
        return parent[x];
    }
    else {
        return parent[x];
    }
}


void DisjointSet::unionByRank(int x, int y, int z) {
    int xrep = findSetWithPathCompressAndWeight(x); // representative of node x
    int yrep = findSetWithPathCompressAndWeight(y); // representative of node y
    if (xrep == yrep) {
        return; // do nothing since x and y are currently in the same set
    }
    else if (rankArr[xrep] > rankArr[yrep]) {
        parent[yrep] = xrep;
        weight[yrep] = z + weight[x] - weight[y];
    }
    else if (rankArr[xrep] < rankArr[yrep]) {
        parent[xrep] = yrep;
        weight[xrep] = -z - weight[x] + weight[y];
    }
    else {
        // rankArr[xrep] = rankArr[yrep]
        parent[xrep] = yrep;
        weight[xrep] = -z - weight[x] + weight[y];
        rankArr[yrep] += 1;
    }
}

bool DisjointSet::same(int x, int y) {
    if (findSetWithPathCompressAndWeight(x) == findSetWithPathCompressAndWeight(y)) {
        return true;
    }
    else {
        return false;
    }
}
