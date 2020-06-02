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

void getin(string fn);
void getin();

int main()
{
    //getin("in.txt");
    getin();
    return 0;
}

void getin(){
    SegmentTree ist;
    int N, L, a;
    //
    cin >> N >> L;
    ist.initRMQ(N);
    vector<int> out(N-L+1);
    // get the whole array
    for (int i = 0; i < N; i++) {
        cin >> a;
        ist.update(i,a);
    }
    // calculate output
    for (int i = 0; i < N-L; i++) {
        cout << ist.findMin(i, i+L-1) << " ";
    }
    cout << ist.findMin(N-L, N-1);
    cout << endl;
}

void getin(string fn) {
    ifstream infile(fn);
    SegmentTree ist;
    int N, L, a;
    //
    infile >> N >> L;
    ist.initRMQ(N);
    vector<int> out(N-L+1);
    // get the whole array
    for (int i = 0; i < N; i++) {
        infile >> a;
        ist.update(i,a);
    }
    // calculate output
    for (int i = 0; i <= N-L; i++) {
        cout << ist.findMin(i, i+L-1) << " ";
    }
    cout << endl;
    infile.close();
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
