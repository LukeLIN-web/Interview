

8月31日

业务运维基础架构部

发送了, 用户不在, 会记录吗?

几万个连接.
性能优化.

他这个就是运维一些效率工具.

怎么解决一些不小心的命令操作?

给用户设置权限吧，规定用户能做的操作.好像没有这种操作，顶多看一下history，看你执行了哪些操作

在Linux中用户要与kernel交互，必须通过一个shell的程序。Linux命令的执行必须依赖于Shell命令解释器。Shell实际上是在Linux系统中运行的一种特殊程序，它位于操作系统内核与用户之间，负责接受用户输入的命令并进行解释，将需要执行的操作传递给系统内核执行，Shell在用户和内核之间充当了一个“翻译官”的角色。当用户登陆到Linux系统时，会自动加载一个Shell程序，以便给用户提供可以输入命令的操作环境。

只要Shell解释器被运行，内部指令也就自动载入内存并驻留在系统内存中，用户可以直接使用。内部命令无需从硬盘中重新读取文件，而且解析内部命令shell不需要创建子进程，因此执行效率更高。常见的builtin命令有： cd, echo, history 等。

二进制可执行文件，需要由磁盘装入内存执行。会派生新的进程，shell解释程序会调用fork自身的一个拷贝，然后用exec系列函数来执行外部命令，然后外部命令就取代了先前fork的子shell。

 Mysql insert update replace的区别

grep,  crontab 命令

怎么看端口  netstat

ping 是基于 `ICMP` 协议工作的，所以要明白 ping 的工作，首先我们先来熟悉 **ICMP 协议**。

OSI七层

TCP和UDP的区别

udp 不稳定, 怎么办? 怎么让他可靠? 

TCP的TIME_WAIT状态

hash 算法有哪些?  除余, 乘余取整法,平方取中法,数字分析法,基数转换法,折叠法

md5 的原理, ·MD5（Message Digest Algorithm5）。MD5是输入不定长度信息，输出固定长度128bits的算法。经过程序流程，生成4个32位数据，最后联合起来成为一个128bits哈希。基本方式为求余、取余、调整长度、与链接变量进行循环运算，得出结果。MD5算法曾被广泛使用，然而目前该算法已被证明是一种不安全的算法。王晓云教授已经于2004年破解了MD5算法。

操作系统——系统调用

为什么要有系统调用. 

fopen与open的区别（好文

cpp 虚函数. 



进程最大地址空间