#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

int main() {    
    // checksum counter
    ll checksum = 0;

    // read in disk map
    string line; cin >> line;

    // vector to keep track of disk space
    vector<ll> v;

    // calculate disk space
    // nonnegative int is file id
    // -1 is blank space
    ll ct = 0;
    for (int i = 0; i < line.size(); i++) {
        ll k = (ll) (line[i] - '0');
        if (i % 2 == 0) {
            while (k--) v.pb(ct);
            ct++;
        } else {
            while (k--) v.pb(-1);
        }
    }
    
    // two pointers to simulate file moving
    ll L = 0;
    ll R = v.size()-1;

    // perform swaps when can move files left
    while (R > L) {
        while (v[L] != -1) L++;
        while (v[R] == -1) R--;
        if (R <= L) break;
        v[L] = v[R];
        v[R] = -1;
    }

    // compute checksum
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == -1) continue;
        checksum += v[i] * i;
    }

    cout << checksum << endl;
}