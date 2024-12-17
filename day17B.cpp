#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back

/*
    we construct this number recursively using the program definition
    which is how the expression for val below is derived
    the main observation is that we go backwards since the current digit (base 8)
    depends on higher digits, so its better to work backwards

    we also don't take the smallest bit each time since its possible it could not work
    instead we construct all possibilities recursively, noting that the recursion tree is
    sparse enough since the recursion tree is strict (this runs very quickly)

    however, taking the smallest bit each time does lead to a valid sol, maybe it was 
    intentional puzzle design
*/
void construct (ll num, ll i, vector<ll> codes) {
    // depth 0, output construction
    if (i == 0) cout << num << endl;

    // test mod 8 residues
    for (int k = 0; k < 8; k++) {
        ll val = (k ^ 3 ^ 5) ^ ((8*num + k) >> (k ^ 3));

        // if print matches up, go down this path
        if ((val % 8) == codes[i-1]) {
            construct(8*num + k, i-1, codes);
        }
    }
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
    
    // recursively construct possible A values
    // we take the smallest one and verify it works with part a
    // we use depth 16 since the program has 16 codes, and we divide A by 8 each time
    construct(0, 16, codes);
}