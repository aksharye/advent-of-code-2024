#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

int main() {
    // list + frequency map
    vector<ll> a;
    map<ll,ll> b;
    
    // read in lists
    ll ct = 0;
    ll x;
    while (cin >> x) {
        if (ct % 2) {
            b[x]++;
        } else {
            a.pb(x);
        }
        ct++;
    }

    // list size
    ll n = ct / 2;

    // find similarity
    ll sim = 0;
    for (int i = 0; i < n; i++) {
        sim += a[i] * b[a[i]];
    }

    cout << sim << endl;
}