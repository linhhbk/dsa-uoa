/* Using priority queue in Cpp
Note: priority_queue in Cpp adapts the vector container to maintain items in an sorted order.
*/
#include <iostream>
#include <queue>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

struct edge{
    int src;
    int des;
    int wei;
    edge(int src_, int des_, int wei_) : src(src_), des(des_), wei(wei_) {}
    bool operator < ( const edge &e2) const {
        return this->wei > e2.wei;
    }
};

int main()
{
    /*using priority_queue*/
    edge e1(0, 1, 1), e2(0, 2, 2), e3(1, 2, 3);
    priority_queue<edge> ique;
    ique.push(e1); ique.push(e2); ique.push(e3);
    edge e = ique.top();
    cout << e.src << " " << e.des << " " << e.wei << "\n";

//    /* Second approach: using vector, to extract the minimum element -> use *min_element function */
//    edge e1(0, 1, 1), e2(0, 2, 2), e3(1, 2, 3);
//    vector<edge> myvec;
//    myvec.push_back(e1);
//    myvec.push_back(e2);
//    myvec.push_back(e3);
//    cout << "min edge: \n";
//    edge me = *min_element(myvec.begin(), myvec.end());
//    cout << me.src << " " << me.des << " " << me.wei << "\n";
//    myvec.erase(myvec.begin());
//    cout << "after erase:\n";
//    for (int i = 0; i < myvec.size(); i++) {
//        cout << myvec[i].src << " " << myvec[i].des << " " << myvec[i].wei << endl;
//    }

    return 0;
}
