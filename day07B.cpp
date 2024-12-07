#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

int main() {    
    // answer counter
    ll cal = 0;

    // read in ops
    string line;
    while (getline(cin, line)) {
        istringstream iss (line);

        // read in target
        string t; iss >> t;
        if (t.size() == 0) break;
        t.pop_back();
        ll target = stoll(t);

        // read in numbers
        vector<ll> v;
        ll x;
        while (iss >> x) v.pb(x);

        // iterate over all 3^n-1 op combos
        ll n = v.size();

        bool works = false;

        // find 3^n-1
        ll g = 1; ll m = n-1; while (m--) g*=3;

        for (int i = 0; i < g; i++) {
            ll z = i;
            ll curr = v[0];
            for (int j = 0; j < n-1; j++) {
                if (z % 3 == 0) {
                    curr *= v[j+1];
                } else if (z % 3 == 1) {
                    curr += v[j+1];
                } else {
                    string ns = to_string(curr) + to_string(v[j+1]);
                    curr = stoll(ns);
                }
                z /= 3;
            }

            // check if curr is target
            if (curr == target) {
                works = true;
                break;
            }
        }

        // works -> add to total
        if (works) cal += target;
    }
    
    cout << cal << endl;
}