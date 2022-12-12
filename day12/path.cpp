#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

#define PART 2

using namespace std;

struct Cell {
    char c;
    int dest;
    int vis = 0;
    int x, y;
    int dist = 0;
};

int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main() {
    ifstream f("input.txt");
    f >> noskipws;
    vector<vector<Cell>> cs = {{}};
    char c; int sx, sy;
    while (f >> c) {
        int y = cs.size() - 1;
        int x = cs[y].size();
        if (c == '\n') {
            cs.push_back({});
            continue;
        } else if (c == 'S') {
            c = 'a';
            if (PART == 1) {
                sy = y;
                sx = x;
            }
        }
        if (PART == 2 && c == 'E') {
            sy = y;
            sx = x;
        }
        int dest = (PART == 1 ? c == 'E' : c == 'a');
        cs[cs.size() - 1].push_back({(c == 'E' ? 'z' : c), dest, 0, x, y});
    }
    cs.pop_back();
    queue<Cell*> q;
    q.push({&cs[sy][sx]});
    for (int k = 0; !q.empty(); ++k) {
        Cell *c = q.front();
        if (c->dest) {
            cout << (PART == 1 ? "silver: ": "gold: ") << c->dist << "\n";
            return 0;
        }
        for (int k = 0; k < 4; ++k) {
            int x = c->x + dirs[k][0];
            int y = c->y + dirs[k][1];
            if (x >= 0 && y >= 0 && y < cs.size() && x < cs[0].size() && 
                !cs[y][x].vis && 
                (PART == 1 ? (cs[y][x].c - 1 <= c->c) : (c->c - 1 <= cs[y][x].c))) 
            {
                cs[y][x].dist = c->dist + 1;
                cs[y][x].vis = 1;
                q.push(&cs[y][x]);
            }
        }
        q.pop();
    }
}
