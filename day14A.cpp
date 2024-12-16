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

        // simulate 100 seconds with mod arithmetic
        px += 100 * vx; px %= m; px += m; px %= m;
        py += 100 * vy; py %= n; py += n; py %= n;

        // find the quad (with binary encoding)
        ll quad = 0;
        if (px == m / 2 || py == n / 2) continue;
        if (px > m / 2) quad += 2;
        if (py > n / 2) quad += 1;
        q[quad]++;
    }

    // find safety factor
    cout << q[0] * q[1] * q[2] * q[3] << endl;
}