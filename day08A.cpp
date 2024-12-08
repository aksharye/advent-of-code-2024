#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

// grid
vector<string> grid;

// helper to check bounds
bool check_bounds(int x, int y) {
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
}

int main() {    
    // read in grid
    string line;
    while (getline(cin, line)) grid.pb(line);

    // keep track of antennas
    map<char, vector<pair<ll,ll>>> freq;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] != '.') freq[grid[i][j]].pb({i,j});
        }
    }

    // keep track of antinodes
    set<pair<ll,ll>> antinodes;
    for (auto [k, v] : freq) {
        ll n = v.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                // add inline antenna
                ll dx = v[i].first - v[j].first;
                ll dy = v[i].second - v[j].second;
                ll x = v[i].first + dx;
                ll y = v[i].second + dy;
                if (check_bounds(x,y)) antinodes.insert({x,y});
            }
        }
    }

    cout << antinodes.size() << endl;
}