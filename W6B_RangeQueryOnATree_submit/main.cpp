#include <iostream>
#include <vector>

using namespace std;
const int INIVAL = 0;

struct WRTree{ // Weighted Rooted Tree
    vector<vector<int>> adj; // adjacent list
    vector<int> listOfNode; // list of nodes in order of appearance with depth-first search
    vector<int> left; // save the position of a node in the vector listOfNode
    vector<int> right; // save the position of the right-most child of a node in the vector listOfNode
    WRTree(int n); // constructor function
    void addEdge(int u, int v); // node v is a children node of node u
    void dfs(int node); // DFS: update vectors "listOfNode", "left" and "right"
};

struct SegmentTree{
    int n; //array size
    vector<int> tree; // store the segment tree
    vector<int> lazy; // store pending updates
    void initRMQ(int arrSize);
    void lazy_evaluate(int iNode, int sStart, int sEnd);
    int readUtil(int iNode, int sStart, int sEnd, int idx);
    int read(int idx);
    void updateRangeUtil(int iNode, int sStart, int sEnd, int uStart, int uEnd, int val);
    void updateRange(int uStart, int uEnd, int val);
};

int main()
{
    // get the weighted rooted tree
    int n; // number of nodes
    cin >> n;
    WRTree T(n);
    int x, y, z;
    for (int i = 0; i < n; i++) {
        cin >> x; // x = k_i
        for (int j = 0; j < x; j++) {
            cin >> y; // y = c_j
            T.addEdge(i, y); // add a new edge
        }
    }

    // convert the input tree to an array
    T.dfs(0); // start from the root (node 0)

    // create a segment tree for the array
    SegmentTree ST; // each node saves the distance from the root to a node
    ST.initRMQ(n);

    // process queries
    int q; // no. of queries
    cin >> q;
    for (int i=0; i<q; i++) {
        cin >> x;
        if (x==1) { // getSum() query
            cin >> y; // y = u (a vertex)
            cout << ST.read(T.left[y]) << "\n";
        }
        else if (x==0) { // add() query
            cin >> y >> z; // y = v (vertex), z = w (weight)
            ST.updateRange(T.left[y], T.right[y], z); // add z to records indexed from T.left[y] to T.right[y]
        }
    }

    return 0;
}

WRTree::WRTree(int n) {
    adj.resize(n);
    left.resize(n);
    right.resize(n);
}

void WRTree::addEdge(int u, int v) {
    adj[u].push_back(v);
}

void WRTree::dfs(int node) {
    listOfNode.push_back(node);
    left[node] = listOfNode.size()-1; // index of the already-visited node in the array listOfNode
    for (int i=0; i<adj[node].size(); i++) {
        int v = adj[node][i];
        dfs(v);
    }
    right[node] = listOfNode.size()-1;
}

void SegmentTree::initRMQ(int arrSize) {
    n = 1;
    while (n<arrSize) {n *= 2;}
    tree = vector<int>(2*n-1, INIVAL);
    lazy = vector<int>(2*n-1, INIVAL);
}

void SegmentTree::lazy_evaluate(int iNode, int sStart, int sEnd) {
    if (lazy[iNode] != 0) {
        // apply the pending update stored in the corresponding lazy node
        tree[iNode] += (sStart-sEnd+1)*lazy[iNode];
        // not a leaf node
        if (sStart!=sEnd) {
            lazy[iNode*2+1] += lazy[iNode];
            lazy[iNode*2+2] += lazy[iNode];
        }
        // erase the mark for the pending update of this node
        lazy[iNode] = 0;
    }
}

int SegmentTree::readUtil(int iNode, int sStart, int sEnd, int idx) {
    // check pending update
    lazy_evaluate(iNode, sStart, sEnd);

    // leaf node
    if (sStart==sEnd){return tree[iNode];}

    // not a leaf node
    int mid = (sStart+sEnd)/2;
    if (sStart <= idx && idx <= mid) {return readUtil(iNode*2+1, sStart, mid, idx);}
    else {return readUtil(iNode*2+2, mid+1, sEnd, idx);}
}

int SegmentTree::read(int idx) {
    return readUtil(0, 0, n-1, idx);
}

void SegmentTree::updateRangeUtil(int iNode, int sStart, int sEnd, int uStart, int uEnd, int val) {
    // apply pending updates (if any)
    lazy_evaluate(iNode, sStart, sEnd);

    // out of range
    if (sStart > uEnd || sEnd < uStart || sStart > sEnd) {return;}

    // current segment is fully in range
    if (sStart >= uStart && sEnd <= uEnd) {
        // update the current node
        tree[iNode] += (sStart-sEnd+1)*val;
        // in case not a leaf node -> postpone the update for children nodes
        if (sStart != sEnd) {
            lazy[iNode*2+1] += val;
            lazy[iNode*2+2] += val;
        }
        return;
    }

    // not completely in range, but overlapped -> recur throughout children nodes
    int mid = (sStart + sEnd)/2;
    updateRangeUtil(iNode*2+1, sStart, mid, uStart, uEnd, val);
    updateRangeUtil(iNode*2+2, mid+1, sEnd, uStart, uEnd, val);
    // then, use the result of children calls to update the current node
    tree[iNode] = tree[iNode*2+1] + tree[iNode*2+2];
}

void SegmentTree::updateRange(int uStart, int uEnd, int val) {
    updateRangeUtil(0, 0, n-1, uStart, uEnd, val);
}
