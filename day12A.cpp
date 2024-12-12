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

// track area and perimeter of current region
ll A = 0;
ll P = 0;

// dfs a region and compute A and P
void dfs(ll x, ll y) {
    if (visited[x][y]) return;

    visited[x][y] = true;

    // area and perimeter contrib is initially 1 anad 4
    A++;
    P += 4;

    // direction arrays
    ll dx [] = {0, 1, 0, -1};
    ll dy [] = {-1, 0, 1, 0};

    // loop through directions and dfs through region
    for (int k = 0; k < 4; k++) {
        ll nx = x + dx[k];
        ll ny = y + dy[k];
        if (check_bounds(nx,ny)) {
            if (grid[nx][ny] == grid[x][y]) {
                P--; // if we share a side with another char in the same region, we remove it
                dfs(nx,ny);
            } 

        }
    }
}

int main() {
    // keep track of price
    ll price = 0;

    // read in grid
    string line;
    while (getline(cin, line)) {
        grid.pb(line);
        vector<bool> v (line.size(), false); visited.pb(v);
    }

    // dfs through regions, track A and P, and reset
    ll n = grid.size();
    ll m = grid[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j]) {
                dfs(i,j);
                price += A * P;
                A = 0; P = 0;
            }
        }
    }

    cout << price << endl;
}