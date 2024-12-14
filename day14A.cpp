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

// dfs through grid to nine positions
ll dfs(ll x, ll y) {
    ll dx [] = {-1, 0, 1, 0};
    ll dy [] = {0, -1, 0, 1};

    if (grid[x][y] == '9') return 1;

    ll ret = 0;

    ll v = grid[x][y] - '0';
    for (int k = 0; k < 4; k++) {
        ll nx = x + dx[k]; ll ny = y + dy[k];
        if (check_bounds(nx,ny)) {
            ll nv = grid[nx][ny] - '0';
            if (nv == v+1) ret += dfs(nx,ny);
        }
    }
    
    return ret;
}

int main() {    
    // read in grid
    ll q [] = {0, 0, 0, 0};
    
    ll m, n; m = 101; n = 103;
    string line;
    while (getline(cin, line)) {
        istringstream iss (line);
        string p, v; iss >> p >> v;

        string spx, spy, svx, svy;

        ll k = 2;
        while (p[k] != ',') {
            spx.pb(p[k]); k++;
        }
        k++;
        while (k < p.size()) {
            spy.pb(p[k]); k++;
        }

        k = 2;
        while (v[k] != ',') {
            svx.pb(v[k]); k++;
        }
        k++;
        while (k < v.size()) {
            svy.pb(v[k]); k++;
        }

        ll px, py, vx, vy;
        px = stoll(spx); py = stoll(spy); vx = stoll(svx); vy = stoll(svy);

        px += 100 * vx; px %= m; px += m; px %= m;
        py += 100 * vy; py %= n; py += n; py %= n;

        ll g = 0;
        if (px == m / 2 || py == n / 2) continue;
        if (px > m / 2) g += 2;
        if (py > n / 2) g += 1;
        q[g]++;
    }

    cout << q[0] * q[1] * q[2] * q[3] << endl;

}