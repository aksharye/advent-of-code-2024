#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

// simulate stone process for given depth
ll stone_count(ll k, ll depth) {
    if (depth == 0) return 1;
    if (k == 0) return stone_count(1, depth-1);

    string sk = to_string(k);
    if (sk.size() % 2 == 0) {
        ll n = sk.size() / 2;
        return stone_count(stoll(sk.substr(0,n)),depth-1) + stone_count(stoll(sk.substr(n,n)),depth-1); 
    }

    return stone_count(2024*k, depth-1);
}

int main() {
    // stone counter
    ll stones = 0;

    // read in input and count how many stones originate from one
    ll x;
    while (cin >> x) stones += stone_count(x, 25);
    
    cout << stones << endl;
}