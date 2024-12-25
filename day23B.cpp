#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
#define pb push_back

string maxclique = ""; // store max clique string representation
set<string> seen; // store seen cliques

void dfs(vector<string> clique, map<string, set<string>>& adj) {
    // compute string representation of clique
    sort(clique.begin(), clique.end());
    string rep = "";
    for (string c : clique) {
        rep += c + ",";
    }

    // if seen already, ignore this candidate
    // then insert it into set of seen candidates
    if (seen.count(rep)) return;
    seen.insert(rep);

    // replace max clique if current clique is bigger
    rep = rep.substr(0, rep.size()-1);
    if (rep.size() > maxclique.size()) maxclique = rep;

    // if clique is empty, check each individual computer
    if (clique.size() == 0) {
        for (auto [c, cons] : adj) {
            clique.pb(c);
            dfs(clique, adj);
            clique.pop_back();
        }
    } else {
        // go through all computers adjacent to first
        string c0 = clique[0];
        for (string c : adj[c0]) {
            bool isclique = true;
            for (string ci : clique) {
                if (!adj[c].count(ci)) {
                    isclique = false;
                    break;
                }
            }

            // add to clique if connected to all computers in clique
            if (isclique) {
                clique.pb(c);
                dfs(clique, adj);
                clique.pop_back();
            }
        }
    }
}

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

    // dfs through all possible cliques to best one
    // we add a computer to our candidate clique if it is connected to all in current clique
    // this runs in time since each computer has 13 adjacent computers and with pruning to remove seen cliques
    // this is only possible due to the above for this case, this is an NP-Hard problem
    dfs({}, adj);

    cout << maxclique << endl; // output maximal clique
}