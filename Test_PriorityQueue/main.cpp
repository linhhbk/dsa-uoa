#include <iostream>
#include <queue>

using namespace std;

class edge{
public:
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
    priority_queue<edge> ique;
    edge e1(0, 1, 1), e2(0, 2, 2), e3(1, 2, 3);
    ique.push(e1); ique.push(e2); ique.push(e3);
    edge e = ique.top();
    cout << e.src << " " << e.des << " " << e.wei << "\n";
    return 0;
}
