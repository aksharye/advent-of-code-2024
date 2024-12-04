#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

// validate if a string is a valid mul call
// returns -1 if invalid, the mul value otherwise
ll check_string(string s) {
    if (s.size() < 8) return -1;
    if (s.substr(0,4) != "mul(") return -1;
    if (s[s.size()-1] != ')') return -1;

    ll n = s.size();
    bool comma = false;
    string a = "";
    string b = "";
    for (int i = 4; i < n-1; i++) {
        if (s[i] - '0' < 0 || s[i] - '0' > 9) {
            if (s[i] != ',') return -1;
            if (comma) return -1;
            comma = true;
        } else {
            if (comma) {
                b.pb(s[i]);
            } else {
                a.pb(s[i]);
            }
        }
    }

    if (a.size() == 0 || b.size() == 0) return -1;

    return stoi(a) * stoi(b);
}

int main() {    
    // answer counter
    ll ans = 0;

    // read in reports
    string line;
    while (getline(cin, line)) {
        ll n = line.size();

        // string candidate has size at least 8 and at most 12
        for (int i = 0; i <= n-8; i++) {
            for (int j = 8; j <= 12; j++) {
                if (i + j <= n) {
                    ll v = check_string(line.substr(i,j));
                    if (v > -1) ans += v;
                }
            }
        }
    }

    cout << ans << endl;
}