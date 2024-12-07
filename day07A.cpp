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

        // iterate over all 2^n-1 op combos
        ll n = v.size();

        bool works = false;
        for (int i = 0; i < (1 << (n-1)); i++) {
            ll curr = v[0];
            for (int j = 0; j < n-1; j++) {
                if ((1 << j) & i) {
                    curr *= v[j+1];
                } else {
                    curr += v[j+1];
                }
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