#include <iostream>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

int mynumber = 0;
int add(int x) {
    if (x == 10) {
        return mynumber;
    }
    else {
        mynumber += add(x);
    }
}

void test(int x) {
    if (x==0) {
        cout << x << "\n";
        return;
    }
    cout << x+1 << "\n";
}

set<int> mylist;

int main()
{
    //cout << add(20);
    // test(1);
    mylist.insert(1);
    if (mylist.find(1)== mylist.end()) {
        cout << "error!" << endl;
    }
    else {
        cout << "no element!\n";
    }
    return 0;
}
