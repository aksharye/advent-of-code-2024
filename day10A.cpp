#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

// grid
vector<string> grid;

// set to track distinct nine positions
set<pair<ll,ll>> nines;

// helper to check bounds
bool check_bounds(int x, int y) {
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
}

// dfs through grid to find distinct nine positions
void dfs(ll x, ll y) {
    ll dx [] = {-1, 0, 1, 0};
    ll dy [] = {0, -1, 0, 1};

    if (grid[x][y] == '9') nines.insert({x,y});

    ll v = grid[x][y] - '0';
    for (int k = 0; k < 4; k++) {
        ll nx = x + dx[k]; ll ny = y + dy[k];
        if (check_bounds(nx,ny)) {
            ll nv = grid[nx][ny] - '0';
            if (nv == v+1) dfs(nx,ny);
        }
    }
}

int main() {    
    // read in grid
    string line;
    while (getline(cin, line)) grid.pb(line);

    // check all 0 positions and add number of distinct nine positions
    ll ans = 0;
    for (int i = 0;i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '0') dfs(i,j);
            ans += nines.size();
            nines.clear();
        }
    }
    
    cout << ans << endl;
}