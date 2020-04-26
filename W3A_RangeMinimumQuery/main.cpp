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
    int query(int a, int b, int k, int l, int r);
    //
    void printTree();
};

int main()
{
    // input from cmd window
    SegmentTree ist;
    int n, q;
    cin >> n >> q;
    ist.initRMQ(n);
    vector<int> out;
    int x, y, z;
    for (int i = 0; i < q; i++) {
        cin >> x >> y >> z;
        if (x == 0) { // update()
            ist.update(y, z);
        }
        else if (x == 1) { // findMin()
            out.push_back(ist.findMin(y, z));
        }
    }

//    // input from file
//    SegmentTree ist;
//    ifstream infile("in6.txt");
//    int n, q;
//    infile >> n >> q;
//    ist.initRMQ(n);
//    vector<int> out;
//    int x, y, z;
//    for (int i = 0; i < q; i++) {
//        infile >> x >> y >> z;
//        if (x == 0) { // update()
//            ist.update(y, z);
//            //ist.printTree();
//        }
//        else if (x == 1) { // findMin()
//            out.push_back(ist.findMin(y, z));
//            //ist.printTree();
//        }
//    }

    // output
    for (int i = 0; i < out.size(); i++) {
        cout << fixed << out[i] << "\n";
    }

    return 0;
}

void SegmentTree::initRMQ(int n_) {
    n = 1;
    while (n < n_) {n *= 2;}
    D = vector<int>(2*n-1, INIVAL);
}

void SegmentTree::printTree() {
    for (int i = 0; i < n; i++) {
        cout << fixed << this->D[i] << "\n";
    }
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
    return query(a, b+1, 0, 0, n);
}

int SegmentTree::query(int a, int b, int k, int l, int r) {
    if ((r <= a) || (b <= l)) { // case 1
        return INIVAL;
    }
    else if ((a <= l) && (r <= b)) { // case 2
        return D[k];
    }
    else { // case 3
        int vl = query(a, b, k*2+1, l, (l+r)/2);
        int vr = query(a, b, k*2+2, (l+r)/2, r);
        return min(vl, vr);
    }
}
