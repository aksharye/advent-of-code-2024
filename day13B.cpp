#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

// grid and visited tracker
vector<string> grid;
vector<vector<bool>> visited;

// helper to check bounds
bool check_bounds(int x, int y) {
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
}

// dfs a region and compute A and P
void dfs(ll x, ll y) {
    if (visited[x][y]) return;

    visited[x][y] = true;

    // direction arrays
    ll dx [] = {0, 1, 0, -1};
    ll dy [] = {-1, 0, 1, 0};

    // loop through directions and dfs through region
    for (int k = 0; k < 4; k++) {
        ll nx = x + dx[k];
        ll ny = y + dy[k];
        if (check_bounds(nx,ny)) {
            if (grid[nx][ny] == grid[x][y]) {
                dfs(nx,ny);
            } 

        }
    }
}

int main() {
    // keep track of price
    ll ans = 0;

    // read in grid
    string line;
    while (getline(cin, line)) {
        grid.pb(line);
        vector<bool> v (line.size(), false); visited.pb(v);
    }

    // dfs through regions, track A and P, and reset
    ll n = grid.size();
    ll m = grid[0].size();

    cout << ans << endl;
}