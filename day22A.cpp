#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back
using pll = pair<ll,ll>;

int main() {
    // keep track of secret sum
    ll secretsum = 0;

    ll MOD = 16777216; // mod for prune op

    // read in secret numbers
    string line;
    while (getline(cin, line)) {
        // read in secret
        ll secret = stoll(line);

        // run for 2000 iterations
        ll iter = 2000;
        while (iter--) {
            secret ^= (secret * 64);
            secret %= MOD;

            secret ^= (secret / 32);
            secret %= MOD;

            secret ^= (secret * 2048);
            secret %= MOD;
        }

        secretsum += secret; // add to secret sum total
    }

    cout << secretsum << endl;
}