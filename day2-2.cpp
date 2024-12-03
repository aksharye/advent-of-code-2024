#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

int main() {    
    // safe reports counter
    ll safe = 0;

    // read in reports
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<ll> v;
        ll x;
        while (iss >> x) v.pb(x);

        // exercise to reader: why the conditionals?

        // iterate over removals
        for (int j = 0; j < v.size(); j++) {
            // increasing check
            bool works = true;
            for (int i = 1+(j == 0); i < v.size(); i++) {
                if (i == j) continue;
                if (v[i]-v[i-1-(j == i-1)] < 1 || v[i]-v[i-1-(j == i-1)] > 3) works = false;
            }

            if (works) {
                safe++;
                break;
            }

            // decreasing check
            works = true;
            for (int i = 1+(j == 0); i < v.size(); i++) {
                if (i == j) continue;
                if (v[i]-v[i-1-(j == i-1)] >= 0 || v[i]-v[i-1-(j == i-1)] < -3) works = false;
            }

            if (works) {
                safe++;
                break;
            }
        }
    }

    cout << safe << endl;
}