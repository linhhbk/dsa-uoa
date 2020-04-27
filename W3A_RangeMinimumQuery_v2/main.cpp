#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int INIVAL = (1<<31) -1;

class SegmentTree{
public:
    int n; //array size
    vector<int> D; //minimum values for the range represented by node i of the segment tree
    //
    void initRMQ(int n_);
    void update(int k, int x);
    int findMin(int a, int b);
    int query(int node, int start, int end_, int l, int r);
    //
    void printTree();
};

int main()
{
//    // input from cmd window
//    SegmentTree ist;
//    int n, q;
//    cin >> n >> q;
//    ist.initRMQ(n);
//    vector<int> out;
//    int x, y, z;
//    for (int i = 0; i < q; i++) {
//        cin >> x >> y >> z;
//        if (x == 0) { // update()
//            ist.update(y, z);
//        }
//        else if (x == 1) { // findMin()
//            out.push_back(ist.findMin(y, z));
//        }
//    }

    // input from file
    SegmentTree ist;
    ifstream infile("in6.txt");
    int n, q;
    infile >> n >> q;
    ist.initRMQ(n);
    vector<int> out;
    int x, y, z;
    for (int i = 0; i < q; i++) {
        infile >> x >> y >> z;
        if (x == 0) { // update()
            ist.update(y, z);
            //ist.printTree();
        }
        else if (x == 1) { // findMin()
            out.push_back(ist.findMin(y, z));
            //cout << out.back() << endl;
        }
    }

    // output
    for (int i = 0; i < out.size(); i++) {
        cout << fixed << out[i] << "\n";
    }

    return 0;
}

void SegmentTree::initRMQ(int n_) {
    n = 1;
    while (n<n_) {n *= 2;}
    D = vector<int>(2*n-1, INIVAL);
}

void SegmentTree::printTree() {
    cout << "segtree: " << endl;
    for (int i = 0; i < D.size(); i++) {
        cout << fixed << this->D[i] << "\t";
    }
    cout << endl;
}

void SegmentTree::update(int k, int x) {
    k += n - 1;
    D[k] = x;
    while (k > 0) {
        k = (k-1)/2;
        D[k] = min(D[k*2+1], D[k*2+2]);
    }
}

int SegmentTree::findMin(int a, int b) {
    return query(0, 0, n-1, a, b);
}

// given searching range a[l], ... a[r]
int SegmentTree::query(int node, int start, int end_, int l, int r) {
    if ((r < start) || (end_ < l)) {
        // the range presented by the current node is completely outside the given (searching) range
        return INIVAL;
    }
    else if ((l <= start) && (end_ <= r)) {
        // completely inside the given range
        return D[node];
    }
    else { // partly inside and partly outside
        int mid = (start+end_)/2;
        int vl = query(2*node+1, start, mid, l, r);
        int vr = query(2*node+2, mid+1, end_, l, r);
        return min(vl, vr);
    }
}
