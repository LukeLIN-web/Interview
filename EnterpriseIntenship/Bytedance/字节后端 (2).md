# 字节后端-基础架构

4月11日, 春招第五场笔试,

第二题动态规划.

动态库和静态库

三道[算法题](zi-jie-hou-duan-ji-chu-jia-gou.md)，感觉并不难，但是本人不怎么[刷题](zi-jie-hou-duan-ji-chu-jia-gou.md)。

1. [进制转换](zi-jie-hou-duan-ji-chu-jia-gou.md)
2. 交叉[链表](zi-jie-hou-duan-ji-chu-jia-gou.md)（面试完才知道是经典题目）
3. 给40亿个正数，判断以下数是否在其中

题三的暴力解法占多少内存？

给40亿个正数，判断以下数是否在其中 题三的暴力解法占多少内存？ 一亿 10^8 4 _10^9 0.4_2^30 一个int 是4个字节, 4bytes\* 0.4\*2^30 =8GB 3.2GB

vector、list、map的底层实现和解释

vector 扩容的过程

Tcp 断开链接的过程

进程和线程的区别

用shell实现：计算某一文件里”stream”出现的次数

`grep -o stream hello.cpp | wc -l`

[项目](zi-jie-hou-duan-ji-chu-jia-gou.md)相关

数据库索引延伸问了数据库有哪些索引结构，查询速度如何（写了几个模糊查询语句问的

写代码：

1.  写一个函数实现[进制转换](zi-jie-hou-duan-ji-chu-jia-gou.md)的功能

    输入一个十进制的整形数，将其转换成 N 进制数(1\<N<=16)

这一位= x%n , x = x/n. 直到x为0 ,然后 逆序输出.

1. 如何判断两个[链表](zi-jie-hou-duan-ji-chu-jia-gou.md)相交 : a开始, b开始, a到了,把a放在b的开头, b到了,把b放在a的开头, 两个互换后相遇的地方就是交点.
2. 40亿数集合，查几个数是否在集合内（说[算法](zi-jie-hou-duan-ji-chu-jia-gou.md)并求所需空间）

STL容器区别用法

list是单向[链表](zi-jie-hou-duan-ji-chu-jia-gou.md)还是双向[链表](zi-jie-hou-duan-ji-chu-jia-gou.md)

反问

### 二面（25min）：

二面前找了很多之前[牛客](zi-jie-hou-duan-ji-chu-jia-gou.md)的[面经](zi-jie-hou-duan-ji-chu-jia-gou.md)，发现基础架构会出一些比较底层的代码题，着重看了看

[项目](zi-jie-hou-duan-ji-chu-jia-gou.md)相关（这次问系统比较多）

数据库模糊查询怎么做

面试官：好，下面我们来写两道题

1. 旋转矩阵

（面试官：给你5-10min）

这题就是 tmp存,然后四个转. 列是 到(n+1)/2 就是奇数就是一个长方形 ,行是到 n/2

1. 面试官：有没有[刷题](zi-jie-hou-duan-ji-chu-jia-gou.md)，刷过堆[排序](zi-jie-hou-duan-ji-chu-jia-gou.md)吗？（我：没有）面试官：那更好

堆[排序](zi-jie-hou-duan-ji-chu-jia-gou.md)的heap\_insert函数

回忆着ads课上内容写的，记忆还比较清晰。

最后问了个删除堆顶的操作思路.

在堆排序中，要排序的数据首先存储在一个堆中。从堆中一次取出一个节点，放置到有序数据集的尾部。当取出每个节点时，它的下一个节点就会浮现到堆的顶部。堆排序和快速排序有相同的时间复杂度，但在实际中，快速排序往往比堆排序复杂度略低，两者相差一个常量因子。

```
//在start 和end区间内，如果父节点小于子节点，就交换
//其实就是persudo down
void max_heapify(int arr[], int start, int end)
{
	//建立父节点指标和子节点指标
	int dad = start;
	int son = dad * 2 + 1;//左子节点
	while (son <= end)  //若子节点指标在范围内才做比较
	{
		if (son + 1 <= end && arr[son] < arr[son + 1]) //先比较两个子节点大小，选择更大的
			son++;
		if (arr[dad] > arr[son]) //如果父节点大于子节点代表调整完毕，直接跳出函数
			return;
		else  //否则交换父子内容再继续子节点和孙节点比较
		{
			swap(arr[dad], arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void heap_sort(int arr[], int len)
{
	//初始化，i从最后一个父节点开始调整
	//堆数组的前一半为父节点，后一半为子节点
	for (int i = len / 2 - 1; i >= 0; i--)
		max_heapify(arr, i, len - 1);
	//先将第一个元素和已经排好的元素前一位做交换，再调整(刚调整的元素之前的元素)，直到排序完毕
	for (int i = len - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);// 把最大值和最后交换
		max_heapify(arr, 0, i - 1);//调整堆。
	}
```

### 三面（30min）：

也是面试前查了很多[面经](zi-jie-hou-duan-ji-chu-jia-gou.md)，发现三面主要看面试官，所以着重看了下底层[算法](zi-jie-hou-duan-ji-chu-jia-gou.md)和我的[项目](zi-jie-hou-duan-ji-chu-jia-gou.md)

首先问了问实习时间，未来规划（就业or读研）

细挖[项目](zi-jie-hou-duan-ji-chu-jia-gou.md)（系统那个，我写上去的几个技术都仔细问过了。）

面试官看了看我之前的代码题，可能觉得没有什么其他想要我写的就没有写代码

然后聊了下意愿方向，一定要我选一个

总的来说感觉基础架构这块要看[项目](zi-jie-hou-duan-ji-chu-jia-gou.md)契合度（一面面试官让我自我介绍时明确要说和部门相关的）

写代码的话比较偏向于底层数据结构的实现，可能[剑指offer](zi-jie-hou-duan-ji-chu-jia-gou.md)比lc刷起来更有效
