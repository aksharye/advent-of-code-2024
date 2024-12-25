#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
#define pb push_back

int main() {
    map<string, set<string>> adj; // adjacency list

    // read in connections
    string line;
    while (getline(cin, line)) {
        string c1 = string() + line[0] + line[1];
        string c2 = string() + line[3] + line[4];

        // connect edges in adj list
        adj[c1].insert(c2);
        adj[c2].insert(c1);
    }

    set<string> triangles; // store set of triangles

    // key observation is that each computer has 13 adjacent ones
    for (auto [c1, cons] : adj) { // iterate over computers and their adj lists
        for (string c2 : cons) { // iterate over computers in adj list
            for (string c3 : cons) { // iterate over second computer in adj list
                if (c2 == c3) continue;
                vector<string> tri; // store tri
                if (adj[c2].count(c3)) { // if last edge is present, we have a triangle
                    tri.pb(c1); tri.pb(c2); tri.pb(c3);
                    sort(tri.begin(), tri.end());
                    string trirep = tri[0] + tri[1] + tri[2];

                    // insert triangle into set if it contains a computer that starts with t
                    if (tri[0][0] == 't' || tri[1][0] == 't' || tri[2][0] == 't') triangles.insert(trirep);
                }
            }
        }
    }

    // return number of triangles
    cout << triangles.size() << endl;
}