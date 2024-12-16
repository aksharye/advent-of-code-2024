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

// store robot positions globally
ll rx = 0;
ll ry = 0;

// simulate move (if possible)
void move(int dir) {
    // direction arrays
    // indices correspond to below
    // ^>v<
    ll dx [4] = {-1, 0, 1, 0};
    ll dy [4] = {0, 1, 0, -1};

    // store empty spot location
    ll ex = -1;
    ll ey = -1;

    // find first non box space
    ll x = rx; ll y = ry;
    while (check_bounds(x,y) && (grid[x][y] != '.' && grid[x][y] != '#')) {
        x += dx[dir]; y += dy[dir];
    };

    // if out of grid or a wall, can't move
    if (!check_bounds(x,y) || grid[x][y] == '#') {
        return;
    }

    // otherwise, is empty space, and can
    // update grid accordingly
    ex = x; ey = y;
    if (grid[x][y] == '.') {
        x = rx; y = ry;
        grid[x][y] = '.';
        x += dx[dir]; y += dy[dir];
        grid[x][y] = '@';
        rx+=dx[dir]; ry += dy[dir];
        while (!(x == ex && y == ey)) {
            x += dx[dir]; y += dy[dir];
            grid[x][y] = 'O';
        };
    }
}

int main() {    
    // keep track of gps sum
    ll gps = 0;
    
    // read in grid, check end by seeing if a row has all walls
    string line;
    ll ct = 0;
    while (getline(cin, line)) {
        grid.pb(line);
        bool allwall = true;
        for (char c : line) if (c != '#') allwall = false;
        if (allwall) ct++;
        if (ct == 2) break;
    }

    // read in moves
    string moves;
    while (getline(cin, line)) moves += line;

    // bounds
    ll n = grid.size(); ll m = grid[0].size();

    // find robot
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '@') {
                rx = i;
                ry = j;
                break;
            }
        }
    }

    // simulate moves
    for (char c : moves) {
        // indices correspond to below
        // ^>v<
        if (c == '^') {
            move(0);
        } else if (c == '>') {
            move(1);
        } else if (c == 'v') {
            move(2);
        } else {
            move(3);
        }
    }

    // add up gps coords of boxes
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'O') gps += 100 * i + j;
        }
    }

    cout << gps << endl;
}