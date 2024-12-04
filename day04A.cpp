#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

// helper to check bounds
bool check_bounds(int x, int y, int mx, int my) {
    return x >= 0 && x < mx && y >= 0 && y < my;
}

int main() {    
    // answer counter
    ll xmas = 0;

    // read in grid;
    vector<string> grid;
    string line;
    while (getline(cin, line)) grid.pb(line);

    ll n = grid.size(); ll m = grid[0].size();

    int dx [] = {1, 0, -1, 0, 1, 1, -1, -1};
    int dy [] = {0, 1, 0, -1, 1, -1, 1, -1};
    
    // search all 8 directions in grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 8; k++) {
                string s = "";
                int x = i; int y = j;

                while (s.size() < 4 && check_bounds(x,y,n,m)) {
                    s += grid[x][y];
                    x += dx[k];
                    y += dy[k];
                }

                if (s == "XMAS") xmas++;
            }
        }
    }

    cout << xmas << endl;
}