#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

#define INTERESTING(n) ((n - 20) % 40 == 0)

struct Addx {
    int val;
    int n;
};

void print(int cycle, int x) {
    if ((cycle % 40) - x <= 2 && (cycle % 40) - x >= 0)
        cout << "#";
    else
        cout << ".";
    if (cycle % 40 == 0)
        cout << "\n";
}

void resolve(vector<Addx> &promises, int &x) {
    for (int i = 0; i < promises.size(); ++i) {
        Addx &p = promises[i];
        --p.n;
        if (p.n == 0) {
            x += p.val;
            promises.erase(promises.begin() + i);
        }
    }
}

int strength_sum(ifstream &f) {
    int sum = 0; int x = 1; string s;
    vector<Addx> addxs;
    for (int c = 1; ; ++c) {
        if (addxs.empty() || addxs[addxs.size() - 1].n != 1) {
            if (getline(f, s).eof())
                break;
            if (s[0] == 'a') {
                int val;
                sscanf(s.c_str(), "%*s %d", &val);
                addxs.push_back({.val = val, .n = 2});
            }
        }
        print(c, x);
        if (INTERESTING(c)) {
            sum += c * x;
        }
        resolve(addxs, x);
    }
    return sum;
}

int main() {
    ifstream f("input.txt");
    int sum = strength_sum(f);
    cout << "silver: " << sum << "\n";
}
