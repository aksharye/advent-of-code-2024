#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

int main() {    
    // read in patterns
    set<string> patterns;
    string pattern = ",";
    while (pattern[pattern.size()-1] == ',') {
        cin >> pattern;
        if (pattern[pattern.size()-1] == ',') {
            patterns.insert(pattern.substr(0,pattern.size()-1));
        } else {
            patterns.insert(pattern);
        }
    }

    // iterate through designs and check which ones are possible
    ll ways = 0;
    string line;
    while (getline(cin, line)) {
        if (line.size() == 0) continue;

        // use dp to find number of ways to make design
        int n = line.size();
        ll dp [n+1] = {0}; // dp[i] = number of ways to make design 1...i
        dp[0] = 1; // one way to make empty design

        // fill out dp table
        for (int i = 1; i <= n; i++) {
            string cand = "";
            ll j = i;
            
            // build a candidate string and check if its in patterns
            // if i+1...j is in patterns
            // then can make 1...j with design 1...i and pattern i+1...j
            // thus, increment dp[j] by dp[i]
            while (j--) {
                cand = line[j] + cand;

                if (patterns.count(cand)) {
                    dp[i] += dp[j];
                }
            }
        }

        // increment number of total ways by ways to make 1...n
        ways += dp[n];
    }

    cout << ways << endl;
}