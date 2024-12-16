#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

int main() {

    // keep track of # of robots in each quadrant
    ll q [] = {0, 0, 0, 0};
    
    // bounds
    ll m, n; m = 101; n = 103;

    // read in robot info
    string line;
    vector<vector<ll>> robos;
    while (getline(cin, line)) {
        istringstream iss (line);

        // parse input to get p and v values
        string p, v; iss >> p >> v;
        string spx, spy, svx, svy;

        ll k = 2;
        while (p[k] != ',') {
            spx.pb(p[k]); 
            k++;
        }
        k++;
        while (k < p.size()) {
            spy.pb(p[k]); 
            k++;
        }

        k = 2;
        while (v[k] != ',') {
            svx.pb(v[k]); 
            k++;
        }
        k++;
        while (k < v.size()) {
            svy.pb(v[k]); 
            k++;
        }

        ll px, py, vx, vy;
        px = stoll(spx); py = stoll(spy); vx = stoll(svx); vy = stoll(svy);

        // store robot info in vector
        vector<ll> rvals = {px, py, vx, vy};
        robos.pb(rvals);
    }

    // define base grid
    char grid [n][m]; 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) grid[i][j] = '.';
    }

    // simulate many timesteps
    for (int t = 1; t <= 100000; t++) {

        // update each robot after timestep and mark occupied spots in grid
        for (int i = 0; i < robos.size(); i++) {
            robos[i][0] += robos[i][2]; robos[i][0] %= m; robos[i][0] += m; robos[i][0] %= m;
            robos[i][1] += robos[i][3]; robos[i][1] %= n; robos[i][1] += n; robos[i][1] %= n;

            grid[robos[i][1]][robos[i][0]] = 'X';
        }

        // check for five consecutive Xs on diagonal
        // i thought this would be a good indicator cuz the leaves on a xmas tree are diagonal
        bool flag = false;
        for (int i = 1; i < n-2; i++) {
            for (int j = 1; j < m-2; j++) {
                bool holds = true;
                for (int k = -2; k <= 2; k++) {
                    if (grid[i+k][j+k] != 'X') holds = false;
                }

                if (holds) {
                    flag = true;
                    break;
                }
            }
        }

        // print grid if found
        // we sift through the found values to find a tree and then our answer
        if (flag) {
            cout << t << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) cout << grid[i][j];
                cout << endl;
            }
        }

        // reset grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) grid[i][j] = '.';
        }
    }
}