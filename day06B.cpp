#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

// grid
vector<string> grid;
vector<string> grid2;

// history
map<pair<ll,ll>,char> hist;

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

// traverse grid, 1 if inf loop, 0 otherwise
int dfs2 (int x, int y) {
    if (!check_bounds(x,y)) return 0;

    // check and update hist
    if (hist[{x,y}] == grid2[x][y]) {
        grid2[x][y] = '.';
        return 1;
    }

    hist[{x,y}] = grid2[x][y];

    ll nx = x;
    ll ny = y;

    // where is guard facing
    if (grid2[x][y] == '^') nx--;
    if (grid2[x][y] == '>') ny++;
    if (grid2[x][y] == 'V') nx++;
    if (grid2[x][y] == '<') ny--;

    if (!check_bounds(nx,ny)) {
        grid2[x][y] = '.';
        return 0;
    }

    // running into obstacle?
    while (grid2[nx][ny] == '#') {
        if (grid2[x][y] == '^') {
            grid2[x][y] = '>';
        } else if (grid2[x][y] == '>') {
            grid2[x][y] = 'V';
        } else if (grid2[x][y] == 'V') {
            grid2[x][y] = '<';
        } else {
            grid2[x][y] = '^';
        }

        nx = x; ny = y;

        // where is guard facing now?
        if (grid2[x][y] == '^') nx--;
        if (grid2[x][y] == '>') ny++;
        if (grid2[x][y] == 'V') nx++;
        if (grid2[x][y] == '<') ny--;
    }

    if (!check_bounds(nx,ny)) {
        grid2[x][y] = '.';
        return 0;
    }

    grid2[nx][ny] = grid2[x][y];

    // cover tracks with .
    grid2[x][y] = '.';

    return dfs2(nx, ny);
}

int main() {    
    // answer counter
    ll loop = 0;

    string line;
    while (getline(cin, line)) {
        grid.pb(line);
        grid2.pb(line);
    }

    pair<ll,ll> startpos;
    for (int i = 0; i < grid.size(); i++) {
        bool found = false;
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] != '.' && grid[i][j] != '#') {
                dfs(i, j);
                startpos = {i,j};
                found = true;
                break;
            }
        }
        if (found) break;
    }
    
    // check all obstacle candidate positions (which are X)
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'X') {
                grid2[i][j] = '#';
                loop += dfs2(startpos.first, startpos.second);
                grid2[i][j] = '.';
                grid2[startpos.first][startpos.second] = '^';
                hist.clear();
            }
        }
    }

    cout << loop << endl;
}