## 二 Executor 框架

### 2.1 简介

`Executor` 框架是 Java5 之后引进的，在 Java 5 之后，通过 `Executor` 来启动线程比使用 `Thread` 的 `start` 方法更好，除了更易管理，效率更好（用线程池实现，节约开销）外，还有关键的一点：有助于避免 this 逃逸问题。

> 补充：this 逃逸是指在构造函数返回之前其他线程就持有该对象的引用. 调用尚未构造完全的对象的方法可能引发令人疑惑的错误。

`Executor` 框架不仅包括了线程池的管理，还提供了线程工厂、队列以及拒绝策略等，`Executor` 框架让并发编程变得更加简单。

### 2.2 Executor 框架结构(主要由三大部分组成)

#### 1) 任务(`Runnable` /`Callable`)

执行任务需要实现的 **`Runnable` 接口** 或 **`Callable`接口**。**`Runnable` 接口**或 **`Callable` 接口** 实现类都可以被 **`ThreadPoolExecutor`** 或 **`ScheduledThreadPoolExecutor`** 执行。

#### 2) 任务的执行(`Executor`)

如下图所示，包括任务执行机制的核心接口 **`Executor`** ，以及继承自 `Executor` 接口的 **`ExecutorService` 接口。`ThreadPoolExecutor`** 和 **`ScheduledThreadPoolExecutor`** 这两个关键类实现了 **ExecutorService 接口**。

**这里提了很多底层的类关系，但是，实际上我们需要更多关注的是 `ThreadPoolExecutor` 这个类，这个类在我们实际使用线程池的过程中，使用频率还是非常高的。**

> **注意：**  `ScheduledThreadPoolExecutor` 源代码我们发现 `ScheduledThreadPoolExecutor` 实际上是继承了 `ThreadPoolExecutor` 并实现了 ScheduledExecutorService ，而 `ScheduledExecutorService` 又实现了 `ExecutorService`，正如我们下面给出的类关系图显示的一样。

**`ThreadPoolExecutor` 类描述:**

```java
//AbstractExecutorService实现了ExecutorService接口
public class ThreadPoolExecutor extends AbstractExecutorService
```

## 三 (重要)ThreadPoolExecutor 类简单介绍

**线程池实现类 `ThreadPoolExecutor` 是 `Executor` 框架最核心的类。**

### 线程池

线程池是一种线程的使用模式。创建若干个可执行的线程放入一个池（容器）中，有任务需要处理时，会提交到线程池中的任务队列，处理完之后线程并不会被销毁，而是仍然在线程池中等待下一个任务。

#### 线程池的好处

在开发过程中，合理地使用线程池可以带来 3 个好处。

降低资源消耗。重复利用线程池中已经创建的线程，可以避免频繁地创建和销毁线程，从而减少资源消耗。

提高响应速度。由于线程池中有已经创建的线程，因此当任务到达时，可以直接执行，不需要等待线程创建。

提高线程的可管理性。线程是稀缺资源，如果无限制地创建，不仅会消耗系统资源，还会降低系统的稳定性，使用线程池可以进行统一分配、调优和监控。

#### 线程池的创建

可以通过 ThreadPoolExecutor 类创建线程池。ThreadPoolExecutor 类有 4 个构造方法，其中最一般化的构造方法包含 7 个参数。

corePoolSize：核心线程数，定义了最少可以同时运行的线程数量，当有新的任务时就会创建一个线程执行任务，当线程池中的线程数量达到 corePoolSize 之后，到达的任务进入阻塞队列。

maximumPoolSize：最大线程数，定义了线程池中最多能创建的线程数量。

keepAliveTime：等待时间，当线程池中的线程数量大于 corePoolSize 时，如果一个线程的空闲时间达到 keepAliveTime 时则会终止，直到线程池中的线程数不超过 corePoolSize。

unit：参数 keepAliveTime 的单位。

workQueue：阻塞队列，用来存储等待执行的任务。

threadFactory：创建线程的工厂。

handler：当拒绝处理任务时的策略。

#### 向线程池提交任务

