#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

// store key and lock representations
vector<vector<ll>> keys;
vector<vector<ll>> locks;

// process incoming grids to key and lock representations
void process (vector<string> grid) {
    if (grid[0][0] == '#') {
        // lock
        vector<ll> v;
        for (int i = 0; i < 5; i++) {
            ll j = 0;
            while (j < 7 && grid[j][i] == '#') {
                j++;
            }
            v.pb(j-1);
        }

        locks.pb(v);
    } else {
        // key
        reverse(grid.begin(), grid.end());
        vector<ll> v;
        for (int i = 0; i < 5; i++) {
            ll j = 0;
            while (j < 7 && grid[j][i] == '#') {
                j++;
            }
            v.pb(j-1);
        }

        keys.pb(v);
    }
}

int main() {
    vector<string> grid;

    // read in grids
    // process last grid and track new grid at 7 lines
    string line;
    while (getline(cin, line)) {
        if (line.size() == 0) continue;

        grid.pb(line);

        if (grid.size() == 7) {
            process(grid);
            grid.clear();
        }
    }

    // find all possible combos by iterating over 
    // all possible pairs of locks and keys
    ll combos = 0;
    for (auto key : keys) {
        for (auto lock : locks) {
            bool fits = true;
            for (int j = 0; j < 5; j++) {
                // if overlaps, then they dont fit
                if (key[j] + lock[j] > 5) {
                    fits = false;
                }
            }
            combos += fits;
        }
    }

    cout << combos << endl;
}