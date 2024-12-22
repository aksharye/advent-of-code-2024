#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back
using pll = pair<ll,ll>;

int main() {
    ll MOD = 16777216; // mod for prune op

    // keep track of bananas at given history
    map<pair<pll,pll>, ll> bananahist;

    // read in secret numbers
    string line;
    while (getline(cin, line)) {
        // read in secret
        ll secret = stoll(line);

        vector<ll> hist; // last four days history
        set<pair<pll,pll>> seen; // keep track of seen histories (can't repeat)

        // run for 2000 iterations
        ll iter = 2000;
        while (iter--) {
            ll prev = secret;
            secret ^= (secret * 64);
            secret %= MOD;

            secret ^= (secret / 32);
            secret %= MOD;

            secret ^= (secret * 2048);
            secret %= MOD;

            ll diff = (secret % 10) - (prev % 10);
            hist.pb(diff);

            if (hist.size() > 4) hist.erase(hist.begin() + 0);

            if (hist.size() == 4) {
                pair<pll,pll> lastfour = {{hist[0], hist[1]}, {hist[2], hist[3]}};
                if (!seen.count(lastfour)) bananahist[lastfour] += secret % 10;
                seen.insert(lastfour);
            }
        }
    }

    // find maximum across all histories
    ll maxbananas = 0;
    for (auto [k, v] : bananahist) maxbananas = max(maxbananas, v);

    cout << maxbananas << endl;
}