可以通过方法 execute 向线程池提交任务。该方法被调用时，线程池会做如下操作。

如果正在运行的线程数量小于 corePoolSize，则创建核心线程运行这个任务。

如果正在运行的线程数量大于或等于 corePoolSize，则将这个任务放入阻塞队列。

如果阻塞队列满了，而且正在运行的线程数量小于 maximumPoolSize，则创建非核心线程运行这个任务。

如果阻塞队列满了，而且正在运行的线程数量大于或等于 maximumPoolSize，则线程池抛出 RejectExecutionException 异常。

上述操作中提到了两个概念，「核心线程」和「非核心线程」。核心线程和非核心线程的最大数目在创建线程池时被指定。核心线程和非核心线程的区别如下。

向线程池提交任务时，首先创建核心线程运行任务，直到核心线程数到达上限，然后将任务放入阻塞队列。

只有在核心线程数到达上限，且阻塞队列满的情况下，才会创建非核心线程运行任务。

### 3.1 ThreadPoolExecutor 类分析

`ThreadPoolExecutor` 类中提供的四个构造方法。我们来看最长的那个，其余三个都是在这个构造方法的基础上产生（其他几个构造方法说白点都是给定某些默认参数的构造方法比如默认制定拒绝策略是什么）。

```
    /**
     * 用给定的初始参数创建一个新的ThreadPoolExecutor。
     */
    public ThreadPoolExecutor(int corePoolSize,//线程池的核心线程数量
                              int maximumPoolSize,//线程池的最大线程数
                              long keepAliveTime,//当线程数大于核心线程数时，多余的空闲线程存活的最长时间
                              TimeUnit unit,//时间单位
                              BlockingQueue<Runnable> workQueue,//任务队列，用来储存等待执行任务的队列
                              ThreadFactory threadFactory,//线程工厂，用来创建线程，一般默认即可
                              RejectedExecutionHandler handler//拒绝策略，当提交的任务过多而不能及时处理时，我们可以定制策略来处理任务
                               ) {
        if (corePoolSize < 0 ||
            maximumPoolSize <= 0 ||
            maximumPoolSize < corePoolSize ||
            keepAliveTime < 0)
            throw new IllegalArgumentException();
        if (workQueue == null || threadFactory == null || handler == null)
            throw new NullPointerException();
        this.corePoolSize = corePoolSize;
        this.maximumPoolSize = maximumPoolSize;
        this.workQueue = workQueue;
        this.keepAliveTime = unit.toNanos(keepAliveTime);
        this.threadFactory = threadFactory;
        this.handler = handler;
    }
```

下面这些对创建非常重要，在后面使用线程池的过程中你一定会用到！所以，务必拿着小本本记清楚。

**`ThreadPoolExecutor` 3 个最重要的参数：**

- **`corePoolSize` :** 核心线程数线程数定义了最小可以同时运行的线程数量。
- **`maximumPoolSize` :** 当队列中存放的任务达到队列容量的时候，当前可以同时运行的线程数量变为最大线程数。
- **`workQueue`:** 当新任务来的时候会先判断当前运行的线程数量是否达到核心线程数，如果达到的话，新任务就会被存放在队列中。

`ThreadPoolExecutor`其他常见参数 :

1. **`keepAliveTime`**:当线程池中的线程数量大于 `corePoolSize` 的时候，如果这时没有新的任务提交，核心线程外的线程不会立即销毁，而是会等待，直到等待的时间超过了 `keepAliveTime`才会被回收销毁；
2. **`unit`** : `keepAliveTime` 参数的时间单位。
3. **`threadFactory`** :executor 创建新线程的时候会用到。
4. **`handler`** :饱和策略。关于饱和策略下面单独介绍一下。

下面这张图可以加深你对线程池中各个参数的相互关系的理解（图片来源：《Java 性能调优实战》）：

