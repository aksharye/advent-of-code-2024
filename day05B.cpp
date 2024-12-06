#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

int main() {    
    // answer counter
    ll valid = 0;

    // read in graph and process updates
    map<ll,set<ll>> graph;
    string line;
    while (getline(cin, line)) {
        if (line.size() == 0) continue;
        if (line.size() == 5) {
            // edge
            string a = string() + line[0] + line[1];
            string b = string() + line[3] + line[4];
            graph[stoi(a)].insert(stoi(b));
        } else {
            // update
            vector<ll> v;
            for (int i = 0; i < line.size(); i += 3) {
                string s = string() + line[i] + line[i+1];
                v.pb(stoi(s));
            }

            bool works = true;
            // find violations
            for (int i = 0; i < v.size(); i++) {
                for (int j = 0; j < i; j++) {
                    // no cycles, so perform swap to fix
                    if (graph[v[i]].count(v[j]) > 0) {
                        works = false;
                        swap(v[i], v[j]);
                    }
                }
            }
            
            if (!works) valid += v[v.size() / 2];
        }
    }

    cout << valid << endl;
}