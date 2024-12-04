#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

int main() {    
    // answer counter
    ll xmas = 0;

    // read in grid;
    vector<string> grid;
    string line;
    while (getline(cin, line)) grid.pb(line);

    ll n = grid.size(); ll m = grid[0].size();
    
    // search all 3x3 regions
    for (int i = 0; i < n-2; i++) {
        for (int j = 0; j < m-2; j++) {
            // check diagonals
            string d1 = string() + grid[i][j] + grid[i+1][j+1] + grid[i+2][j+2];
            string d2 = string() + grid[i][j+2] + grid[i+1][j+1] + grid[i+2][j];
            if ((d1 == "MAS" || d1 == "SAM") && (d2 == "MAS" || d2 == "SAM")) xmas++;
        }
    }

    cout << xmas << endl;
}