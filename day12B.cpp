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

// track area and corners of current region
// we track corners because # of corners = # of sides
ll A = 0;
ll C = 0;

// dfs a region and compute A and C
void dfs(ll x, ll y) {
    if (visited[x][y]) return;

    visited[x][y] = true;
    
    // area contrib is 1
    A++;

    // direction arrays
    ll dx [] = {0, 1, 0, -1};
    ll dy [] = {-1, 0, 1, 0};

    // loop through directions and dfs through region
    // we check adjacent directions and diagonal elements to compute corners
    /*
        The center point is a corner for region A:
        
        XX
        XA

        The center point is also a corner for region A:

        XA
        AA
    */
    for (int k = 0; k < 4; k++) {
        
        // booleans to check if the two adjacent and the diagonal elements are equal to the current
        bool A1 = false;
        bool A2 = false;
        bool D = false;

        // A1
        ll nx = x + dx[k];
        ll ny = y + dy[k];
        if (check_bounds(nx,ny)) {
            if (grid[nx][ny] == grid[x][y]) {
                dfs(nx,ny);
                A1 = true;
            }
        }

        // A2
        nx = x + dx[(k+1) % 4];
        ny = y + dy[(k+1) % 4];
        if (check_bounds(nx,ny)) {
            if (grid[nx][ny] == grid[x][y]) {
                dfs(nx,ny);
                A2 = true;
            }
        }

        // D
        nx = x + dx[k] + dx[(k+1) % 4];
        ny = y + dy[k] + dy[(k+1) % 4];
        if (check_bounds(nx,ny)) {
            if (grid[nx][ny] == grid[x][y]) {
                D = true;
            }
        }

        // if either case holds increment the # of corners
        if ((!A1 && !A2) || (A1 && A2 && !D)) C++;
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

    // dfs through regions, track A and C, and reset
    ll n = grid.size();
    ll m = grid[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j]) {
                dfs(i,j);
                price += A * C;
                A = 0; C = 0;
            }
        }
    }

    cout << price << endl;
}