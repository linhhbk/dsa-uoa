#include <iostream>
#include <fstream>

using namespace std;

class DisjSet{
public:
    int numOfNode; // number of nodes
    int* parent; // parent nodes
    int* rankArr; //rankArr of each node
    DisjSet(int x);
    int findSet(int node);
    int findSetWithPC(int x); // findSet() operation with path compression
    void unionByRank(int x, int y);
    bool same(int x, int y); // check whether x and y are in the same set
};

int main()
{
//    // import data from a txt file
//    int n; // number of nodes
//    int q; // number of queries
//    int a, b, c;
//    ifstream infile("input.txt");
//    infile >> n >> q;
//    cout << n << " " << q << endl;
//    DisjSet mySet(n);
//    char output[q]; // sample output: 0 -> skip, 1 -> return yes ("
//    for (int i = 0; i < q; i++) {
//        infile >> a >> b >> c;
//        cout << a << " " <<  b << " " << c << endl;
//        if (a == 0) { // "unite(x,y)"
//            mySet.unionByRank(b, c);
//            output[i] = 'n';
//        }
//        else if (a == 1) { // "same(x, y)"
//            if (mySet.same(b, c)) { output[i] = '1'; }
//            else { output[i] = '0'; }
//        }
//    }
//    infile.close();

    // import data from command line
    int n; // number of nodes
    int q; // number of queries
    int a, b, c;
    cin >> n >> q;
    DisjSet mySet(n);
    char output[q]; // sample output: 0 -> skip, 1 -> return yes ("
    for (int i = 0; i < q; i++) {
        cin >> a >> b >> c;
        if (a == 0) { // "unite(x,y)"
            mySet.unionByRank(b, c);
            output[i] = 'n';
        }
        else if (a == 1) { // "same(x, y)"
            if (mySet.same(b, c)) { output[i] = '1'; }
            else { output[i] = '0'; }
        }
    }

    //print out the output
    for (int i = 0; i < q; i++) {
        if (output[i] != 'n') { cout << output[i] << endl; }
    }
    return 0;
}

DisjSet::DisjSet(int x) {
    numOfNode = x;
    parent = new int[numOfNode];
    rankArr = new int[numOfNode];
    for (int i = 0; i < numOfNode; i++) {
        parent[i] = i;
        rankArr[i] = 1;
    }
}

int DisjSet::findSet(int node) {
    if (parent[node] != node) {
        return findSet(parent[node]);
    } else {
        return parent[node];
    }
}

int DisjSet::findSetWithPC(int x) {
    if (parent[x] !=  x) {
        parent[x] = findSetWithPC(parent[x]);
    }
    return parent[x];
}

void DisjSet::unionByRank(int x, int y) {
    int xrep = findSetWithPC(x); // representative of node x
    int yrep = findSetWithPC(y); // representative of node y
    if (xrep == yrep) {
        return; // do nothing since x and y are curently in the same set
    }
    else if (rankArr[xrep] > rankArr[yrep]) {
        parent[yrep] = xrep;
    }
    else if (rankArr[xrep] < rankArr[yrep]) {
        parent[xrep] = yrep;
    }
    else {
        // rankArr[xrep] = rankArr[yrep]
        parent[xrep] = yrep;
        rankArr[yrep] += 1;
    }
}

bool DisjSet::same(int x, int y) {
    if (findSetWithPC(x) == findSetWithPC(y)) {
        return true;
    }
    else {
        return false;
    }
}
