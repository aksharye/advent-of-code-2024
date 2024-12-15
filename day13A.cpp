#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
#define pb push_back

// grid and visited tracker
vector<string> grid;
vector<vector<bool>> visited;

// helper to check bounds
bool check_bounds(int x, int y) {
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
}

// dfs a region and compute A and P
void dfs(ll x, ll y) {
    if (visited[x][y]) return;

    visited[x][y] = true;

    // direction arrays
    ll dx [] = {0, 1, 0, -1};
    ll dy [] = {-1, 0, 1, 0};

    // loop through directions and dfs through region
    for (int k = 0; k < 4; k++) {
        ll nx = x + dx[k];
        ll ny = y + dy[k];
        if (check_bounds(nx,ny)) {
            if (grid[nx][ny] == grid[x][y]) {
                dfs(nx,ny);
            } 

        }
    }
}

ll read_x (string s) {
    ll n = s.size();
    n -= 3;
    return stoll(s.substr(2,n));
}

ll read_y (string s) {
    ll n = s.size();
    n -= 2;
    return stoll(s.substr(2,n));
}

int main() {
    // keep track of price
    ll ans = 0;

    // read in grid
    string line;
    ll ct = 0;
    ll XA, XB, YA, YB;
    while (getline(cin, line)) {
        if (line.size() == 0) continue;
        ct++;

        if (ct % 3 == 0) {
            istringstream iss (line);
            string a, x, y; iss >> a >> x >> y;
            ll O = 1; ll oz = 13; while (oz--) O *= 10;
            ll X = read_x(x);
            ll Y = read_y(y);
            X += O;
            Y += O;
   
            ll XXB = XB;
            ll YYB = YB;
            XXB *= YA;
            YYB *= XA;
            ll XX = X;
            ll YY = Y;
            XX *= YA;
            YY *= XA;

            ll ZA = max(XA,YA);
            ll ZZA = min(XA, YA);
            ll ZB = max(XB,YB);
            ll ZZB = min(XB,YB);

            if ((XXB-YYB) != 0 && abs(XX - YY) % abs(XXB - YYB) == 0) {
 
                
                ll z = (XX - YY)/(XXB - YYB);

                if ((X - z * XB) % XA == 0) {
                    ll g = (X - z * XB)/XA;
                    ans += z + 3 * g;
                }

            }

        } else if (ct % 3 == 1) {
            istringstream iss (line);
            string a, a2, x, y; iss >> a >> a2 >> x >> y;

            XA = read_x(x);
            YA = read_y(y);
        } else {
            istringstream iss (line);
            string a, a2, x, y; iss >> a >> a2 >> x >> y;

            XB = read_x(x);
            YB = read_y(y);
        }


        
    }

    cout << ans << endl;
}