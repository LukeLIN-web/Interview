

#### 一面

**C++**

1）说下智能指针？（说了unique ptr和shared ptr）

1. shared_ptr
2. unique_ptr
3. weak_ptr
4. auto_ptr（被 C++11 弃用）

- Class shared_ptr 实现共享式拥有（shared ownership）概念。多个智能指针指向相同对象，该对象和其相关资源会在 “最后一个 reference 被销毁” 时被释放。
- Class unique_ptr 实现独占式拥有（exclusive ownership）或严格拥有（strict ownership）概念，保证同一时间内只有一个智能指针可以指向该对象。你可以移交拥有权。它对于避免内存泄漏（resource leak）——如 new 后忘记 delete ——特别有用。

##### shared_ptr

多个智能指针可以共享同一个对象，对象的最末一个有责任销毁对象，并清理与该对象相关的所有资源。

- 支持定制型删除器（custom deleter），可防范 Cross-DLL 问题（对象在动态链接库（DLL）中被 new 创建，却在另一个 DLL 内被 delete 销毁）、自动解除互斥锁

##### weak_ptr

weak_ptr 允许你共享但不拥有某对象，一旦最末一个拥有该对象的智能指针失去了所有权，任何 weak_ptr 都会自动成空（empty）。因此，在 default 和 copy 构造函数之外，weak_ptr 只提供 “接受一个 shared_ptr” 的构造函数。weak_ptr是shared_ptr的"观察者"，它与一个shared_ptr绑定，但却不参与引用计数的计算，在需要时，它还能摇身一变，生成一个与它所"观察"的shared_ptr共享引用计数器的新shared_ptr。

- 可打破环状引用（cycles of references，两个其实已经没有被使用的对象彼此互指，使之看似还在 “被使用” 的状态）的问题

##### unique_ptr

unique_ptr 是 C++11 才开始提供的类型，是一种在异常时可以帮助避免资源泄漏的智能指针。采用独占式拥有，意味着可以确保一个对象和其相应的资源同一时间只被一个 pointer 拥有。一旦拥有着被销毁或编程 empty，或开始拥有另一个对象，先前拥有的那个对象就会被销毁，其任何相应资源亦会被释放。

- unique_ptr 用于取代 auto_ptr

2）shared_ptr的计数器什么时候清零？（释放对象时计数器减一）追问：什么情况下释放对象（不会）

C++11的标准库提供了两种解决问题的思路：1、不允许多个对象管理一个指针（unique_ptr）；2、允许多个对象管理同一个指针，但仅当管理这个指针的最后一个对象析构时才调用delete（shared_ptr）。这两个思路的共同点是：只！允！许！delete一次！

重载 new 或者改构造函数，打日志，然后启动程序跑一个完整流程，然后写脚本分析日志。具体地说，你每次分配内存的时候都能得到一个地址，delete 的时候自然也能记录到被 delete 的地址，如果 log 里面出现了 new/delete 不成对的地址，那显然是有问题的。怎么通过这个地址找到代码，办法很多，基本上只要能确定泄露对象的 size，就能猜个八九不离十了。

**操作系统**

1）如果一台电脑只有2GB，进程能访问的空间会不会大于2GB（会，虚拟内存）

2）虚拟内存放在哪里（磁盘）

3）讲下进程访问页面过程（TLB -> 页表 -> 主存，如果主存没有就去磁盘调页，如果主存满了就用替换策略）

4）如果一个进程以遍历的方式访问全部内存，这会对所有其他进程造成影响，如何解决？（标答是让那些只被访问一次的页面不进入LRU，就不会被频繁替换）

删除一个链表中为指定值的结点，并返回链表，要求自己设计链表。

上来先写一个LRU

list , 来实现, 迭代器,  * 就可以解耦. begin是第一个, end -- 是最后一个. 

虚拟内存是怎么实现的? 

我们在开启分页前，要先把页表准备好，这个页表也就是内核态的页表。为了方便内核寻址，我们往往选择固定偏移量的va -> pa映射，举个例子来说，我们可以把虚拟地址3GB-4GB的这部分全部固定映射到0-1GB的实际物理内存（当然实际不一定要这么大）

不管是页目录项还是页表项中存的都是物理地址噢

由于地址访问往往是连续的，因此这种映射有个专门的单元来管理缓存，就是tlb了，所以说切换进程往往要刷新tlb，因为这个映射往往只对当前进程有效（内核态另说）。

内核态共享页表吗? 

不共享,  每个进程的页表都是由OS来管理的, 在Linux操作系统里面，所有进程在内核态空间里，va <-> pa的对应空间是相同的

切换进程要更换页表吗?

要更换

陷入内核态要更换页表吗? 系统调用要切换页表吗? 

不用更换页表. 

mmap和文件io 效率?

面试官说他做过实验,是差不多的, 都需要缺页中断. 





#### 流数据内核

为什么需要流处理系统，因为有低延时的应用需求：如实时数据分析，如性能指标，error 指标

1) 易用性：程序员如何声明流处理的逻辑，SQL 语言（或者类 SQL 语言）支持是否已经足够；还是要支持 general purpose 的处理逻辑，比如可以让程序员用 C++或者 Java 语言来实现处理逻辑然后交给系统执行（类似于 map-reduce）。从声明，测试到发布，整个生命周期需要多长时间？

2）性能：性能一般指延迟和吞吐量（throughput）需求。延迟是毫秒级别，秒级别，或者是分钟级别？吞吐量需要多高？

3）健壮性（fault-tolerance）：系统能够支持什么级别的崩溃恢复？对于数据处理，能提供什么样的 service level agreement ,是至少一次，至多一次，还是保证一次？如果某个 task 崩溃了，如何恢复 in-memory 的状态，等等。

4）扩展性（scalability）：数据处理是否能被 shard 或者 reshard 来提高吞吐量？系统是否能动态地伸缩（elasticity）。

5）正确性：是否提供类似数据库的 ACID 保证？是否会有数据丢失（这点和上面的健壮性有重叠）。

Facebook 在设计流系统时的决策是基于这个前提：秒级别的延迟和几百 GB/s 吞吐量需求（a few seconds of latency with hundreds of GB/s throughput）。在这个前提下，不同的批处理过程可以通过一个 persistent 的 message bus 系统（Scribe，类似于 Kafka）相连来传输数据。异构数据传输和数据处理，能够使得整个系统更好地处理上述提到的这些属性。

