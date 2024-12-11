#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

// add memory
map<pair<ll,ll>,ll> track;

// simulate stone process for given depth, but use memory for repeated states
ll stone_count(ll k, ll depth) {
    if (track.count({k, depth})) return track[{k, depth}];

    if (depth == 0) return 1;
    if (k == 0) {
        track[{k, depth}] = stone_count(1, depth-1);
        return track[{k, depth}];
    }

    string sk = to_string(k);
    if (sk.size() % 2 == 0) {
        ll n = sk.size() / 2;
        track[{k, depth}] = stone_count(stoll(sk.substr(0,n)),depth-1) + stone_count(stoll(sk.substr(n,n)),depth-1);
        return track[{k, depth}];
    }

    track[{k, depth}] = stone_count(2024*k, depth-1);
    return track[{k, depth}];
}

int main() {
    // stone counter
    ll stones = 0;

    // read in input and count how many stones originate from one
    ll x;
    while (cin >> x) stones += stone_count(x, 75);
    
    cout << stones << endl;
}