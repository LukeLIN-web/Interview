我记得ee这边，有两种情况，一个是你学校好，成绩足够好，而且有国奖，即很有hkpfs竞争力的，虽然没有高水平论文，也有可能被选上。另一种情况是学校好，成绩一般，当然也没有国奖，但是发表过高水平论文，可能性也比较大。（我记得当时答疑会上一人说发表过trans on image processing，当时汪小刚老师说过这个可以加分）


答疑会上，cs和ie这边我记得当时林老师没有怎么说国奖，成绩这种事，主观认为可能更看重科研潜力吧～林老师都出来答了，我就不班门弄斧啦。链接：https://www.zhihu.com/question/41537308/answer/124309142

# ece

香港中文大学电子工程学系在深圳举行的博士生入学面

自我介绍blabla的，大约1-3分钟自我介绍

每个教授喜欢问的问题都不一样，所以真的还挺看人品

你平时有啥爱好啊，你觉得香港哪里好啊,rowing , rowing club.  更加暖和, 杭州冬天有一点冷.

为啥选这个学校:

 I wish to possess a global perspective and obtain solid academic training, to lay a solid foundation for my future research career. I believe that erudite professors will be of great help to my accumulation of knowledge.

口语没必要这么长. 

 Your school enjoys a worldwide prestige with students around the world converging here to pursue professional growth. These excellent fellows are valuable resources, and to exchange ideas with them is an opportunity to treasure for a lifetime.

要用 英语讲出来

# CSE

cuhk面试历来是要考算法题目的

https://zhuanlan.zhihu.com/p/142840101

三位男性导师，看了一下名字，估摸着是一个中国人，一个香港人，一个美国人

N*N的矩阵，从左上角开始出发，只能向右走或向下走，一共有多少种走法?

Is it the polynomial of N or exponential of N

一道是给一张图判断是否可以2-colorable写个搜索就行；另一个是很简单的贪心题

minimum spanning tree相关最小生成树的算法(Prim算法

生成树是将原图的全部顶点以最少的边连通的子图,权值总和最小的生成树则称为图的最小生成树。

prim 是对所有u∈U，v∈(V – U)（其中u,v表示顶点）的边(u,v)中不断找一条权值最小的边(u’,v’)，将这条边加入到集合T中，将顶点v’加入集合U中。U为最小生成树的顶点集合,V为所有顶点的集合.

解最小生成树的另一种常见的算法是Kruskal算法，它比Prim算法更直观。
Kruskal算法的做法是：每次都从剩余边中选取权值最小的,当然，这条边不能使已有的边产生回路.如何判断两个顶点是否属于同一个连通分量呢？这个可以参照并查集的做法解决。

Cuhk大概三天就出结果了。

面试录音

如果只用两种颜色给图进行染色，那么确定一个顶点后，和它相邻的顶点的颜色也就确定了。因此，选择任意一个顶点出发，依次确定相邻顶点的颜色，就可以判断是否可以被2种颜色染色了。这个问题使用DFS很容易解决。

华中科技大学计算机acm班 system方向，算法题：求一个数组中和为t的所有子数组，用动态规划做被老师说复杂度太高, 后面被问了泰勒展开式。

要用前缀和，map存储， 不然会超时。 

```python
#subArraySum
res = 0
​    dic = {0: 1 }
​    pre =0
​    for i in range(len(nums)):
​      pre += nums[i]
​      if pre-k in dic:
​        res += dic[pre-k]
​      if pre in dic:
​        dic[pre] = dic[pre] +1 # 如果没有会报错
​      else:
​        dic[pre] = 1 # add element
​    return res
```

Derivative 导数

JHU MSCS学长，医学方向，算法题是一个数列找出最常出现的数，空间复杂度有要求, Constant extra memory space  数据大就sorted   traverse.，边扫边记录相同的数的个数。

在一个很长的数组中，如何找出出现频率最高的数？该算法的时间复杂度和空间复杂度？

如果值域在0-100, 那就开100长度的数组b, 然后 扫描,在b数组第三个位置的下标加一，也就是b[3] = 1 . 复杂度为On

数列里第k大的数

你来cuhk可以干啥? 

反问

何时发邮件通知  .  录用率：

When will get the notification? What percentage of people will receive offer?

问了很多问题，比如“比较下快排和归并排序”、“快排的原理”、“介绍下二分算法”

both from idea divide and conquer, 递归实现, 归并 merge , 快排 partition分区. 

**平均时间复杂度都是 O(logN), 但归并排序的常数部分比快排大，因而速度慢**

归并排序需要 O(n) space complexity. 是稳定的 stable

quick sort  unstable .don't need extra space complexity. 如果 本来有序, 那么退化为O(square of n)

另一个老师开始问操作系统相关的，也都是一些基础知识，但就是不知道用英文该怎么说

# 实际面试

就两分钟介绍一下自己.

然后就考题目,

8个bit, 一次翻转两bit, 可以翻转很多次, 最多可以产生多少个数?教授三分钟看我不会就move to next了

因为只能有偶数个被反转,C(0,8)+C(2,8)+C(4,8)+C(6,8)+C(8,8)

还有就问个和rank的关系, 

![](https://pic3.zhimg.com/80/v2-3c91966739eeace08b1e78f61873dfce_1440w.jpg)

然后问 如果只用两种颜色给图进行染色，怎么染色?

为啥用dfs? 你还知道别的算法吗?

何时发邮件通知  .  录用率： 没有录取率,认真考虑每一个学生.

我室友问了quicksort, merge sort,二分查找. 二叉搜索树.教授觉得他cs基础比较薄弱, 他然后和教授说, 他没上过数据结构,  他一周前刚学的.  不是为了面试 , 而是为了弥补自己薄弱的基础.教授问他你是不是知道了面试会考啥.  还考了指针的大小.

答案是:在32位系统中为4字节；在64位系统中为8字节；

我又面试了一个老师

通过可以先来做毕设, 来工作工作适应适应环境.  

英语提高.   研究要写文章, 非常重要. 英语的论文写多了对你很有好处，就写过论文，没写过论文，完全就是两个人

那个老师还问我说为什么你不去美国？

我说香港比较近，又可以享受海外留学的待遇

