#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

// grid, dp, and visited arrays
vector<string> grid;
vector<vector<vector<ll>>> dp; // x, y, dir
vector<vector<vector<bool>>> visited;

// helper to check bounds
bool check_bounds(int x, int y) {
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
}

// helper to get min value with associated grid tile
ll min_val(ll x, ll y) {
    return min(min(dp[x][y][0], dp[x][y][1]), min(dp[x][y][2], dp[x][y][3]));
}

int main() {
    // read in grid, initialize dp and visited
    string line;
    while (getline(cin, line)) {
        grid.pb(line);
        vector<vector<ll>> v (line.size(), vector<ll> (4, 1e16)); dp.pb(v);
        vector<vector<bool>> w (line.size(), vector<bool> (4, false)); visited.pb(w);
    }

    // bounds
    ll n = grid.size(); ll m = grid[0].size();

    // find start and end positions
    ll sx, sy, ex, ey;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'S') {
                sx = i; sy = j;
                dp[i][j][0] = 0;
            }
            if (grid[i][j] == 'E') {
                ex = i; ey = j;
            }
        }
    }

    // direction arrays
    ll dx [] = {0, 1, 0, -1};
    ll dy [] = {-1, 0, 1, 0};

    // dijkstras
    priority_queue<pair<ll,pair<pair<ll,ll>, ll>>,
        vector<pair<ll,pair<pair<ll,ll>, ll>>>,
        greater<pair<ll,pair<pair<ll,ll>, ll>>>> pq; // dist, state
    pq.push({0,{{sx,sy},0}});
    while (pq.size() > 0) {
        pair<ll,pair<pair<ll,ll>,ll>> top = pq.top(); pq.pop();

        ll x = top.second.first.first;
        ll y = top.second.first.second;
        ll dir = top.second.second;

        if (visited[x][y][dir]) continue; // if visited, continue;
        if (x == ex && y == ey) continue; // ignore last tile

        visited[x][y][dir] = true; // mark visited

        // check each direction
        for (int i = 0; i < 4; i++) {
            ll nx = x + dx[i]; ll ny = y + dy[i];
            ll upd = dp[x][y][dir] + 1 + 1000 * (i != dir) + 1000 * (((i - dir + 4) % 4) == 2);

            if (check_bounds(nx,ny) && grid[nx][ny] != '#' && upd < dp[nx][ny][i]) {
                // add to pq
                dp[nx][ny][i] = upd;
                pq.push({dp[nx][ny][i],{{nx,ny},i}});
            }
        }
    }

    cout << min_val(ex,ey) << endl;
}