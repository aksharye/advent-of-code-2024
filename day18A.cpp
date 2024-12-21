#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

// grid array
vector<string> grid;

// helper to check bounds
bool check_bounds(int x, int y) {
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
}

int main() {
    // initialize empty grid
    ll n = 71; ll m = 71;
    for (int i = 0; i < n; i++) {
        string line;
        for (int j = 0; j < m; j++) line.pb('.');
        grid.pb(line);
    }
    
    // read in and parse byte coordinates
    string line;
    vector<pair<ll,ll>> bytes;
    while (getline(cin, line)) {
        cin >> line;
        
        string xx, yy;
        ll k = 0;
        while (line[k] != ',') {
            xx.pb(line[k]); 
            k++;
        }
        k++;
        while (k < line.size()) {
            yy.pb(line[k]); 
            k++;
        }
        
        ll x = stoll(xx); ll y = stoll(yy);
        bytes.pb({x,y});
    }

    // place first 1024 bytes
    for (int i = 0; i < 1024; i++) grid[bytes[i].first][bytes[i].second] = '#';

    // bfs to find minimum steps
    queue<pair<ll,ll>> q;
    q.push({0,0});

    ll steps = -1;
    ll dist = 0;

    ll dx [4] = {-1, 0, 1, 0};
    ll dy [4] = {0, 1, 0, -1};

    set<pair<ll,ll>> visited;
    while (q.size() > 0) {
        ll d = q.size();
        while (d--) {
            pair<ll,ll> top = q.front(); q.pop();

            if (visited.count(top)) continue;
            visited.insert(top);

            ll x = top.first; ll y = top.second;

            // obtain minimum once we hit ending coordinate
            if (x == n-1 && y == m-1) {
                steps = dist;
                break;
            }

            // bfs to neighbors
            for (int k = 0; k < 4; k++) {
                ll nx = x + dx[k]; ll ny = y + dy[k];
                if (check_bounds(nx,ny) && grid[nx][ny] != '#') q.push({nx, ny});
            }
        }
        dist++;
    }

    cout << steps << endl;
}