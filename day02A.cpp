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

        // exercise to reader: why are the below checks sufficient?
        // increasing check
        bool works = true;
        for (int i = 1; i < v.size(); i++) if (v[i]-v[i-1] < 1 || v[i]-v[i-1] > 3) works = false;
        if (works) safe++;

        // decreasing check
        works = true;
        for (int i = 1; i < v.size(); i++) if (v[i]-v[i-1] >= 0 || v[i]-v[i-1] < -3) works = false;
        if (works) safe++;
    }

    cout << safe << endl;
}