#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

// helper to evaluate combo operand
ll combo(ll k, ll reg []) {
    if (k <= 3) return k;
    if (k <= 6) return reg[k-4];
    return 7;
}

int main() {
    // read in registers
    ll reg [3];
    for (int i = 0; i < 3; i++) {
        string _, __, s; cin >> _ >> __ >> s;
        reg[i] = stoll(s); 
    }

    // read in program, convert to codes
    string ___, prog; cin >> ___ >> prog;
    vector<ll> codes;

    for (int i = 0; i < prog.size(); i+=2) {
        codes.pb(prog[i] - '0');
    }

    // simulate program
    int i = 0; // pc
    string out = "";
    while (i < codes.size()) {
        ll code = codes[i];
        ll val = codes[i+1];
        if (code == 0) {
            reg[0] = reg[0] / (1 << combo(val,reg)); i += 2;
        } else if (code == 1) {
            reg[1] ^= val; i += 2;
        } else if (code == 2) {
            reg[1] = combo(val, reg) % 8; i += 2;
        } else if (code == 3) {
            if (reg[0] != 0) {
                i = val;
            } else {
                i += 2;
            }
        } else if (code == 4) {
            reg[1] ^= reg[2]; i += 2;
        } else if (code == 5) {
            out.pb('0' + combo(val, reg) % 8); out.pb(','); i += 2;
        } else if (code == 6) {
            reg[1] = reg[0] / (1 << combo(val,reg)); i += 2;
        } else {
            reg[2] = reg[0] / (1 << combo(val,reg)); i += 2;
        }
    }

    // remove the last comma
    cout << out.substr(0, out.size()-1) << endl;
}