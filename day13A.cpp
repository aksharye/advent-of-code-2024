#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
#define pb push_back

// i did the same thing for parts A and B because i didnt read the 100 constraint for A

// helper functions to read in the values of X and Y
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
    // keep track of tokens
    ll tokens = 0;

    // read in claw machine values
    string line;
    ll ct = 0;
    ll XA, XB, YA, YB;
    while (getline(cin, line)) {
        if (line.size() == 0) continue;
        istringstream iss (line);

        ct++;
        if (ct % 3 == 0) {
            string _, x, y; iss >> _ >> x >> y;

            ll X = read_x(x); ll Y = read_y(y);

            // solve the system, count tokens only if sol exists
            // i checked beforehand to make sure there were no eqns with inf sols
            ll XXB = XB; XXB *= YA;
            ll YYB = YB; YYB *= XA;

            ll XX = X; XX *= YA;
            ll YY = Y; YY *= XA;

            if (abs(XX - YY) % abs(XXB - YYB) == 0) {
                ll B = (XX - YY)/(XXB - YYB);
                if (abs(X - B * XB) % abs(XA) == 0) {
                    ll A = (X - B * XB)/XA;
                    tokens += 3 * A + B;
                }
            }
        } else if (ct % 3 == 1) {
            string _, __, x, y; iss >> _ >> __ >> x >> y;
            XA = read_x(x);
            YA = read_y(y);
        } else {
            string _, __, x, y; iss >> _ >> __ >> x >> y;
            XB = read_x(x);
            YB = read_y(y);
        }   
    }

    cout << tokens << endl;
}