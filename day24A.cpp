#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

int main() {
    map<string, ll> val; // store value of each wire
    map<string, vector<pair<pss, pss>>> adj; // adj list of circuits for each wire
    queue<pair<pss,pss>> q; // queue for topo sort

    // read in input
    string line;
    while (getline(cin, line)) {
        if (line.size() == 0) continue;
        istringstream iss (line);
        string reg1; iss >> reg1; // read first wire

        // if first wire is a value definition, store it
        if (reg1[reg1.size()-1] == ':') {
            ll v; iss >> v;
            val[reg1.substr(0,reg1.size()-1)] = v;
        } else {
            // otherwise, read full circuit
            string op; iss >> op;
            string reg2; iss >> reg2;
            string _; iss >> _;
            string res; iss >> res;

            // store circuit in adj list
            pair<pss, pss> circuit = {{reg1, reg2}, {op, res}};
            adj[reg1].pb(circuit);
            adj[reg2].pb(circuit);
            
            // push to queue if we have seen both input wires
            if (val.count(reg1) && val.count(reg2)) q.push(circuit);
        }
    }

    // evaluate the circuit in topological sort order
    while (q.size() > 0) {
        pair<pss,pss> circuit = q.front(); q.pop();

        // read in circuit
        string reg1 = circuit.first.first; string reg2 = circuit.first.second;
        string op = circuit.second.first; string res = circuit.second.second;

        // evaluate resulting wire value
        if (op == "XOR") {
            val[res] = val[reg1] ^ val[reg2];
        } else if (op == "OR") {
            val[res] = val[reg1] | val[reg2];
        } else if (op == "AND") {
            val[res] = val[reg1] & val[reg2];
        }

        // if adjacent circuits have both input wires evaluated
        // add it to the queue
        for (auto c : adj[res]) {
            string r1 = c.first.first; string r2 = c.first.second;
            if (val.count(r1) && val.count(r2)) q.push(c);
        }
    }

    ll out = 0; // evaluate answer from z registers
    ll pow = 1;
    for (ll i = 0; i < 64; i++) {
        string zreg = "z";
        if (i < 10) {
            zreg += "0" + to_string(i);
        } else {
            zreg += to_string(i);
        }
        out += val[zreg] * pow;
        pow *= 2;
    }

    cout << out << endl;
}