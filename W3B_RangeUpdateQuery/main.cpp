#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int INIVAL = (1<<31) -1;

class SegmentTree{
public:
    int n; //array size
    vector<int> tree; // store the segment tree
    vector<int> lazy; // store pending updates
    //
    void initRMQ(int arrSize);
    void update(int idx, int val);
    void lazy_evaluate(int iNode, int sStart, int sEnd);
    int readUtil(int iNode, int sStart, int sEnd, int idx);
    int read(int idx);
    void updateRangeUtil(int iNode, int sStart, int sEnd, int uStart, int uEnd, int val);
    void updateRange(int uStart, int uEnd, int val);
    int findMinUtil(int iNode, int nStart, int nEnd, int qLeft, int qRight);
    int findMin(int fLeft, int fRight);
    //
    void printTree();
};

int main()
{
    // get input from cmd window
    SegmentTree ist;
    int n, q, x, y, z, t;
    cin >> n >> q;
    ist.initRMQ(n);
    vector<int> out;
    for (int i = 0; i < q; i++) {
        cin >> x;
        if (x==0) {
            cin >> y >> z >> t;
            ist.updateRange(y, z, t);
        }
        else if (x==1) {
            cin >> y;
            out.push_back(ist.read(y));
        }
    }

//    // get input from file
//    SegmentTree ist;
//    ifstream infile("in_sam2.txt");
//    int n, q, x, y, z, t;
//    infile >> n >> q;
//    ist.initRMQ(n);
//    vector<int> out;
//    for (int i = 0; i < q; i++) {
//        infile >> x;
//        if (x==0) {
//            infile >> y >> z >> t;
//            ist.updateRange(y, z, t);
//            ist.printTree();
//        }
//        else if (x==1) {
//            infile >> y;
//            out.push_back(ist.read(y));
//        }
//    }
//    infile.close();

    // output
    for (int i = 0; i < out.size(); i++) {cout << fixed << out[i] << "\n";}
    return 0;
}

void SegmentTree::initRMQ(int arrSize) {
    n = 1;
    while (n<arrSize) {n *= 2;}
    tree = vector<int>(2*n-1, INIVAL);
    lazy = vector<int>(2*n-1, -1);
}

void SegmentTree::printTree() {
    cout << "tree[]: " << "\t";
    for (int i = 0; i < tree.size(); i++) {cout << fixed << this->tree[i] << "\t";}
    cout << "\n" << "lazy[]: " << "\t";
    for (int i = 0; i < lazy.size(); i++) {cout << fixed << this->lazy[i] << "\t";}
    cout << endl;
}

void SegmentTree::update(int idx, int val) {
    idx += n - 1;
    tree[idx] = val;
    while (idx > 0) {
        idx = (idx-1)/2;
        tree[idx] = min(tree[idx*2+1], tree[idx*2+2]);
    }
}

void SegmentTree::lazy_evaluate(int iNode, int sStart, int sEnd) {
    if (lazy[iNode] != -1) {
        // apply the pending update stored in the corresponding lazy node
        tree[iNode] = lazy[iNode]; // since all elements in the range presented by this node are the same = lazy[iNode]
        // not a leaf node
        if (sStart!=sEnd) {
            lazy[iNode*2+1] = lazy[iNode];
            lazy[iNode*2+2] = lazy[iNode];
        }
        // erase the mark for the pending update of this node
        lazy[iNode] = -1;
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
        tree[iNode] = val;
        // in case not a leaf node -> postpone the update for children nodes
        if (sStart != sEnd) {
            lazy[iNode*2+1] = val;
            lazy[iNode*2+2] = val;
        }
        return;
    }

    // not completely in range, but overlapped -> recur throughout children nodes
    int mid = (sStart + sEnd)/2;
    updateRangeUtil(iNode*2+1, sStart, mid, uStart, uEnd, val);
    updateRangeUtil(iNode*2+2, mid+1, sEnd, uStart, uEnd, val);
    // then, use the result of children calls to update the current node
    tree[iNode] = min(tree[iNode*2+1], tree[iNode*2+2]);
}

void SegmentTree::updateRange(int uStart, int uEnd, int val) {
    updateRangeUtil(0, 0, n-1, uStart, uEnd, val);
}

int SegmentTree::findMin(int fLeft, int fRight) {
    return findMinUtil(0, 0, n-1, fLeft, fRight);
}

// given searching range a[l], ... a[r]
int SegmentTree::findMinUtil(int iNode, int nStart, int nEnd, int qLeft, int qRight) {
    if ((qRight < nStart) || (nEnd < qLeft)) {
        // the range presented by the current node is completely outside the given (searching) range
        return INIVAL;
    }
    else if ((qLeft <= nStart) && (nEnd <= qRight)) {
        // the range presented by the current node is completely inside the given range
        return tree[iNode];
    }
    else {
        // the range presented by the current node is  partly inside and partly outside the given range
        int mid = (nStart+nEnd)/2;
        int vl = findMinUtil(2*iNode+1, nStart, mid, qLeft, qRight);
        int vr = findMinUtil(2*iNode+2, mid+1, nEnd, qLeft, qRight);
        return min(vl, vr);
    }
}
