#include <iostream>
#include<vector>
#include<string>
//#include<fstream>

using namespace std;

const bool FREE = false; // not threatened by any queen
const bool NOT_FREE = true; // threatened by a queen

struct chess{
    int N; // size of the chess board: N x N
    vector<int> row; // row(i) = N -> no queen at $i$-th row
    vector<bool> col, dpos, dneg;
    vector<int> isFixed;
    chess(int n);
    void printBoard();
    void putQueen(int i);
    void getInput();
//    void getInput2(string filename);
//    void test();
};

chess::chess(int n) {
    N = n;
    row = vector<int>(n,n);
    col = vector<bool>(n,FREE);
    dpos = vector<bool>(2*n-1,FREE);
    dneg = vector<bool>(2*n-1,FREE);
    isFixed = vector<int>(N,N);
}

void chess::printBoard() {
    for (int i = 0; i < N; i++) {
        string temp = "........";
        temp[row[i]] = 'Q';
        cout << temp << "\n";
    }
}

void chess::putQueen(int i) {
    if (i==N) {
        printBoard();
        return;
    }
    if (isFixed[i]<N) { // the queen for i-th row is given as input
        row[i] = isFixed[i];
        col[isFixed[i]] = dpos[i+isFixed[i]] = dneg[i-isFixed[i]+N-1] = NOT_FREE;
        putQueen(i+1);
        //test();
    }
    else {
        for (int j = 0; j < N; j++) {
            if ((col[j]==NOT_FREE) || (dpos[i+j]==NOT_FREE) || (dneg[i-j+N-1]==NOT_FREE)) {
                continue;
            }
            //put a queen at (i,j)
            row[i] = j;
            col[j] = dpos[i+j] = dneg[i-j+N-1] = NOT_FREE;
            //try the next row
            putQueen(i+1);
            //remove the queen at (i,j) for backtracking
            col[j] = FREE; dpos[i+j] = FREE; dneg[i-j+N-1] = FREE;
        }
    }
}

void chess::getInput() {
    int k, r, c;
    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> r >> c;
        row[r] = c;
        col[c] = NOT_FREE;
        dpos[r+c] = NOT_FREE;
        dneg[r-c+N-1] = NOT_FREE;
        isFixed[r] = c;
    }
}

//void chess::getInput2(string filename) {
//    ifstream infile(filename);
//    int k, r, c;
//    infile >> k;
//    for (int i = 0; i < k; i++) {
//        infile >> r >> c;
//        row[r] = c;
//        col[c] = NOT_FREE;
//        dpos[r+c] = NOT_FREE;
//        dneg[r-c+N-1] = NOT_FREE;
//        isFixed[r] = c;
//    }
//    infile.close();
//}

//void chess::test() {
//    cout << "row:\t";
//    for (int i = 0; i < 8; i++) {
//        cout << (int) row[i] << " ";
//    }
//    cout << "\n";
//    cout << "col:\t";
//    for (int i = 0; i < 8; i++) {
//        cout << (int) col[i] << " ";
//    }
//    cout << "\n";
//    cout << "dpos:\t";
//    for (int i = 0; i < 15; i++) {
//        cout << (int) dpos[i] << " ";
//    }
//    cout << "\n";
//    cout << "dneg:\t";
//    for (int i = 0; i < 15; i++) {
//        cout << (int) dneg[i] << " ";
//    }
//    cout << "\n";
//}

int main()
{
    chess mychess(8);
    mychess.getInput();
    //mychess.getInput2("in.txt");
    //mychess.test();
    //mychess.printBoard();
    mychess.putQueen(0);
    return 0;
}
