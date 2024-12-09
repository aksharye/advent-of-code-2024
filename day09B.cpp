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

    // keep track of file chunks and empty chunks
    vector<pair<ll,ll>> range;
    vector<pair<ll,ll>> empty;

    // keep track of current file position
    ll curr = 0;
    for (int i = 0; i < line.size(); i++) {
        ll k = (ll) (line[i] - '0');
        ll zk = k;
        if (i % 2 == 0) {
            while (k--) v.pb(ct);
            ct++;
            range.pb({curr, curr+zk});
        } else {
            while (k--) v.pb(-1);
            empty.pb({curr, curr+zk});
        }
        curr += zk;
    }

    // swap file chunks to left if space is available
    for (int i = range.size() - 1; i >= 0; i--) {
        ll z = range[i].second - range[i].first;

        for (int j = 0; j < empty.size(); j++) {
            // left check (break because sorted)
            if (empty[j].first > range[i].first) break;

            // length check
            ll y = empty[j].second - empty[j].first;
            if (y < z) continue;

            // perform swap
            for (int k = empty[j].first; k < empty[j].first + z; k++) {
                v[k] = i;
            }

            for (int k = range[i].first; k < range[i].first + z; k++) {
                v[k] = -1;
            }

            // update empty range space
            empty[j].first = empty[j].first + z;

            break;
        }
    }

    // compute checksum
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == -1) continue;
        checksum += v[i] * i;
    }

    cout << checksum << endl;
}