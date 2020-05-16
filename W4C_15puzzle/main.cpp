#include <bits/stdc++.h>
using namespace std;

const int N = 4; // N x N board
const int max_depth = 45;

struct Node{
    unsigned long long int id;  // hash key
    int mat[N][N];              // to save the N x N board
    int x0, y0;                 // location of the blank square
    int cost;                   // minimum number of movements to reach the destination Node
    int level;                  // no. of movements so far to reach this Node
    Node(){}                    // construction function #1
    Node(int matrix_[N][N], int x0_, int y0_, int cost_, int level_){
        memcpy(mat, matrix_, sizeof(mat));
        x0 = x0_;  y0 = y0_;
        cost = cost_;
        level = level_;
    }    // construction function #2
};

int calCostUtil(int mat[N][N], int i, int j) {
    int cost  = 0;
    if (mat[i][j] != 0) {
        int x1 = (int) (mat[i][j]-1) / N;
        int y1 = (int) (mat[i][j]-1) - N*x1;
        cost = abs(i-x1) + abs(j-y1);
    }
    return cost;
}

int calCost(int mat[N][N]) {
    int cost = 0;
    for (int i = 0; i < N; i++) {
        for (int j=0; j<N; j++) {
            if (mat[i][j] != 0) {
                cost += calCostUtil(mat, i, j);
            }
        }
    }
    return cost;
}

Node getInput(string fn) {
    ifstream infile(fn);
    int tmp, x0, y0;
    int mat[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            infile >> tmp;
            mat[i][j] = tmp;
            if (tmp==0) {x0=i; y0=j;}
        }
    }
    Node root(mat, x0, y0, calCost(mat), 0);
    infile.close();
    return root;
}

Node getInput() {
    int tmp, x0, y0;
    int mat[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> tmp;
            mat[i][j] = tmp;
            if (tmp==0) {x0=i; y0=j;}
        }
    }
    Node root(mat, x0, y0, calCost(mat), 0);
    return root;
}

void printNode(Node nd) {
    for (int i=0; i<N; i++) {
        for (int j = 0; j < N; j++) {
            cout << nd.mat[i][j] <<"  ";
        }
        cout << "\n";
    }
    cout << "(" << nd.x0 << ", " << nd.y0 << ")\n";
    cout << "cost: " << nd.cost << "\n";
    cout << "level: " << nd.level << "\n";
}

unsigned long long int genHashKey(int mat[N][N]) {
    unsigned long long int tmp = 0;
    for (int i=0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tmp += mat[i][j]*pow(10, i*N+j);
        }
    }
    return tmp;
}

bool isMoveValid(int x0, int y0, int mrow, int mcol) {
    if ((x0+mrow>=0) && (x0+mrow<N) && (y0+mcol>=0) && (y0+mcol<N)) {
        return true;
    }
    else {
        return false;
    }
}

//              up      down    left    right
int mrow[] = {  1,      -1,     0,      0       };
int mcol[] = {  0,      0,      -1,     1       };

// flag
bool isSolved = false;
set<unsigned long long int> mylist;     // save all hash keys of nodes visited

bool solveUtil(Node* node, int limit) {
    if (!isSolved) {
        // if destination node is reached: print current node's level
        if (node->cost==0) {
            cout << node->level << "\n";  // minimum no. of steps to reach the goal
            isSolved = true;
            return true;
        }

        // else: visit children nodes (depth-first search)
        for (int imove = 0; imove < 4; imove++) {
            if(isMoveValid(node->x0, node->y0, mrow[imove], mcol[imove])) {
                int x0_new = node->x0 + mrow[imove];
                int y0_new = node->y0 + mcol[imove];
                int mat[N][N];
                memcpy(mat, node->mat, sizeof(mat));
                swap(mat[node->x0][node->y0], mat[x0_new][y0_new]);
                int cost = calCost(mat);
                // check whether depth limit is reached
                if (node->level + cost <= limit) {
                    //check whether the node is visited before
                    unsigned long long int id = genHashKey(mat);
                    if (mylist.find(id)==mylist.end()) {
                        Node newNode(mat, x0_new, y0_new, cost, node->level+1);
                        mylist.insert(id);
                        solveUtil(&newNode, limit);
                        // if cannot reach the goal -> erase the node from list for backtracking
                        mylist.erase(id);
                    }
                }
            }
        }

        // after visiting all children nodes but the goal has not reached
        return false;
    }
}

void solve(Node* root, int depth_limit) {
    // iterative deepening DFS
    for (int i = root->cost; i < depth_limit; i++) {
        mylist.clear();
        mylist.insert(genHashKey(root->mat));
        if (solveUtil(root, i)) {return;};
    }
}

int main() {
    Node root = getInput("in.txt");  // root node
    //Node root = getInput();  // root node
    solve(&root, max_depth);
    return 0;
}
