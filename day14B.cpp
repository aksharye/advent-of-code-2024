#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

// grid


// helper to check bounds
void setIO(string name){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}


int main() {    
    setIO("test");

    // read in grid
    ll q [] = {0, 0, 0, 0};
    
    ll m, n; m = 101; n = 103;
    ll z = 0;
    string line;
    vector<vector<ll>> vv;
    while (getline(cin, line)) {
        istringstream iss (line);
        string p, v; iss >> p >> v;

        string spx, spy, svx, svy;

        ll k = 2;
        while (p[k] != ',') {
            spx.pb(p[k]); k++;
        }
        k++;
        while (k < p.size()) {
            spy.pb(p[k]); k++;
        }

        k = 2;
        while (v[k] != ',') {
            svx.pb(v[k]); k++;
        }
        k++;
        while (k < v.size()) {
            svy.pb(v[k]); k++;
        }

        ll px, py, vx, vy;
        px = stoll(spx); py = stoll(spy); vx = stoll(svx); vy = stoll(svy);

        vector<ll> vvv = {px, py, vx, vy};
        vv.pb(vvv);
    }

    char grid [103][101]; 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) grid[i][j] = '.';
    }

    for (int zz = 0; zz < 100000; zz++) {

        for (int i = 0; i < vv.size(); i++) {
            vv[i][0] += vv[i][2]; vv[i][0] %= m; vv[i][0] += m; vv[i][0] %= m;
            vv[i][1] += vv[i][3]; vv[i][1] %= n; vv[i][1] += n; vv[i][1] %= n;

            grid[vv[i][1]][vv[i][0]] = '1';
        }

        bool legend = false;

        for (int i = 1; i < n-3; i++) {
            for (int j = 1; j < m-3; j++) {
                bool wow = true;
                for (int k = -2; k <= 2; k++) {
                    if (grid[i+k][j+k] != '1') {
                        wow = false;
                    }
                }
                if (wow) {
                    legend = true;
                    break;
                }
            }
        }
        if (legend) {
            cout <<zz+1 << endl;
            for (int i = 0; i < n; i++) {

                for (int j = 0; j < m; j++) cout << grid[i][j];
                cout << endl;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) grid[i][j] = '.';
        }
    }



}