![](https://github.com/Snailclimb/JavaGuide/raw/main/docs/java/concurrent/images/java-thread-pool-summary/%E7%BA%BF%E7%A8%8B%E6%B1%A0%E5%90%84%E4%B8%AA%E5%8F%82%E6%95%B0%E4%B9%8B%E9%97%B4%E7%9A%84%E5%85%B3%E7%B3%BB.png)

![](https://camo.githubusercontent.com/5bfca62306da35f93fe15082a3de891dc6932181d7187415c31d663b8b679b36/68747470733a2f2f67756964652d626c6f672d696d616765732e6f73732d636e2d7368656e7a68656e2e616c6979756e63732e636f6d2f6a61766167756964652f2545352539422542452545382541372541332545372542412542462545372541382538422545362542312541302545352541452539452545372538452542302545352538452539462545372539302538362e706e67)

有一个简单并且适用面比较广的公式：

- **CPU 密集型任务(N+1)：** 这种任务消耗的主要是 CPU 资源，可以将线程数设置为 N（CPU 核心数）+1，比 CPU 核心数多出来的一个线程是为了防止线程偶发的缺页中断，或者其它原因导致的任务暂停而带来的影响。一旦任务暂停，CPU 就会处于空闲状态，而在这种情况下多出来的一个线程就可以充分利用 CPU 的空闲时间。
- **I/O 密集型任务(2N)：** 这种任务应用起来，系统会用大部分的时间来处理 I/O 交互，而线程在处理 I/O 的时间段内不会占用 CPU 来处理，这时就可以将 CPU 交出给其它线程使用。因此在 I/O 密集型任务的应用中，我们可以多配置一些线程，具体的计算方法是 2N。

**如何判断是 CPU 密集任务还是 IO 密集任务？**

CPU 密集型简单理解就是利用 CPU 计算能力的任务比如你在内存中对大量数据进行排序。但凡涉及到网络读取，文件读取这类都是 IO 密集型，这类任务的特点是 CPU 计算耗费时间相比于等待 IO 操作完成的时间来说很少，大部分时间都花在了等待 IO 操作完成上。

## 实践

### 1. 使用 `ThreadPoolExecutor `的构造函数声明线程池

**1. 线程池必须手动通过 `ThreadPoolExecutor `的构造函数来声明，避免使用`Executors `类的 `newFixedThreadPool` 和 `newCachedThreadPool` ，因为可能会有 OOM 的风险。**

> Executors 返回线程池对象的弊端如下：
>
> - **`FixedThreadPool` 和 `SingleThreadExecutor`** ： 允许请求的队列长度为 `Integer.MAX_VALUE`,可能堆积大量的请求，从而导致 OOM。
> - **CachedThreadPool 和 ScheduledThreadPool** ： 允许创建的线程数量为 `Integer.MAX_VALUE` ，可能会创建大量线程，从而导致 OOM。

说白了就是：**使用有界队列，控制线程创建数量。**

除了避免 OOM 的原因之外，不推荐使用 `Executors `提供的两种快捷的线程池的原因还有：

1. 实际使用中需要根据机器的性能、业务场景来手动配置线程池的参数比如核心线程数、使用的任务队列、饱和策略等等。
2. 应该给线程池命名，这样有助于我们定位问题。

### 2.监测线程池运行状态

你可以通过一些手段来检测线程池的运行状态比如 SpringBoot 中的 Actuator 组件。

除此之外，我们还可以利用 `ThreadPoolExecutor` 的相关 API做一个简陋的监控。从下图可以看出， `ThreadPoolExecutor`提供了获取线程池当前的线程数和活跃线程数、已经执行完成的任务数、正在排队中的任务数等等。

### 3.建议不同类别的业务用不同的线程池

很多人在实际项目中都会有类似这样的问题：**我的项目中多个业务需要用到线程池，是为每个线程池都定义一个还是说定义一个公共的线程池呢？**

一般建议是不同的业务使用不同的线程池，配置线程池的时候根据当前业务的情况对当前线程池进行配置，因为不同的业务的并发以及对资源的使用情况都不同，重心优化系统性能瓶颈相关的业务。

# JUC

一文读懂 CAS
把 CAS 放在整个并发系列的这个位置，主要原因就是接下来我们将要学习到的 J.U.C 并发包中的很多类都涉及到了 CAS，可以说没有 CAS 和 volatile 就没有 J.U.C 并发包。

乐观锁和悲观锁回顾
提到 CAS 就不得不说一嘴乐观锁和悲观锁，之前的文章【Java 并发中的各种 ”锁“ 事】中我们已经讲过，这里简单回顾下。

悲观锁是一种悲观思想，认为自己在使用数据的时候一定有别的线程来修改数据，因此在获取数据的时候会先加锁，确保数据不会被别的线程修改。

synchronized 关键字和 Lock 接口的实现类就是悲观锁。

乐观锁是一种乐观思想，认为自己在使用数据时不会有别的线程修改数据，所以不会添加锁，只是在提交修改的时候去判断一下，在此之前有没有其他的线程也修改了这个数据：

如果其他的线程还没有提交修改，那么当前线程就将自己修改的数据成功写入；
如果其他的线程已经提交了修改，则当前线程会根据不同的实现方式执行不同的操作（例如报错或者自动重试）。
换句话说，乐观锁的目的就是在不使用锁（悲观锁）的情况下保证线程安全。

乐观锁在 Java 中是采用 CAS 算法实现的，J.U.C 包中的原子类就是通过 CAS 算法来实现了乐观锁，关于原子类下篇文章会详细解释。

使用这种 CAS 算法的代码也常被称为 无锁 编程（Lock-Free）。

#### 什么是 CAS

再强调一遍， CAS 是一种算法，不要把 CAS 和乐观锁直接画等号。事实上，现代处理器基本都已经内置了实现 CAS 的指令，比如 x86 指令集上的 CAMPXCHG。

首先，大家应该已经知道，JMM 中不仅有主内存，每个线程还有各自的本地内存。每个线程会先更新自己的本地内存，然后再同步更新到主内存。

那如果多个线程都想要同步更新到主内存怎么办呢？

CAS 就是用来保证这种情况下的线程安全的。当多个线程尝试使用 CAS 同时更新主内存中的同一个变量时，只有一个线程可以成功更新变量的值，其他的线程都会失败，失败的线程并不会挂起，而是会自旋重试。

具体来说，CAS（Compare And Set）：比较并替换
首先线程先读取需要读写的某个变量的值，然后比较当前该变量的值和该变量原来应该有的值：

如果当前该变量的值与原来应该有的值相匹配，那么这个线程就可以将该变量更新为新值
如果当前该变量的值与原来应该有的值不匹配，那就更新失败，开始自旋重试。
CAS 存在的三大问题
看起来 CAS 好像很不错，高效地解决了并发问题，但事实上，CAS 仍然存在三大问题：

ABA 问题
循环时间长开销大
只能保证一个共享变量的原子操作

#### Lock 接口底层：AQS 概述

事实上，Lock 接口的实现基本都是通过聚合了一个队列同步器（AbstractQueuedSynchronizer，AQS）的子类来完成线程访问控制的。比如 ReentrantLock：

AQS 将一些方法开放给子类进行重写，进而 AQS 提供的模板方法就会调用这些被子类重写的方法。

AQS 是一个抽象类，是用来构建锁或者其他同步组件的基础框架，它使用了一个 volaitle 修饰的 int 成员变量 state 表示同步状态，通过内置的 FIFO 双向队列（源码注释上写的 CLH（Craig，Landin，and Hagersten） 队列（三个人名的简称），其实就是一个先进先出的双向队列）来完成线程们获取资源的时候的排队工作。

具体来说，如果某个线程请求锁（共享资源）失败，则该线程就会被加入到 CLH 队列的末端。当持有锁的线程释放锁之后，会唤醒其后继节点，这个后继节点就可以开始尝试获取锁。

JDK 提供的这些容器大部分在 `java.util.concurrent` 包中。

- **`ConcurrentHashMap`** : 线程安全的 `HashMap`
- **`CopyOnWriteArrayList`** : 线程安全的 `List`，在读多写少的场合性能非常好，远远好于 `Vector`。
- **`ConcurrentLinkedQueue`** : 高效的并发队列，使用链表实现。可以看做一个线程安全的 `LinkedList`，这是一个非阻塞队列。
- **`BlockingQueue`** : 这是一个接口，JDK 内部通过链表、数组等方式实现了这个接口。表示阻塞队列，非常适合用于作为数据共享的通道。
- **`ConcurrentSkipListMap`** : 跳表的实现。这是一个 Map，使用跳表的数据结构进行快速查找。

## ConcurrentHashMap

我们知道 `HashMap` 不是线程安全的，在并发场景下如果要保证一种可行的方式是使用 `Collections.synchronizedMap()` 方法来包装我们的 `HashMap`。但这是通过使用一个全局的锁来同步不同线程间的并发访问，因此会带来不可忽视的性能问题。

所以就有了 `HashMap` 的线程安全版本—— `ConcurrentHashMap` 的诞生。

在 `ConcurrentHashMap` 中，无论是读操作还是写操作都能保证很高的性能：在进行读操作时(几乎)不需要加锁，而在写操作时通过锁分段技术只对所操作的段加锁而不影响客户端对其它段的访问。

那既然没有使用分段锁，如何保证并发安全性的呢？

synchronized + CAS！

简单来说，Node 数组其实就是一个哈希桶数组，每个 Node 头节点及其所有的 next 节点组成的链表就是一个桶，只要锁住这个桶的头结点，就不会影响其他哈希桶数组元素的读写。桶级别的粒度显然比 1.7 版本的 Segment 段要细。

## CopyOnWriteArrayList

### CopyOnWriteArrayList 简介

```
public class CopyOnWriteArrayList<E>
extends Object
implements List<E>, RandomAccess, Cloneable, Serializable
```

在很多应用场景中，读操作可能会远远大于写操作。由于读操作根本不会修改原有的数据，因此对于每次读取都进行加锁其实是一种资源浪费。我们应该允许多个线程同时访问 `List` 的内部数据，毕竟读取操作是安全的。

如果你想要对一块内存进行修改时，我们不在原有内存块中进行写操作，而是将内存拷贝一份，在新的内存中进行写操作，写完之后呢，就将指向原来内存指针指向新的内存，原来的内存就可以被回收掉了。

`CopyOnWriteArrayList` 写入操作 `add()`方法在添加集合的时候加了锁，保证了同步，避免了多线程写的时候会 copy 出多个副本出来。

读线程会先读一次旧的, 再读一次新的. 

## ConcurrentLinkedQueue

Java 提供的线程安全的 `Queue` 可以分为**阻塞队列**和**非阻塞队列**，其中阻塞队列的典型例子是 `BlockingQueue`，非阻塞队列的典型例子是 `ConcurrentLinkedQueue`，在实际应用中要根据实际需要选用阻塞队列或者非阻塞队列。 **阻塞队列可以通过加锁来实现，非阻塞队列可以通过 CAS 操作实现。**

`ConcurrentLinkedQueue` 应该算是在高并发环境中性能最好的队列了。它之所有能有很好的性能，是因为其内部复杂的实现。  主要使用 CAS 非阻塞算法来实现线程安全。

`ConcurrentLinkedQueue` 适合在对性能要求相对较高，同时对队列的读写存在多个线程同时进行的场景，即如果对队列加锁的成本较高则适合使用无锁的 `ConcurrentLinkedQueue` 来替代。

### BlockingQueue 简介

上面我们己经提到了 `ConcurrentLinkedQueue` 作为高性能的非阻塞队列。下面我们要讲到的是阻塞队列——`BlockingQueue`。阻塞队列（`BlockingQueue`）被广泛使用在“生产者-消费者”问题中，其原因是 `BlockingQueue` 提供了可阻塞的插入和移除的方法。当队列容器已满，生产者线程会被阻塞，直到队列未满；当队列容器为空时，消费者线程会被阻塞，直至队列非空时为止。

下面主要介绍一下 3 个常见的 `BlockingQueue` 的实现类：`ArrayBlockingQueue`、`LinkedBlockingQueue` 、`PriorityBlockingQueue` 。

如果你的应用需要有序性，那么跳表就是你不二的选择。JDK 中实现这一数据结构的类是 `ConcurrentSkipListMap`。
