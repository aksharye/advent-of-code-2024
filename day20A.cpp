#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
#define pb push_back

// grid array
vector<string> grid;

// helper to check bounds
bool check_bounds(int x, int y) {
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
}

int main() {
    // read in grid
    string line;
    while (getline(cin, line)) {
        grid.pb(line);
    }

    // bounds
    ll n = grid.size(); ll m = grid[0].size();

    // find start and end positions
    ll sx, sy, ex, ey;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'S') {
                sx = i; sy = j;
            }
            if (grid[i][j] == 'E') {
                ex = i; ey = j;
            }
        }
    }

    // dirrection arrays
    ll dx [4] = {0, 1, 0, -1};
    ll dy [4] = {1, 0, -1, 0};

    // find distance of each tile from start via bfs
    vector<vector<ll>> distS (n, vector<ll> (m, 0));
    vector<vector<ll>> visited (n, vector<ll> (m, false));

    queue<pll> q;
    q.push({sx, sy});
    ll dist = 0;

    while (q.size() > 0) {
        ll d = q.size();
        while (d--) {
            pll top = q.front(); q.pop();
            ll x = top.first; ll y = top.second;

            if (visited[x][y]) continue;
            visited[x][y] = true;

            distS[x][y] = dist;

            for (int k = 0; k < 4; k++) {
                ll nx = x + dx[k]; ll ny = y + dy[k];
                if (check_bounds(nx,ny) && grid[nx][ny] != '#') {
                    q.push({nx, ny});
                }
            }
        }
        dist++;
    }

    // find distance of each tile from end via bfs
    vector<vector<ll>> distE (n, vector<ll> (m, 0));
    visited = vector<vector<ll>> (n, vector<ll> (m, false));

    q.push({ex, ey});
    dist = 0;

    while (q.size() > 0) {
        ll d = q.size();
        while (d--) {
            pll top = q.front(); q.pop();
            ll x = top.first; ll y = top.second;

            if (visited[x][y]) continue;
            visited[x][y] = true;

            distE[x][y] = dist;

            for (int k = 0; k < 4; k++) {
                ll nx = x + dx[k]; ll ny = y + dy[k];
                if (check_bounds(nx,ny) && grid[nx][ny] != '#') {
                    q.push({nx, ny});
                }
            }
        }
        dist++;
    }

    ll currTime = distS[ex][ey]; // time with no cheats

    // iterate through tiles
    ll cheats = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '#') {
                // check all tiles two away
                for (int k = 0; k < 4; k++) {
                    ll nx = i + 2*dx[k]; ll ny = j + 2*dy[k];
                    if (check_bounds(nx,ny) && grid[nx][ny] != '#') {
                        // compute new time using start and end distances along with cheat distance
                        ll newTime = distS[i][j] + 2 + distE[nx][ny];
                        if (currTime - newTime >= 100) cheats++; // increment if it saves at least 100 picoseconds
                    }
                }
            }
        }
    }

    cout << cheats << endl;
}