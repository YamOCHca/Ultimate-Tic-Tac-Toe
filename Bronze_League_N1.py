import sys
import math
import random

def check(grid, move):
    if grid[0][0] == grid[1][1] == grid[2][2] != -1:
        if grid[0][0] == move:
            return 2
        else:
            return 0
    if grid[0][2] == grid[1][1] == grid[2][0] != -1:
        if grid[0][2] == move:
            return 2
        else:
            return 0
    fl = 1
    for i in range(3):
        if grid[i][0] == grid[i][1] == grid[i][2] != -1:
            if grid[i][0] == move:
                return 2
            else:
                return 0
        if grid[0][i] == grid[1][i] == grid[2][i] != -1:
            if grid[0][i] == move:
                return 2
            else:
                return 0
        if min(grid[i]) == -1:
            fl = 0
    if fl:
        return 1
    else:
        return -1

def weight(gr, move):
    ans = 0
    gg = [[-1 for i in range(3)] for j in range(3)]
    for i in range(3):
        for j in range(3):
            tp = check(gr[i][j], move)
            if tp == 2:
                ans += 100
                gg[i][j] = move
            elif tp == 0:
                ans -= 100
                gg[i][j] = move ^ 1
            else:
                for o in range(3):
                    for e in range(3):
                        if gr[i][j][o][e] == move:
                            ans += 1
                        elif gr[i][j][o][e] == move ^ 1:
                            ans -= 1
    tp = check(gg, move)
    if tp == 2:
        ans = 1000
    elif tp == 0:
        ans = -1000
    return ans

def to_go(grid, last):
    gg = [[check(grid[i][j], 0) == -1 for j in range(3)] for i in range(3)]
    ans = []
    if last[0] != -1 and gg[last[0]][last[1]]:
        for i in range(3):
            for j in range(3):
                if grid[last[0]][last[1]][i][j] == -1:
                    ans.append((last[0] * 3 + i, last[1] * 3 + j))
    else:
        for i in range(3):
            for j in range(3):
                for o in range(3):
                    for e in range(3):
                        if gg[i][j] and grid[i][j][o][e] == -1:
                            ans.append((i * 3 + o, j * 3 + e))
    return ans

def dfs(grid, move, last, dep):
    way = to_go(grid, last)
    random.shuffle(way)
    if len(way) == 0 or dep == 0:
        return weight(grid, move ^ 1)
    ans = -2000 * (-1 ** dep)
    for i in way:
        grid[i[0] // 3][i[1] // 3][i[0] % 3][i[1] % 3] = move
        if dep & 1:
            ans = min(ans, dfs(grid, move ^ 1, (i[0] % 3, i[1] % 3), dep - 1))
        else:
            ans = max(ans, dfs(grid, move ^ 1, (i[0] % 3, i[1] % 3), dep - 1))
        grid[i[0] // 3][i[1] // 3][i[0] % 3][i[1] % 3] = -1
    return ans
            
fl = 1

tur = -1

grid = [[[[-1, -1, -1], [-1, -1, -1], [-1, -1, -1]] for i in range(3)] for j in range(3)]

while True:
    x, y = map(int, input().split())
    n = int(input())
    a = [tuple(map(int, input().split())) for i in range(n)]
    if fl:
        if x == y == -1:
            tur = 0
        else:
            tur = 1
        fl = 0
    if not (x == y == -1):
        grid[x // 3][y // 3][x % 3][y % 3] = tur ^ 1
    best = 2000
    pos = 0
    for i in range(n):
        grid[a[i][0] // 3][a[i][1] // 3][a[i][0] % 3][a[i][1] % 3] = tur
        s = dfs(grid, tur ^ 1, (a[i][0] % 3, a[i][1] % 3), 1)
        if s < best:
            best = s
            pos = i
        grid[a[i][0] // 3][a[i][1] // 3][a[i][0] % 3][a[i][1] % 3] = -1
    print(*a[pos])
    grid[a[pos][0] // 3][a[pos][1] // 3][a[pos][0] % 3][a[pos][1] % 3] = tur
