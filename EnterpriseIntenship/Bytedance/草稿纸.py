from collections import deque
from typing import List
st = '9'
# str = "abc123"
#coding=utf-8
# 本题为考试单行多行输入输出规范示例，无需提交，不计分。
import sys 
for line in sys.stdin:
    a = line.split()
    print(int(a[0]) + int(a[1]))
#coding=utf-8
# 本题为考试多行输入输出规范示例，无需提交，不计分。
import sys
if __name__ == "__main__":
    # 读取第一行的n
    n = int(sys.stdin.readline().strip())
    ans = 0
    for i in range(n):
        # 读取每一行
        line = sys.stdin.readline().strip()
        # 把每一行的数字分隔后转化成int列表
        values = list(map(int, line.split()))
        for v in values:
            ans += v
    print(ans)
e = input('输入你最喜欢的数字:')
print("dotcpp的网址:",e)
n=9
l = [[0,2,2],[4,2,4],[2,13,1000000000]]
# for i in l:
#     print(i)
# for i in str:
#     if i.isdigit() :
#         print( (int(i),i) )
#print( (int(st),str))
# i = 0
# while i < 3:
#     i = 4
#     print( (int(i),i) )
# t = Solution()
# print(t.decodeString("10[we]"))
dict = {n %3: 0}
degree = [i for i in range(8)]
dq = deque([1,2,3])

# print (2 in dict.keys())
# f = open('log.txt','w')
# for i in range(1,400*400+1,1):
#     print(str(1),end= " ", file=f)
# f.close()