#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <bits/stdc++.h>

using namespace std;

mt19937_64 rnd(173124062026);

int grid[3][3][3][3];
int gg[3][3];
int tur = -1;
bool is_turn_known = false;

int check(int a[3][3], int move) {
    if (a[0][0] == a[1][1] && a[1][1] == a[2][2] && a[0][0] != -1) {
        if (a[0][0] == move) return 2;
        else return 0;
    }
    if (a[0][2] == a[1][1] && a[1][1] == a[2][0] && a[0][2] != -1) {
        if (a[0][2] == move) return 2;
        else return 0;
    }
    bool fl = 1;
    for (int i = 0; i < 3; i++) {
        if (a[i][0] == a[i][1] && a[i][1] == a[i][2] && a[i][0] != -1) {
            if (a[i][0] == move) return 2;
            else return 0;
        }
        if (a[0][i] == a[1][i] && a[1][i] == a[2][i] && a[0][i] != -1) {
            if (a[0][i] == move) return 2;
            else return 0;
        }
        if (a[i][0] == -1 || a[i][1] == -1 || a[i][2] == -1) {
            fl = 0;
        }
    }
    if (fl) return 1;
    else return -1;
}

int next_move(int last) {
    //cout << last / 3 << " " << last % 3 << '\n';
    if (gg[last / 3][last % 3] != -1) {
        for (int i = 0; i < 81; i++) {
            int x = rnd() % 9, y = rnd() % 9;
            if (gg[x / 3][y / 3] == -1 && grid[x / 3][y / 3][x % 3][y % 3] == -1) {
                return x * 9 + y;
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (gg[i][j] != -1) continue;
                for (int o = 0; o < 3; o++) {
                    for (int e = 0; e < 3; e++) {
                        if (grid[i][j][o][e] == -1) {
                            return (i * 3 + o) * 9 + (j * 3 + e);
                        }
                    }
                }
            }
        }
    } else {
        for (int i = 0; i < 9; i++) {
            int x = rnd() % 3, y = rnd() % 3;
            if (grid[last / 3][last % 3][x][y] == -1) {
                return ((last / 3) * 3 + x) * 9 + ((last % 3) * 3 + y);
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[last / 3][last % 3][i][j] == -1) {
                    return ((last / 3) * 3 + i) * 9 + ((last % 3) * 3 + j);
                }
            }
        }
    }
    return -1;
}

void solve() {
/*/*
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i) {
            for (int j = 0; j < 30; j++) {
                cout << '-';
            }
            cout << '\n';
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j) {
                cout << "|";
            }
            cout << grid[i / 3][j / 3][i % 3][j % 3] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << gg[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
/*
*/
    int lx, ly;
    cin >> lx >> ly;
    if (!is_turn_known) {
        if (lx == -1 && ly == -1) {
            lx = 0, ly = 0;
            tur = 0;
        } else {
            tur = 1;
            grid[lx / 3][ly / 3][lx % 3][ly % 3] = 0;
        }
        is_turn_known = true;
    } else {
        grid[lx / 3][ly / 3][lx % 3][ly % 3] = tur ^ 1;
        gg[lx / 3][ly / 3] = check(grid[lx / 3][ly / 3], tur);
    }
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    /*
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i) {
            for (int j = 0; j < 11; j++) {
                cout << '-';
            }
            cout << '\n';
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j) {
                cout << "|";
            }
            cout << grid[i / 3][j / 3][i % 3][j % 3] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << gg[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
    */
    int nex = next_move((lx % 3) * 3 + ly % 3);
    grid[(nex / 9) / 3][(nex % 9) / 3][(nex / 9) % 3][(nex % 9) % 3] = tur;
    gg[(nex / 9) / 3][(nex % 9) / 3] = check(grid[(nex / 9) / 3][(nex % 9) / 3], tur);
    cout << nex / 9 << " " << nex % 9;
}

int main()
{
    memset(grid, -1, sizeof(grid));
    memset(gg, -1, sizeof(gg));
    while (true) {
        solve();
        cout << '\n';
    }
    return 0;
}
