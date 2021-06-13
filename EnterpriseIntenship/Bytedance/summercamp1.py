#coding=utf-8
import sys

def recur(root:int, value: list,n:int ) -> list:
    if root >=n:
        return [0,0]
    res = [0,0 ]
    left = recur(root*2,values,n)
    right = recur(root*2+1,values,n)
    res[0] = max(left[0],left[1]) +max(right[0],right[1])
    res[1] = left[0]+right[0]+value[root]
    return res
if __name__ == "__main__":
    # 读取第一行的n
    n = int(sys.stdin.readline().strip())
    ans = 0
    # 读取行
    line = sys.stdin.readline().strip()
    # 把每一行的数字分隔后转化成int列表
    values = list(map(int, line.split()))
    values.insert(0,0)
    #res = values[0]
    res= recur(1,values,n+1)
    print(max(res[0],res[1]))
    
