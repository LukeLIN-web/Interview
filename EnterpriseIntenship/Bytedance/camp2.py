#coding=utf-8
import sys
from collections import deque
if __name__ == "__main__":
    # 读取第一行的n
    line = sys.stdin.readline().strip()
    l1 = list(map(int, line.split()))
    vnum = l1[0] # vetex number
    m = l1[1]
    graph = []
    for i in range(vnum):
        # 读取每一行
        line = sys.stdin.readline().strip()
        # 把每一行的数字分隔后转化成int列表
        values = list(map(int, line.split()))
        graph.append(values)
    tmp = sys.stdin.readline().strip()
    affs = list(map(int, tmp.split()))
    q= deque()
    q.append(affs[0]) # 从一个到其他所有的
    distance = [-1 for i in range(vnum)]
    distance[affs[0]] =0
    path = []
    while len(q) != 0:
        v = q.popleft()
        path.append(v)  
        for w in range(vnum):
            j = graph[v][w]
            if j == 1 and distance[w] == -1:
                distance[w] = distance[v] +1
                q.append(w)
    #res = values[0]
    print(len(path))