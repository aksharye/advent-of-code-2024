#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

int main() {
    /*
        we note that printing the circuits in topological order* and separating the output by OR operation
        yields the components of our add circuit, which is a standard shift adder, where we

        XOR and AND the x and y wires
        XOR the previous carry with the above to get our Z register result
        AND the previous carry with the first to get our tentative carry
        OR the first with the tentative carry to get our actual carry

        based on these observations we could write code to check swaps given this structure
        but it is much faster to scan the output for anomalies, so this code makes the output readable
        so that finding the four swaps takes around 5 minutes

        * as a note, the topological order gives us this because we can only evaluate the add of a given bit
        given the results of the previous bits (since we need the carry info)
    */

    map<string, ll> val; // store value of each wire
    map<string, vector<pair<pss, pss>>> adj; // adj list of circuits for each wire
    queue<pair<pss,pss>> q; // queue for topo sort
    map<string, string> parser; // map to make output readable

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

        // swap x and y register for consistent ordering
        if (reg1[0] == 'y' && reg2[0] == 'x') {
            swap(circuit.first.first, circuit.first.second);
            swap(reg1, reg2);
        }

        // update parser to replace wires with their definition in output
        if (reg1[0] == 'x' && reg2[0] == 'y') {
            parser[res] = "(" + reg1 + " " + op + " " + reg2 + ") [" + res + "]";
        }

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

        // print output according to parser
        if (parser.count(reg1)) {
            cout << parser[reg1] << " ";
        } else {
            cout << reg1 << " ";
        }

        cout << op << " ";

        if (parser.count(reg2)) {
            cout << parser[reg2] << " ";
        } else {
            cout << reg2 << " ";
        }

        cout << "= ";

        if (parser.count(res)) {
            cout << parser[res] << " ";
        } else {
            cout << res << " ";
        }

        cout << "(" + op + ")" << endl;

        // separate output based on OR operation
        if (op == "OR") cout << "------------" << endl;
    }
}