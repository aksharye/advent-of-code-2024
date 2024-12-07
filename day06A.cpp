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

// traverse grid
void dfs (int x, int y) {
    if (!check_bounds(x,y)) return;

    ll nx = x;
    ll ny = y;

    // where is guard facing
    if (grid[x][y] == '^') nx--;
    if (grid[x][y] == '>') ny++;
    if (grid[x][y] == 'V') nx++;
    if (grid[x][y] == '<') ny--;

    if (!check_bounds(nx,ny)) {
        grid[x][y] = 'X';
        return;
    }

    // running into obstacle?
    while (grid[nx][ny] == '#') {
        if (grid[x][y] == '^') {
            grid[x][y] = '>';
        } else if (grid[x][y] == '>') {
            grid[x][y] = 'V';
        } else if (grid[x][y] == 'V') {
            grid[x][y] = '<';
        } else {
            grid[x][y] = '^';
        }

        nx = x; ny = y;

        // where is guard facing now?
        if (grid[x][y] == '^') nx--;
        if (grid[x][y] == '>') ny++;
        if (grid[x][y] == 'V') nx++;
        if (grid[x][y] == '<') ny--;
    }

    if (!check_bounds(nx,ny)) {
        grid[x][y] = 'X';
        return;
    }

    grid[nx][ny] = grid[x][y];

    // cover tracks with X
    grid[x][y] = 'X';

    dfs(nx, ny);
    return;
}

int main() {    
    // answer counter
    ll vis = 0;

    string line;
    while (getline(cin, line)) grid.pb(line);

    for (int i = 0; i < grid.size(); i++) {
        bool found = false;
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] != '.' && grid[i][j] != '#') {
                dfs(i, j);
                found = true;
                break;
            }
        }
        if (found) break;
    }
    
    // count Xs
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'X') vis++;
        }
    }

    cout << vis << endl;
}