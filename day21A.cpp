#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pllc = pair<pair<ll,ll>, char>;
using plpllc = pair<ll, pair<pair<ll,ll>, char>>;
#define pb push_back

// grid array
vector<string> grid;

// helper to check bounds
bool check_bounds(int x, int y) {
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
}

// helper to return optimal value between two chars
ll f(char x, char y, map<char, map<char, map<char,ll>>>& dist) {
    string dir = "^v><A";
    ll val = 1e17;
    for (char c : dir) {
        val = min(val, dist[x][y][c]);
    }
    return val;
}

int main() {
    // keypad grid
    grid.pb("#^A");
    grid.pb("<v>");

    // direction string
    string dir = "^v><A";

    // direction arrays
    ll dy [4] = {0, 0, 1, -1};
    ll dx [4] = {-1, 1, 0, 0};

    // two distance maps
    map<char, map<char, map<char,ll>>> dist;
    map<char, map<char, map<char,ll>>> dist0;

    // for our keypad, distance 1 to press each key
    for (char a : dir) for (char b : dir) for (char c : dir) dist0[a][b][c] = 1;

    // work out optimal pathing for intermediary keyboards
    for (int keys = 1; keys <= 2; keys++) {
        // initialize distance map
        for (char a : dir) for (char b : dir) for (char c : dir) dist[a][b][c] = 1e12;

        // find shortest paths between each character
        // can do in many ways, i used dijkstras (since its eventually weighted)
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == '#') continue;
                priority_queue<plpllc,
                    vector<plpllc>,
                    greater<plpllc>> pq;
                pq.push({0,{{i,j},'A'}});

                set<pllc> visited;
                dist[grid[i][j]][grid[i][j]]['A'] = 0;

                // dijkstras
                while (pq.size() > 0) {
                    plpllc top = pq.top(); pq.pop();

                    if (visited.count(top.second)) continue;
                    visited.insert(top.second);

                    ll dt = top.first; char dh = top.second.second;
                    ll x = top.second.first.first; ll y = top.second.first.second;

                    for (int k = 0; k < 4; k++) {
                        ll nx = x + dx[k]; ll ny = y + dy[k];
                        ll upd = dt + f(dh, dir[k], dist0);
                        if (check_bounds(nx,ny) && grid[nx][ny] != '#' && upd < dist[grid[i][j]][grid[nx][ny]][dir[k]]) {
                            dist[grid[i][j]][grid[nx][ny]][dir[k]] = upd;
                            pq.push({upd,{{nx, ny},dir[k]}});
                        }
                    }
                }

                // go to activate key
                for (int ii = 0; ii < 2; ii++) {
                    for (int jj = 0; jj < 3; jj++) {
                        if (grid[ii][jj] == '#')continue;
                        for (char c : dir) {
                            dist[grid[i][j]][grid[ii][jj]][c] += f(c,'A',dist0);
                        }
                    }
                }
            }
        }

        // swap distance maps for second iteration
        swap(dist, dist0);
    }

    // numbers
    string nums = "0123456789A";
    for (char a : nums) for (char b : nums) for (char c : dir) dist[a][b][c] = 1e12;

    // number keypad
    grid.clear();
    grid.pb("789");
    grid.pb("456");
    grid.pb("123");
    grid.pb("#0A");

    // work out optimal pathing for numpad
    // given final intermediary keyboard weights
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == '#') continue;
            priority_queue<plpllc,
                vector<plpllc>,
                greater<plpllc>> pq;
            pq.push({0,{{i,j},'A'}});

            set<pllc> visited;
            dist[grid[i][j]][grid[i][j]]['A'] = 0;

            // dijkstras
            while (pq.size() > 0) {
                plpllc top = pq.top(); pq.pop();

                if (visited.count(top.second)) continue;
                visited.insert(top.second);

                ll dt = top.first; char dh = top.second.second;
                ll x = top.second.first.first; ll y = top.second.first.second;

                for (int k = 0; k < 4; k++) {
                    ll nx = x + dx[k]; ll ny = y + dy[k];
                    ll upd = dt + f(dh, dir[k], dist0);
                    if (check_bounds(nx,ny) && grid[nx][ny] != '#' && upd < dist[grid[i][j]][grid[nx][ny]][dir[k]]) {
                        dist[grid[i][j]][grid[nx][ny]][dir[k]] = upd;
                        pq.push({upd,{{nx, ny},dir[k]}});
                    }
                }
            }

            // go to activate key
            for (int ii = 0; ii < 4; ii++) {
                for (int jj = 0; jj < 3; jj++) {
                    if (grid[ii][jj] == '#')continue;
                    for (char c : dir) {
                        dist[grid[i][j]][grid[ii][jj]][c] += f(c,'A',dist0);
                    }
                }
            }
        }
    }

    // obtain answers for input
    ll complex = 0;
    string line;
    while (getline(cin, line)) {
        ll minlen = 0;
        for (int i = 0; i < line.size(); i++) {
            if (i == 0) {
                minlen += f('A',line[0], dist);
            } else {
                minlen += f(line[i-1],line[i], dist);
            }
        }
        complex += stoll(line.substr(0, line.size()-1)) * minlen; // compute individual complexity
    }

    cout << complex << endl;
}