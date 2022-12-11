#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#define PART 2

struct Monkey {
    queue<long> items;
    int add = 0;
    int mul = 1;
    int test = 1;
    long count = 0;
    long throwt = 0;
    long throwf = 0;
};

int main() {
    std::ifstream f("input.txt");
    string s; char c; long n, t, item, rounds = (PART == 1 ? 20 : 10000), q = 1;
    vector<Monkey> ms;
    while (f >> s >> s >> s >> s)
    {
        Monkey m;
        while (f >> n >> c) {
            m.items.push(n);
        }
        f.clear();
        f >> s >> s >> s >> s >> c >> s;
        if (c == '+')
            m.add = (s == "old" ? -1 : stoi(s));
        else
            m.mul = (s == "old" ? -1 : stoi(s));
        f >> s >> s >> s >> n;
        m.test = n;
        f >> s >> s >> s >> s >> s >> n;
        m.throwt = n;
        f >> s >> s >> s >> s >> s >> n;
        m.throwf = n;
        ms.push_back(m);
        q *= m.test; // The product of all `tests`
    }
    for (int r = 0; r < rounds; ++r) {
        for (int i = 0; i < ms.size(); ++i) {
            while (!ms[i].items.empty()) {
                item = ms[i].items.front();
                item += (ms[i].add < 0 ? item : ms[i].add);
                item *= (ms[i].mul < 0 ? item : ms[i].mul);
                item /= (PART == 1 ? 3 : 1);
                item %= q;
                t = (item % ms[i].test == 0 ? ms[i].throwt : ms[i].throwf);
                ms[t].items.push(item);
                ms[i].items.pop();
                ++ms[i].count;
            }
        }
    }
    sort(ms.begin(), ms.end(), [](Monkey m1, Monkey m2) { return m1.count > m2.count; });
    cout << (PART == 1 ? "silver: " : "gold: ") << ms[0].count * ms[1].count << "\n";
}
