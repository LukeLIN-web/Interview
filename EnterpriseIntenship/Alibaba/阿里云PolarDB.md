

如果让你实现一个mutex你要怎么设计呢？

调用Lock请求锁的时候，通过xadd方法进行CAS操作，xadd方法通过循环执行CAS操作直到成功，保证对key+1的操作成功完成。如果锁没有被其他的goroutine持有，那么Lock方法成功地将key设置1，这个goroutine就持有了这个锁，如果锁被其他goroutine持有了，当前的gorouine会把key+1，而且还会调用semacquire方法，使用信号量将自己休眠，等待锁释放的时候，信号量会将它唤醒。

#### 为什么多线程下载能加速？

 congestion control 的算法是 **per connection** 的 .  最终算法的目的是 connection-wise fairness ——在不出现拥塞的前提下，让每个 connection 都能大致得到同样的、最大的带宽。所以，如果你开多个连接，你就能”抢占“到更多的带宽

AWS的Aurora或者阿里云的PolarDB就是把MySQL、PostgreSQL等单机数据库部署到一个由EBS磁盘或者RDMA高速网络连接的分布式文件系统上，实现100%的SQL兼容。

![](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/47c28441babd4880a08c286c788fc105~tplv-k3u1fbpfcp-watermark.awebp)

**但是这种架构也有明显的缺点：**

**运维更为复杂：**除了关注 MySQL 本身，还需要运维数据实时同步流，SQL代理层，镜像索引这些系统。

**数据实时同步容易出现故障或者延迟：**客户可能感知到明显的不一致，从镜像索引查询到的数据跟从MySQL查询有差异。为了降低这种差异的影响，SQL代理层还需要设计一定的降级能力（发现延迟时尽可能切换到MySQL查询）。还需要有快速修正镜像索引数据的设施。

**资源冗余浪费：**镜像索引实际是数据的复制， MySQL为扛住读性能和同步需求需要大量的从库。

PolarDB最高可达100TB，性能是MySQL的6倍。

**技术的条件：**

1、分布式系统需要有效的通信框架，百度的brpc框架当时已经非常成熟，是工业级的RPC实现，有超大规模的应用。

2、保障数据一致性当时主流的方案就是Paxos和Raft，百度braft框架是基于brpc的Raft协议实现，发展也很迅速，有内部支持。

3、单机存储节点需要一个可靠的KV存储，Facebook&Google联合出品的RocksDB是基于LSM-Tree的高性能KV引擎，CockroachDB和TiDB都选择了RocksDB。

