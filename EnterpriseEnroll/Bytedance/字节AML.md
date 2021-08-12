字节AML

### AML [机器学习]()平台实习

链接：https://www.nowcoder.com/discuss/362640?type=post&order=time&pos=&page=1&ncTraceId=&channel=-1&source_id=search_post_nctrack

（有两个团队，一个是做[机器学习]()平台的，一个是做[算法]()优化的） 

 一面 

 [二叉树]()序列化与反序列化 

```python
class Codec:
    def serialize(self, root):
        if not root:
            return "" # can not return "[]"
        s = []
        dq = deque()
        dq.append(root)
        while dq :
            node = dq.popleft()
            if node != None:
                s.append(str(node.val))
                dq.append(node.left)
                dq.append(node.right)
            else:
                s.append('None')
        print(s)
        # return "[" +",".join(s)+"]" 
        return ",".join(s)

    def deserialize(self, data):
        if not data:
            return []
        # s = data[1:-1]
        num = data.split(",")
        root = TreeNode(num[0])
        dq = deque()
        dq.append(root)
        i = 1 
        while dq :
            node = dq.popleft()
            if num[i] != 'None':
                node.left = TreeNode(int(num[i]))
                dq.append(node.left)
            i +=1
            if num[i] != "None":
                node.right = TreeNode(int(num[i]))
                dq.append(node.right) 
            i +=1
        return root
```

 有没有看过kfserving[源码]() 

 Yarn的调度 

 K8S的底层网络 

 二面 

 实现优先队列 

 手写迪杰斯特拉[算法]() 

 之前实习中做的有意思的事情 

 三面 

 粘包问题 

 实现sharedptr 

 Malloc实现原理 

 四面 

 聊之前实习做的事情 

 看一段论文，现场实现

### aml[机器学习]()系统研发： 

  一面（50min）：问[项目]()，20分钟，当中想深入问一些网络和cpu体系结构，然而这两块我基本没看过，直接跳过，后面半小时做题。上来先是两道python看代码说结果，然后三道[c++]()题，素数判断（写完后问我sqrt复杂度，我说牛顿迭代是二阶的，然后根据精度要求反推复杂度即可，没具体算），lis（不要求优化到nlogn）

```python
class Solution: # lc 1964
    def longestObstacleCourseAtEachPosition(self, obstacles: List[int]) -> List[int]:
        st =[obstacles[0]]
        res = [1]
        obstacles = obstacles[1:]
        for i, height in enumerate(obstacles):
            if  height >= st[-1]:
                st.append(height)
                res.append(len(st))
            else:
                l = 0
                r = len(st)-1
                while l <r :
                    mid =  l + (r-l)//2
                    if st[mid] > height :
                        r = mid 
                    elif st[mid] <= height:
                        l = mid +1
                st[l] =  height
                res.append(l+1)
        return res
```

中序波兰式（只考虑加法乘法和括号，细节忘光了，面试官提示了括号怎么处理才顺利写出来，光这道题就写了20多分钟QAQ） lc上没有

python`isdigit()`函数是检测输入字符串是否只由数字组成(str_2.isalpha())*#isalnum()判断是否数字和字母的组合*  注意：如果字符串中含有空格，也会返回False

```c
PROCESS BEGIN:
   1.从左往右扫描中缀表达式串s，对于每一个操作数或操作符，执行以下操作;
       2.IF (扫描到的s[i]是操作数DATA)
　　　　　    将s[i]添加到输出串中;
               3.IF (扫描到的s[i]是开括号'(')
                        将s[i]压栈;
               4.WHILE (扫描到的s[i]是操作符OP)
                       IF (栈为空 或 栈顶为'(' 或 扫描到的操作符优先级比栈顶操作符高)
                             将s[i]压栈;
                             BREAK;
                       ELSE
                             出栈至输出串中
               5.IF (扫描到的s[i]是闭括号')')
                       栈中运算符逐个出栈并输出，直到遇到开括号'(';
                       开括号'('出栈并丢弃;
               6.返回第1.步
　　       7.WHILE (扫描结束而栈中还有操作符)
                        操作符出栈并加到输出串中
PROCESS END
```

  二面（40min）：自我介绍的时候面试官麦有点不太好，他说：没事，反正待会就做题了。第一道：快排和并查集二选一，我选了并查集，秒了。第二道：拓扑[排序]()，秒了。 

```python
#findOrder lc210
class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) :
        n = len(prerequisites)
        inlist = [0 for i in range(numCourses) ]
        edges = collections.defaultdict(list)
        for info in prerequisites:
            inlist[info[0]] +=1
            edges[info[1]].append( info[0]) 
        # 所有入度为 0 的节点都被放入队列中，它们就是可以作为拓扑排序最前面的节点，并且它们之间的相对顺序是无关紧要的。
        dq = deque()
        res = []
        for i in range(numCourses):
            if inlist[i] == 0 :
                dq.append(i)
        while len(dq)>0:
            node = dq.popleft()
            res.append(node)
            for j in edges[node]:
                inlist[j] -=1
                if inlist[j] == 0:
                    dq.append(j)
        if len(res) == numCourses:
            return res
        else:
            return []
```

  三面（45min）：自我介绍，说一下[项目]()。 题目: 二叉树选择权重和最大的结点，要求选择的任意两个结点不相邻。秒了，最后15分钟问了一些进程线程之类的八股，被我强行扯到[项目]()上。

