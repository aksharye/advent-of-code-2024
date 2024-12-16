#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

// grid
vector<string> grid;

// direction arrays
// indices correspond to below
// ^>v<
ll dx [4] = {-1, 0, 1, 0};
ll dy [4] = {0, 1, 0, -1};

// helper to check bounds
bool check_bounds(int x, int y) {
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
}

// store robot positions globally
ll rx = 0;
ll ry = 0;

// check if a move is possible
// for vertical moves, if we encounter a box
// we also check if its other half can be moved recursively
bool check_empty(ll x, ll y, int dir) {
    // loop until empty
    while (check_bounds(x,y) && (grid[x][y] != '.' && grid[x][y] != '#')) { 
        x += dx[dir]; y += dy[dir];

        // if at box, check other half (only for vertical)
        if (dy[dir] == 0 && grid[x][y] == '[') {
            if (!check_empty(x,y+1,dir)) return false;
        }

        if (dy[dir] == 0 && grid[x][y] == ']') {
            if (!check_empty(x,y-1,dir)) return false;
        }
    };

    // if first non-box is out of grid or a wall, can't move
    if (!check_bounds(x,y) || grid[x][y] == '#') {
        return false;
    }

    return true;
}

// make move
// we make vertical moves recursively, similar to checking for a move
void move_empty(ll x, ll y, int dir) {
    // store prev char
    char temp = '.';

    while (check_bounds(x,y) && (grid[x][y] != '.' && grid[x][y] != '#')) {
        // update grid
        swap(grid[x][y], temp);

        x += dx[dir]; y += dy[dir];

        // if at box, move other half (only for vertical)
        if (dy[dir] == 0 && grid[x][y] == '[') move_empty(x,y+1,dir);
        if (dy[dir] == 0 && grid[x][y] == ']') move_empty(x,y-1,dir);
    };

    // final update
    swap(grid[x][y], temp);
}

// simulate move (if possible)
void move(int dir) {
    if (check_empty(rx, ry, dir)) {
        move_empty(rx, ry, dir);
        rx += dx[dir]; ry += dy[dir];
    }
}

int main() {    
    // keep track of gps sum
    ll gps = 0;
    
    // read in grid, check end by seeing if a row has all walls
    string line;
    ll ct = 0;
    while (getline(cin, line)) {
        string newline = "";
        bool allwall = true;

        // expand grid according to rules
        for (char c : line) {
            if (c != '#') allwall = false;
            if (c == '#') {
                newline += "##";
            } else if (c == 'O') {
                newline += "[]";
            } else if (c == '@') {
                newline += "@.";
            } else {
                newline += "..";
            }
        }

        grid.pb(newline);
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
            if (grid[i][j] == '[') gps += 100 * i + j;
        }
    }

    cout << gps << endl;
}