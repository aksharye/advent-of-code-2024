#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

int main() {
    // lists
    vector<ll> a, b;
    
    // read in lists
    ll ct = 0;
    ll x;
    while (cin >> x) {
        if (ct % 2) {
            b.pb(x);
        } else {
            a.pb(x);
        }
        ct++;
    }

    // list size
    ll n = ct / 2;

    // sort lists
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    // find distance
    ll dist = 0;
    for (int i = 0; i < n; i++) {
        dist += abs(a[i] - b[i]);
    }

    cout << dist << endl;
}