```python
# 递归的参数 , 根结点
# 递归的终止条件   null
# 单层逻辑,  偷 / 不偷. 偷就num+ 
#dp[0] 不偷最大金钱
class Solution:
    def rob(self, root: TreeNode) -> int:
        def cur(root: TreeNode) -> List:
            if root == None:
                return [0,0]
            left = cur(root.left) 
            right = cur(root.right)
            stole = root.val + left[0] + right[0] # 下面两个不偷
            nosteal = max(right[0],right[1]) + max(left[0] , left[1]) #下面两个的最大
            return [nosteal,stole]
        l = cur(root)
        return max(l[0],l[1])
```

  四面（45min）：leader面，第一道是场景题，挺有意思的，具体题目就不放出了，一开始想了歪门邪道，面试官指出这不太数学，让我重新想一个方法，想了几分钟做出来了。第二道写了一个LFU cache，没写完，大致看了我的思路，指出空间复杂度较高。 

```python
class Node:
    def __init__(self, key, val, pre=None, nex=None, freq=0):
        self.pre = pre
        self.nex = nex
        self.freq = freq
        self.val = val
        self.key = key
        
    def insert(self, nex):
        nex.pre = self
        nex.nex = self.nex
        self.nex.pre = nex
        self.nex = nex
    
def create_linked_list():
    head = Node(0, 0)
    tail = Node(0, 0)
    head.nex = tail
    tail.pre = head
    return (head, tail)

class LFUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.size = 0
        self.minFreq = 0
        self.freqMap = collections.defaultdict(create_linked_list)
        self.keyMap = {}
# 看前面有没有, 如果有, 删除这个元素, 如果fremap[freq]没了pop掉
    def delete(self, node):
        if node.pre:
            node.pre.nex = node.nex
            node.nex.pre = node.pre
            if node.pre is self.freqMap[node.freq][0] and node.nex is self.freqMap[node.freq][-1]:
                self.freqMap.pop(node.freq)
        return node.key
        #删除feremap中这个频率, 加到下一个频率的最后, 然后更新minFreq
    def increase(self, node):
        node.freq += 1
        self.delete(node) # 先删除
        self.freqMap[node.freq][-1].pre.insert(node) #[-1]是tail
        if node.freq == 1:
            self.minFreq = 1
        elif self.minFreq == node.freq - 1:
            head, tail = self.freqMap[node.freq - 1]
            if head.nex is tail:
                self.minFreq = node.freq # 如果下面的频率已经被删除的了话,那就min就为大一些的. 

    def get(self, key: int) -> int:
        if key in self.keyMap:
            self.increase(self.keyMap[key]) # 找到
            return self.keyMap[key].val # return
        return -1
#在就更新, 不在就插keymap, 如果超出就deletemin, 从keymappop. 最后插入node.
    def put(self, key: int, value: int) -> None:
        if self.capacity != 0:
            if key in self.keyMap:
                node = self.keyMap[key]
                node.val = value # 更新值
            else:
                node = Node(key, value) # 默认freq为0 
                self.keyMap[key] = node
                self.size += 1
            if self.size > self.capacity:
                self.size -= 1
                deleted = self.delete(self.freqMap[self.minFreq][0].nex)#头部. 
                self.keyMap.pop(deleted)
            self.increase(node) # 最后都要 更新频率
```

  PS:二面到四面是一天内面完的，[百度]()的二面也在这一天

### 机器学习平台研发

[字节aml面经，已收意向书_笔经面经_牛客网 (nowcoder.com)](https://www.nowcoder.com/discuss/458758?type=all&order=time&pos=&page=1&ncTraceId=&channel=-1&source_id=search_all_nctrack)

三面技术面每面两道题加问问简历里的实习[项目]()。 

  一面： 

  1、翻转的有序数组，不知道旋转点，log查找值的位置（2次二分 

  2、设计cash缓存每次访问后更新并删除最久没有访问的内存（我撸了个线段树，面试官表示hashmap可以做，但是我想了下感觉不好维护 

  二面： 

  1、dp，n个物品，每个基础价值ai，第k个拿会减去（k-1）*bi的价值，要拿m个使总价值最大（卡了，面试官给了提示过了  

先按b排序，然后dp。先考虑简单情况，n=m，此时，显而易见你只要从bi大的往小的拿就能最优。那么拿m个的时候，假如你先考虑是否拿的物品bi一定大于后考虑是否拿的物品bj，那么考虑完是否拿的同时，顺序是一定的，如果同时知道这是第几个拿的物品，该物品的最终价值也是确定的。所以dp需要一个纬度记录你已经拿了几个物品，一个纬度记录考虑到第几个物品。最后可以滚动数组优化空间。

  2、贪心，n个怪物，每个怪物有攻击ai，勇者防御初始为d，每打一只防御+1，防御<ai的话直接受到bi的伤害。问最优打怪顺序。（没做出来，给了个n=1000的网络流做法，面试官表示n是10w也能贪心做,   可以并查集o(n)堆就是用来做贪心的 ai bi    建立最小堆 每次pop堆顶就行 .先按bi排个序，大到小，这样你先能无伤尽量无伤干就可以贪出最优解了。对于某个怪的攻击找到第一个能防住且尚未占用的回合，找不到往前扔。

d是增长的。目前bi最小的打不过的可能后面可以打过但你先打了。
hack你代码的数据：a，1 10000；b， 2 10000；d=1。首先没有无伤可以打的，你会先打b=2。但是如果先打b=10000，下一次就能无伤打b=2

  三面： 

  1、多线程写稀疏矩阵*稠密矩阵 

我是对于稀疏矩阵用hashmap的key，val对存储，矩阵相乘时候必定是一层乘法一层加法，构建有向无环图每个节点意味着两个数字的相乘或者对某个地址值的增加。然后就是划分子图分配给各个线程去并行运行。大致思路就这样。

  2、[二叉树]()序列化和反序列化+校验

至于[项目](https://www.nowcoder.com/jump/super-jump/word?word=项目)经历的话其实答的不好。不过面试官不太看重的样子。

