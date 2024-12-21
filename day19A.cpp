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
    ll designs = 0;
    string line;
    while (getline(cin, line)) {
        if (line.size() == 0) continue;

        // use dp to find if a design is possible
        int n = line.size();
        bool dp [n+1] = {0}; // dp[i] = design 1...i is possible
        dp[0] = true; // empty design is possible

        // fill out dp table
        for (int i = 1; i <= n; i++) {
            string cand = "";
            ll j = i;
            
            // build a candidate string and check if its in patterns
            // if 1...i is possible and i+1...j is in patterns
            // then 1...j is possible
            while (j--) {
                cand = line[j] + cand;

                if (dp[j] && patterns.count(cand)) {
                    dp[i] = true;
                }
            }
        }

        // if true, 1...n is possible, increment number of possible designs
        designs += dp[n];
    }

    cout << designs << endl;
}