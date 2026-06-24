#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <bits/stdc++.h>

using namespace std;

mt19937_64 rnd(time(0));

const int inf = (1ll << 30) - 1;
const double magic_constant = 69;
const int iter = 1500;
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
    if (last < 0 || gg[last / 3][last % 3] != -1) {
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

int weight(int move) {
    int tp = check(gg, move);
    if (tp != -1) {
        return 1000 * (tp - 1);
    }
    int ans = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gg[i][j] == -1) {
                for (int o = 0; o < 3; o++) {
                    for (int e = 0; e < 3; e++) {
                        if (grid[i][j][o][e] == move) ans++;
                        else if (grid[i][j][o][e] == move ^ 1) ans--;
                    }
                }
            } else {
                if (gg[i][j] == move) ans += 100;
                else ans -= 100;
            }
        }
    }
    return ans;
}

int monte_karlo(int last, int move, int dep) {
    int ans = check(gg, move);
    if (ans != -1 || dep == 0) {
        return weight(move);
    }
    int nex = next_move(last);
    int x = nex / 9, y = nex % 9;
    int ls2 = gg[x / 3][y / 3];
    grid[x / 3][y / 3][x % 3][y % 3] = move;
    gg[x / 3][y / 3] = check(grid[x / 3][y / 3], tur);
    ans = -monte_karlo((x % 3) * 3 + (y % 3), move ^ 1, dep - 1);
    gg[x / 3][y / 3] = ls2;
    grid[x / 3][y / 3][x % 3][y % 3] = -1;
    return ans;
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
    shuffle(a.begin(), a.end(), rnd);
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
    int ans;
    vector<int> sum(n, 0), cnt(n, 0);
    int c = n * 10;
    for (int i = 0; i < n; i++) {
        int nex = a[i].first * 9 + a[i].second;
        grid[(nex / 9) / 3][(nex % 9) / 3][(nex / 9) % 3][(nex % 9) % 3] = tur;
        int ls = gg[(nex / 9) / 3][(nex % 9) / 3];
        gg[(nex / 9) / 3][(nex % 9) / 3] = check(grid[(nex / 9) / 3][(nex % 9) / 3], tur);
        for (int j = 0; j < 10; j++) {
            sum[i] += -monte_karlo(((nex / 9) % 3) * 3 + (nex % 9) % 3, tur ^ 1, 30);
            cnt[i]++;
        }
        gg[(nex / 9) / 3][(nex % 9) / 3] = ls;
        grid[(nex / 9) / 3][(nex % 9) / 3][(nex / 9) % 3][(nex % 9) % 3] = -1;
    }
    for (int _ = 0; _ < iter; _++) {
        double s = -inf, pos = -1;
        for (int i = 0; i < n; i++) {
            double ss = (1. * sum[i]) / cnt[i] + magic_constant * sqrt(log(c) / cnt[i]);
            if (ss > s) {
                s = ss;
                pos = i;
            }
        }
        int nex = a[pos].first * 9 + a[pos].second;
        grid[(nex / 9) / 3][(nex % 9) / 3][(nex / 9) % 3][(nex % 9) % 3] = tur;
        int ls = gg[(nex / 9) / 3][(nex % 9) / 3];
        gg[(nex / 9) / 3][(nex % 9) / 3] = check(grid[(nex / 9) / 3][(nex % 9) / 3], tur);
        sum[pos] += -monte_karlo(((nex / 9) % 3) * 3 + (nex % 9) % 3, tur ^ 1, 30);
        cnt[pos]++;
        c++;
        gg[(nex / 9) / 3][(nex % 9) / 3] = ls;
        grid[(nex / 9) / 3][(nex % 9) / 3][(nex / 9) % 3][(nex % 9) % 3] = -1;
    }
    double s = -inf;
    for (int i = 0; i < n; i++) {
        double ss = (1. * sum[i]) / cnt[i] + magic_constant * sqrt(log(c) / cnt[i]);
        if (ss > s) {
            s = ss;
            ans = a[i].first * 9 + a[i].second;
        }
    }
    grid[(ans / 9) / 3][(ans % 9) / 3][(ans / 9) % 3][(ans % 9) % 3] = tur;
    gg[(ans / 9) / 3][(ans % 9) / 3] = check(grid[(ans / 9) / 3][(ans % 9) / 3], tur);
    cout << ans / 9 << " " << ans % 9;
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
