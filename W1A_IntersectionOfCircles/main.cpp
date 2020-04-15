#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int main() {
    float cx1, cy1, r1, cx2, cy2, r2;
    cin >> cx1 >> cy1 >> r1 >> cx2 >> cy2 >> r2;
    float d = sqrt(pow(cx1-cx2, 2) + pow(cy1-cy2, 2));
    if (r1 + r2 < d) {
        cout << "4\n";
    } else if (r1 + r2 == d) {
        cout << "3\n";
    } else { // r1 + r2 > d
        float sub = abs(r1-r2);
        if (sub < d) {
            cout << "2\n";
        } else if (sub == d) {
            cout << "1\n";
        } else { // |r1-r2| > d
            cout << "0\n";
        }
    }
    return 0;
}
