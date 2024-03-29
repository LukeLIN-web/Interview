CPP 基础知识

c++起手primer工具书，进阶到 effective c++就足够，然后补stl源码分析/effective stl，c++对象模型，就侯捷cpp不带泛型，再加上现代c++，最后可以补一手essential c++，c++ standard library，boost 之类的

程序员的自我修养，那本

服务器编程就得apue unp linux高性能服务端编程等balabala

工作的话补git，vim，valgrind，gdb，cmake/makefile，shell，python，lua，火焰图之类的



C++比起其他语言来说有什么优点缺点?

C++和Python的区别包括但不限于：

- Python是一种脚本语言，是解释执行的，而C++是编译语言，是需要编译后在特定平台运行的。python可以很方便的跨平台，但是效率没有C++高。
- Python使用缩进来区分不同的代码块，C++使用花括号来区分
- C++中需要事先定义变量的类型，而Python不需要，Python的基本数据类型只有数字，布尔值，字符串，列表，元组等等
- Python的库函数比C++的多，调用起来很方便

C++和C语言的区别

- C++中new和delete是对内存分配的运算符，取代了C中的malloc和free。
- 标准C++中的字符串类取代了标准C函数库头文件中的字符数组处理函数（C中没有字符串类型）。
- C++中用来做控制态输入输出的iostream类库替代了标准C中的stdio函数库。
- C++中的try/catch/throw异常处理机制取代了标准C中的setjmp()和longjmp()函数。
- 在C++中，允许有相同的函数名，不过它们的参数类型不能完全相同，这样这些函数就可以相互区别开来。而这在C语言中是不允许的。也就是C++可以重载，C语言不允许。
- C++语言中，允许变量定义语句在程序中的任何地方，只要在是使用它之前就可以；而C语言中，必须要在函数开头部分。而且C++不允许重复定义变量，C语言也是做不到这一点的
- 在C++中，除了值和指针之外，新增了引用。引用型变量是其他变量的一个别名，我们可以认为他们只是名字不相同，其他都是相同的。
- C++相对与C增加了一些关键字，如：bool、using、dynamic_cast、namespace等等

C++与Java的区别

**语言特性**

- Java语言给开发人员提供了更为简洁的语法；完全面向对象，由于JVM可以安装到任何的操作系统上，所以说它的可移植性强
- Java语言中没有指针的概念，引入了真正的数组。不同于C++中利用指针实现的“伪数组”，Java引入了真正的数组，同时将容易造成麻烦的指针从语言中去掉，这将有利于防止在C++程序中常见的因为数组操作越界等指针操作而对系统数据进行非法读写带来的不安全问题
- C++也可以在其他系统运行，但是需要不同的编码（这一点不如Java，只编写一次代码，到处运行），例如对一个数字，在windows下是大端存储，在unix中则为小端存储。Java程序一般都是生成字节码，在JVM里面运行得到结果
- Java用接口(Interface)技术取代C++程序中的抽象类。接口与抽象类有同样的功能，但是省却了在实现和维护上的复杂性

**垃圾回收**

- C++用析构函数回收垃圾，写C和C++程序时一定要注意内存的申请和释放
- Java语言不使用指针，内存的分配和回收都是自动进行的，程序员无须考虑内存碎片的问题

**应用场景**

- Java在桌面程序上不如C++实用，C++可以直接编译成exe文件，指针是c++的优势，可以直接对内存的操作，但同时具有危险性 。
- Java在Web 应用上具有C++ 无可比拟的优势，具有丰富多样的框架
- 对于底层程序的编程以及控制方面的编程，C++很灵活，因为有句柄的存在

你觉得C++的哪些特性或者哪些优点对你来说是最重要的。

STL的内存分配器

C++的内存分配管理机制

重载cout怎么做?

用到了osstream

C++11的一些新特性，移动语义，智能指针，内部类





### 内存管理

new / delete 与 malloc / free的异同

**相同点**

- 都可用于内存的动态申请和释放

**不同点**

- 前者是C++运算符，后者是C/C++语言标准库函数
- new自动计算要分配的空间大小，malloc需要手工计算
- new是类型安全的，malloc不是。例如：

```
int *p = new float[2]; //编译错误
int *p = (int*)malloc(2 * sizeof(double));//编译无错误
```

- new调用名为**operator new**的标准库函数分配足够空间并调用相关对象的构造函数，delete对指针所指对象运行适当的析构函数；然后通过调用名为**operator delete**的标准库函数释放该对象所用内存。后者均没有相关调用
- 后者需要库文件支持，前者不用
- new是封装了malloc，直接free不会报错，但是这只是释放内存，而不会析构对象

new和delete是如何实现的？

- new的实现过程是：首先调用名为**operator new**的标准库函数，分配足够大的原始为类型化的内存，以保存指定类型的一个对象；接下来运行该类型的一个构造函数，用指定初始化构造对象；最后返回指向新分配并构造后的的对象的指针
- delete的实现过程：对指针指向的对象运行适当的析构函数；然后通过调用名为**operator delete**的标准库函数释放该对象所用内存

#### malloc和new的区别？

- malloc和free是标准库函数，支持覆盖；new和delete是运算符，不重载。
- malloc仅仅分配内存空间，free仅仅回收空间，不具备调用构造函数和析构函数功能，用malloc分配空间存储类的对象存在风险；new和delete除了分配回收功能外，还会调用构造函数和析构函数。
- malloc和free返回的是void类型指针（必须进行类型转换），new和delete返回的是具体类型指针。

既然有了malloc/free，C++中为什么还需要new/delete呢？直接用malloc/free不好吗？

- malloc/free和new/delete都是用来申请内存和回收内存的。
- 在对非基本数据类型的对象使用的时候，对象创建的时候还需要执行构造函数，销毁的时候要执行析构函数。而malloc/free是库函数，是已经编译的代码，所以不能把构造函数和析构函数的功能强加给malloc/free，所以new/delete是必不可少的。

被free回收的内存是立即返还给操作系统吗？

不是的，被free回收的内存会首先被ptmalloc使用双链表保存起来，当用户下一次申请内存的时候，会尝试从这些内存中寻找合适的返回。这样就避免了频繁的系统调用，占用过多的系统资源。同时ptmalloc也会尝试对小块内存进行合并，避免过多的内存碎片。



## 基础进阶

### [const 那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/const)

const的实现机制是什么?

如果是函数内部定义的const，编译器来检查你有没有修改const。 编译器会报错。但是我们可以骗编译器. 是在函数的帧里的，程序拥有对这个存储区写的权限。

#### 1.const含义

常类型是指使用类型修饰符**const**说明的类型，常类型的变量或对象的值是不能被更新的。

#### 2.const作用

- 可以定义常量

```
const int a=100;
```

- 类型检查

  - const常量与`#define`宏定义常量的区别：

  > ~~**const常量具有类型，编译器可以进行安全检查；#define宏定义没有数据类型，只是简单的字符串替换，不能进行安全检查。**~~感谢两位大佬指出这里问题，见：[issue](https://github.com/Light-City/CPlusPlusThings/issues/5)

  - const定义的变量只有类型为整数或枚举，且以常量表达式初始化时才能作为常量表达式。
  - 其他情况下它只是一个 `const` 限定的变量，不要将与常量混淆。

- 防止修改，起保护作用，增加程序健壮性

```
void f(const int i){
    i++; //error!
}
```

- 可以节省空间，避免不必要的内存分配
  - const定义常量从汇编的角度来看，只是给出了对应的内存地址，而不是像`#define`一样给出的是立即数。
  - const定义的常量在程序运行过程中只有一份拷贝，而`#define`定义的常量在内存中有若干个拷贝。

#### 3.const对象默认为文件局部变量

注意：非const变量默认为extern。要使const变量能够在其他文件中访问，必须在文件中显式地指定它为extern。

> 未被const修饰的变量在不同文件的访问

```
// file1.cpp
int ext
// file2.cpp
#include<iostream>

extern int ext;
int main(){
    std::cout<<(ext+10)<<std::endl;
}
```

> const常量在不同文件的访问

```
//extern_file1.cpp
extern const int ext=12;
//extern_file2.cpp
#include<iostream>
extern const int ext;
int main(){
    std::cout<<ext<<std::endl;
}
```

> 小结：
> 可以发现未被const修饰的变量不需要extern显式声明！而const常量需要显式声明extern，并且需要做初始化！因为常量在定义后就不能被修改，所以定义时必须初始化。

#### 4.定义常量

```
const int b = 10;
b = 0; // error: assignment of read-only variable ‘b’
const string s = "helloworld";
const int i,j=0 // error: uninitialized const ‘i’
```

上述有两个错误：

- b 为常量，不可更改！
- i 为常量，必须进行初始化！(因为常量在定义后就不能被修改，所以定义时必须初始化。)

#### 5.指针与const

与指针相关的const有四种：

```
const char * a; //指向const对象的指针或者说指向常量的指针。
char const * a; //同上
char * const a; //指向类型对象的const指针。或者说常指针、const指针。
const char * const a; //指向const对象的const指针。
```

> **小结：**
> 如果*const*位于`*`的左侧，则const就是用来修饰指针所指向的变量，即指针指向为常量；
> 如果const位于`*`的右侧，*const*就是修饰指针本身，即指针本身是常量。

具体使用如下：

（1） **指向常量的指针**

```
const int *ptr;
*ptr = 10; //error
```

ptr是一个指向int类型const对象的指针，const定义的是int类型，也就是ptr所指向的对象类型，而不是ptr本身，所以ptr可以不用赋初始值。但是不能通过ptr去修改所指对象的值。

除此之外，也不能使用void`*`指针保存const对象的地址，必须使用const void`*`类型的指针保存const对象的地址。

```
const int p = 10;
const void * vp = &p;
void *vp = &p; //error
```

另外一个重点是：**允许把非const对象的地址赋给指向const对象的指针**。

将非const对象的地址赋给const对象的指针:

```
const int *ptr;
int val = 3;
ptr = &val; //ok
```

我们不能通过ptr指针来修改val的值，即使它指向的是非const对象!

我们不能使用指向const对象的指针修改基础对象，然而如果该指针指向了非const对象，可用其他方式修改其所指的对象。可以修改const指针所指向的值的，但是不能通过const对象指针来进行而已！如下修改：

```
int *ptr1 = &val;
*ptr1=4;
cout<<*ptr<<endl;
```

> 小结：
> 1.对于指向常量的指针，不能通过指针来修改对象的值。
> 2.不能使用void`*`指针保存const对象的地址，必须使用const void`*`类型的指针保存const对象的地址。
> 3.允许把非const对象的地址赋值给const对象的指针，如果要修改指针所指向的对象值，必须通过其他方式修改，不能直接通过当前指针直接修改。

（2） **常指针**

const指针必须进行初始化，且const指针的值不能修改。

```
#include<iostream>
using namespace std;
int main(){

    int num=0;
    int * const ptr=&num; //const指针必须初始化！且const指针的值不能修改
    int * t = &num;
    *t = 1;
    cout<<*ptr<<endl;
}
```

上述修改ptr指针所指向的值，可以通过非const指针来修改。

最后，当把一个const常量的地址赋值给ptr时候，由于ptr指向的是一个变量，而不是const常量，所以会报错，出现：const int`*` -> int `*`错误！

```
#include<iostream>
using namespace std;
int main(){
    const int num=0;
    int * const ptr=&num; //error! const int* -> int*
    cout<<*ptr<<endl;
}
```

上述若改为 const int `*`ptr或者改为const int `*`const ptr，都可以正常！

（3）**指向常量的常指针**

理解完前两种情况，下面这个情况就比较好理解了：

```
const int p = 3;
const int * const ptr = &p; 
```

ptr是一个const指针，然后指向了一个int 类型的const对象。

#### 6.函数中使用const

> const修饰函数返回值

这个跟const修饰普通变量以及指针的含义基本相同：

（1）**const int**

```
const int func1();
```

这个本身无意义，因为参数返回本身就是赋值给其他的变量！

（2）**const int***

```
const int* func2();
```

指针指向的内容不变。

（3）int *const

```
int *const func2();
```

指针本身不可变。

> const修饰函数参数

（1）传递过来的参数及指针本身在函数内不可变，无意义！

```
void func(const int var); // 传递过来的参数不可变
void func(int *const var); // 指针本身不可变
```

表明参数在函数体内不能被修改，但此处没有任何意义，var本身就是形参，在函数内不会改变。包括传入的形参是指针也是一样。

输入参数采用“值传递”，由于函数将自动产生临时变量用于复制该参数，该输入参数本来就无需保护，所以不要加const 修饰。

（2）**参数指针所指内容为常量不可变**

```
void StringCopy(char *dst, const char *src);
```

其中src 是输入参数，dst 是输出参数。给src加上const修饰后，如果函数体内的语句试图改动src的内容，编译器将指出错误。这就是加了const的作用之一。

（3）**参数为引用，为了增加效率同时防止修改。**

```
void func(const A &a)
```

对于非内部数据类型的参数而言，象void func(A a) 这样声明的函数注定效率比较低。因为函数体内将产生A 类型的临时对象用于复制参数a，而临时对象的构造、复制、析构过程都将消耗时间。

为了提高效率，可以将函数声明改为void func(A &a)，因为“引用传递”仅借用一下参数的别名而已，不需要产生临 时对象。

> 但是函数void func(A &a) 存在一个缺点：
>
> “引用传递”有可能改变参数a，这是我们不期望的。解决这个问题很容易，加const修饰即可，因此函数最终成为 void func(const A &a)。

以此类推，是否应将void func(int x) 改写为void func(const int &x)，以便提高效率？完全没有必要，因为内部数

据类型的参数不存在构造、析构的过程，而复制也非常快，“值传递”和“引用传递”的效率几乎相当。

> 小结：
> 1.对于非内部数据类型的输入参数，应该将“值传递”的方式改为“const 引用传递”，目的是提高效率。例如将void func(A a) 改为void func(const A &a)。
>
> 2.对于内部数据类型的输入参数，不要将“值传递”的方式改为“const 引用传递”。否则既达不到提高效率的目的，又降低了函数的可理解性。例如void func(int x) 不应该改为void func(const int &x)。

以上解决了两个面试问题：

- 如果函数需要传入一个指针，是否需要为该指针加上const，把const加在指针不同的位置有什么区别；
- 如果写的函数需要传入的参数是一个复杂类型的实例，传入值参数或者引用参数有什么区别，什么时候需要为传入的引用参数加上const。

#### 7.类中使用const

在一个类中，任何不会修改数据成员的函数都应该声明为const类型。如果在编写const成员函数时，不慎修改 数据成员，或者调用了其它非const成员函数，编译器将指出错误，这无疑会提高程序的健壮性。

使用const关键字进行说明的成员函数，称为常成员函数。只有常成员函数才有资格操作常量或常对象，没有使用const关键字进行说明的成员函数不能用来操作常对象。

对于类中的const成员变量必须通过初始化列表进行初始化

### static 那些事

(https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/static)

当与不同类型一起使用时，Static关键字具有不同的含义。我们可以使用static关键字：

**静态变量：** 函数中的变量，类中的变量

**静态类的成员：** 类对象和类中的函数

现在让我们详细看一下静态的这些用法：

**静态变量**

- 函数中的静态变量

当变量声明为static时，空间**将在程序的生命周期内分配**。即使多次调用该函数，静态变量的空间也**只分配一次**，前一次调用中的变量值通过下一次函数调用传递。这对于在C / C ++或需要存储先前函数状态的任何其他应用程序非常有用。

- 类中的静态变量

由于声明为static的变量只被初始化一次，因为它们在单独的静态存储中分配了空间，因此类中的静态变量**由对象共享。**对于不同的对象，不能有相同静态变量的多个副本。也是因为这个原因，静态变量不能使用构造函数初始化。



### this 那些事

首先来谈谈this指针的用处：

（1）一个对象的this指针并不是对象本身的一部分，不会影响sizeof(对象)的结果。

（2）this作用域是在类内部，当在类的非静态成员函数中访问类的非静态成员的时候，编译器会自动将对象本身的地址作为一个隐含参数传递给函数。也就是说，即使你没有写上this指针，编译器在编译的时候也是加上this的，它作为非静态成员函数的隐含形参，对各成员的访问均通过this进行。

其次，this指针的使用：

（1）在类的非静态成员函数中返回类对象本身的时候，直接使用 return *this。

（2）当参数与成员变量名相同时，如this->n = n （不能写成n = n)。



### [inline 那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/inline)

内联能提高函数效率，但并不是所有的函数都定义成内联函数！内联是以代码膨胀(复制)为代价，仅仅省去了函数调用的开销，从而提高函数的执行效率。

- 如果执行函数体内代码的时间相比于函数调用的开销较大，那么效率的收货会更少！
- 另一方面，每一处内联函数的调用都要复制代码，将使程序的总代码量增大，消耗更多的内存空间。

以下情况不宜用内联：

（1）如果函数体内的代码比较长，使得内联将导致内存消耗代价比较高。

（2）如果函数体内出现循环，那么执行函数体内代码的时间要比函数调用的开销大。

- 虚函数可以是内联函数，内联是可以修饰虚函数的，但是当虚函数表现多态性的时候不能内联。
- 内联是在编译期建议编译器内联，而虚函数的多态性在运行期，编译器无法知道运行期调用哪个代码，因此虚函数表现为多态性时（运行期）不可以内联。
- `inline virtual` 唯一可以内联的时候是：编译器知道所调用的对象是哪个类（如 `Base::who()`），这只有在编译器具有实际对象而不是对象的指针或引用时才会发生。

- [sizeof 那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/sizeof)

- 空类的大小为1字节
- 一个类中，虚函数本身、成员函数（包括静态与非静态）和静态数据成员都是不占用类对象的存储空间。
- 对于包含虚函数的类，不管有多少个虚函数，只有一个虚指针,vptr的大小。
- 普通继承，派生类继承了所有基类的函数与成员，要按照字节对齐来计算大小
- 虚函数继承，不管是单继承还是多继承，都是继承了基类的vptr。(32位操作系统4字节，64位操作系统 8字节)！
- 虚继承,继承基类的vptr。

### 智能指针

智能指针？（说了unique ptr和shared ptr）

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





### 函数指针那些事

```cpp

/**
 * @brief 定义了一个变量pFun，这个变量是个指针，指向返回值和参数都是空的函数的指针！
 */
void (*pFun)(int); 

/**
 * @brief 代表一种新类型，不是变量！所以与上述的pFun不一样！
 */
typedef void (*func)(void);  

void myfunc(void)
{
    cout<<"asda"<<endl;
}

void glFun(int a){ cout<<a<<endl;} 
int main(){
    func pfun = myfunc;/*赋值*/  
    pfun();/*调用*/  
    pFun = glFun; 
    (*pFun)(2); 
}
```

- [纯虚函数和抽象类那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/abstract)

C++中的纯虚函数(或抽象函数)是我们没有实现的虚函数！我们只需声明它! 通过声明中赋值0来声明纯虚函数！

```
// 抽象类
Class A {
public: 
    virtual void show() = 0; // 纯虚函数
    /* Other members */
}; 
```

- 纯虚函数：没有函数体的虚函数
- 抽象类：包含纯虚函数的类

抽象类只能作为基类来派生新类使用，不能创建抽象类的对象,抽象类的指针和引用->由抽象类派生出来的类的对象！

抽象类中：在成员函数内可以调用纯虚函数，在构造函数/析构函数内部不能使用纯虚函数。

如果一个类从抽象类派生而来，它必须实现了基类中的所有纯虚函数，才能成为非抽象类。

- [vptr_vtable 那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/vptr_vtable)
- [virtual 那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/virtual)

 **静态函数可以声明为虚函数吗？**

原因主要有两方面：

**静态函数不可以声明为虚函数，同时也不能被const 和 volatile关键字修饰**

static成员函数不属于任何类对象或类实例，所以即使给此函数加上virutal也是没有任何意义

虚函数依靠vptr和vtable来处理。vptr是一个指针，在类的构造函数中创建生成，并且只能用this指针来访问它，静态成员函数没有this指针，所以无法访问vptr。

代码学习：[static_error.cpp](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/virtual/set3/static_error.cpp)

（2）**构造函数可以为虚函数吗？**

构造函数不可以声明为虚函数。同时除了inline|explicit之外，构造函数不允许使用其它任何关键字。

为什么构造函数不可以为虚函数？

尽管虚函数表vtable是在编译阶段就已经建立的，但指向虚函数表的指针vptr是在运行阶段实例化对象时才产生的。 如果类含有虚函数，编译器会在构造函数中添加代码来创建vptr。 问题来了，如果构造函数是虚的，那么它需要vptr来访问vtable，可这个时候vptr还没产生。 因此，构造函数不可以为虚函数。

我们之所以使用虚函数，是因为需要在信息不全的情况下进行多态运行。而构造函数是用来初始化实例的，实例的类型必须是明确的。 因此，构造函数没有必要被声明为虚函数。

**析构函数可以为虚函数吗？**

析构函数可以声明为虚函数。如果我们需要删除一个指向派生类的基类指针时，应该把析构函数声明为虚函数。 事实上，只要一个类有可能会被其它类所继承， 就应该声明虚析构函数(哪怕该析构函数不执行任何操作)。



- [volatile 那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/volatile)

如果将变量i加上volatile修饰，则编译器保证对变量i的读写操作都不会被优化，从而保证了变量i被外部程序更改后能及时在原程序中得到感知。

多线程应用中被多个任务共享的变量。 当多个线程共享某一个变量时，该变量的值会被某一个线程更改，应该用 volatile 声明。作用是防止编译器优化把变量从内存装入CPU寄存器中，当一个线程更改变量后，未及时同步到其它线程中导致程序出错。volatile的意思是让编译器每次操作该变量时一定要从内存中真正取出，而不是使用已经存在寄存器中的值。

是否了解volatile的应用场景是区分C/C++程序员和嵌入式开发程序员的有效办法，搞嵌入式的家伙们经常同硬件、中断、RTOS等等打交道，这些都要求用到volatile变量，不懂得volatile将会带来程序设计的灾难。

- [assert 那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/assert)

断言，**是宏，而非函数**。

assert 宏的原型定义在 <assert.h>（C）、（C++）中。其作用是如果它的条件返回错误，则终止程序执行。

可以通过定义 `NDEBUG` 来关闭 assert，**但是需要在源代码的开头，include <assert.h> 之前。**



### 位域那些事

(https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/bit)



### extern 那些事

(https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/extern)

#### 1.C++与C编译区别

在C++中常在头文件见到extern "C"修饰函数，那有什么作用呢？ 是用于C++链接在C语言模块中定义的函数。

C++虽然兼容C，但C++文件中函数编译后生成的符号与C语言生成的不同。因为C++支持函数重载，C++函数编译后生成的符号带有函数参数类型的信息，而C则没有。

例如`int add(int a, int b)`函数经过C++编译器生成.o文件后，`add`会变成形如`add_int_int`之类的, 而C的话则会是形如`_add`, 就是说：相同的函数，在C和C++中，编译后生成的符号不同。

这就导致一个问题：如果C++中使用C语言实现的函数，在编译链接的时候，会出错，提示找不到对应的符号。此时`extern "C"`就起作用了：告诉链接器去寻找`_add`这类的C语言符号，而不是经过C++修饰的符号。

#### 2.C++调用C函数

C++调用C函数的例子: 引用C的头文件时，需要加`extern "C"`

`extern "C"`在C中是语法错误，需要放在C++头文件中。

不过与C++调用C接口不同，C++确实是能够调用编译好的C函数，而这里C调用C++，不过是把C++代码当成C代码编译后调用而已。也就是说，C并不能直接调用C++库函数。

### struct 那些事

(https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/struct)

#### C++中struct

与C对比如下：

- C++结构体中不仅可以定义数据，还可以定义函数。
- C++结构体中可以使用访问修饰符，如：public、protected、private 。
- C++结构体使用可以直接使用不带struct。
- C++继承
- 若结构体的名字与函数名相同，可以正常运行且正常的调用！但是定义结构体变量时候只用用带struct的！

[struct 与 class 那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/struct_class)

总的来说，struct 更适合看成是一个数据结构的实现体，class 更适合看成是一个对象的实现体。

区别:

最本质的一个区别就是默认的访问控制

默认的继承访问权限。struct 是 public 的，class 是 private 的。

struct 作为数据结构的实现体，它默认的数据访问控制是 public 的，而 class 作为对象的实现体，它默认的成员变量访问控制是 private 的。

- [union 那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/union)
- [c 实现 c++ 多态那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/c_poly)

C++中的多态:在C++中会维护一张虚函数表，根据赋值兼容规则，我们知道父类的指针或者引用是可以指向子类对象的。

如果一个父类的指针或者引用调用父类的虚函数则该父类的指针会在自己的虚函数表中查找自己的函数地址，如果该父类对象的指针或者引用指向的是子类的对象，而且该子类已经重写了父类的虚函数，则该指针会调用子类的已经重写的虚函数。

```cpp
class A
{
    public:
        virtual void f()//虚函数实现
        {
            cout << "Base A::f() " << endl;
        }
};

class B:public A    // 必须为共有继承，否则后面调用不到，class默认为私有继承！
{
    public:
        virtual void f()//虚函数实现,子类中virtual关键字可以没有
        {
            cout << "Derived B::f() " << endl;
        }
};

int main() 
{
    A a;//基类对象
    B b;//派生类对象

    A* pa = &a;//父类指针指向父类对象
    pa->f();//调用父类的函数

    pa = &b; //父类指针指向子类对象，多态实现
    pa->f();//调用派生类同名函数
    return 0;
}
```



### explicit 那些事

(https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/explicit)

explicit 修饰构造函数时，可以防止隐式转换和复制初始化

explicit 修饰转换函数时，可以防止隐式转换，但按语境转换除外

```cpp
#include <iostream>

using namespace std;

struct A
{
    A(int) { }
    operator bool() const { return true; }
};

struct B
{
    explicit B(int) {}
    explicit operator bool() const { return true; }
};

void doA(A a) {}

void doB(B b) {}

int main()
{
    A a1(1);        // OK：直接初始化
    A a2 = 1;        // OK：复制初始化
    A a3{ 1 };        // OK：直接列表初始化
    A a4 = { 1 };        // OK：复制列表初始化
    A a5 = (A)1;        // OK：允许 static_cast 的显式转换 
    doA(1);            // OK：允许从 int 到 A 的隐式转换
    if (a1);        // OK：使用转换函数 A::operator bool() 的从 A 到 bool 的隐式转换
    bool a6(a1);        // OK：使用转换函数 A::operator bool() 的从 A 到 bool 的隐式转换
    bool a7 = a1;        // OK：使用转换函数 A::operator bool() 的从 A 到 bool 的隐式转换
    bool a8 = static_cast<bool>(a1);  // OK ：static_cast 进行直接初始化

    B b1(1);        // OK：直接初始化
//    B b2 = 1;        // 错误：被 explicit 修饰构造函数的对象不可以复制初始化
    B b3{ 1 };        // OK：直接列表初始化
//    B b4 = { 1 };        // 错误：被 explicit 修饰构造函数的对象不可以复制列表初始化
    B b5 = (B)1;        // OK：允许 static_cast 的显式转换
//    doB(1);            // 错误：被 explicit 修饰构造函数的对象不可以从 int 到 B 的隐式转换
    if (b1);        // OK：被 explicit 修饰转换函数 B::operator bool() 的对象可以从 B 到 bool 的按语境转换
    bool b6(b1);        // OK：被 explicit 修饰转换函数 B::operator bool() 的对象可以从 B 到 bool 的按语境转换
//    bool b7 = b1;        // 错误：被 explicit 修饰转换函数 B::operator bool() 的对象不可以隐式转换
    bool b8 = static_cast<bool>(b1);  // OK：static_cast 进行直接初始化

    return 0;
}
```





- friend 那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/friend)

  [using 那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/using)

### :: 那些事

(https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/maohao)

- 全局作用域符（::name）：用于类型名称（类、类成员、成员函数、变量等）前，表示作用域为全局命名空间
- 类作用域符（class::name）：用于表示指定类型的作用域范围是具体某个类的
- 命名空间作用域符（namespace::name）:用于表示指定类型的作用域范围是具体某个命名空间的



- [enum 那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/enum)
- [decltype 那些事](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/decltype)

### [引用与指针那些事

[(https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/pointer_refer)

总论：

| 引用         | 指针         |
| ------------ | ------------ |
| 必须初始化   | 可以不初始化 |
| 不能为空     | 可以为空     |
| 不能更换目标 | 可以更换目标 |

> 引用必须初始化，而指针可以不初始化。

我们在定义一个引用的时候必须为其指定一个初始值，但是指针却不需要。

> 引用不能为空，而指针可以为空。

由于引用不能为空，所以我们在使用引用的时候不需要测试其合法性，而在使用指针的时候需要首先判断指针是否为空指针，否则可能会引起程序崩溃。

> 引用不能更换目标

指针可以随时改变指向，但是引用只能指向初始化时指向的对象，无法改变。

#### 左值引用

常规引用，一般表示对象的身份。

#### 右值引用

右值引用就是必须绑定到右值（一个临时对象、将要销毁的对象）的引用，一般表示对象的值。

右值引用可实现转移语义（Move Sementics）和精确传递（Perfect Forwarding），它的主要目的有两个方面：

- 消除两个对象交互时不必要的对象拷贝，节省运算存储资源，提高效率。
- 能够更简洁明确地定义泛型函数。

#### 引用折叠

- `X& &`、`X& &&`、`X&& &` 可折叠成 `X&`
- `X&& &&` 可折叠成 `X&&`

C++的引用**在减少了程序员自由度的同时提升了内存操作的安全性和语义的优美性**。比如引用强制要求必须初始化，可以让我们在使用引用的时候不用再去判断引用是否为空，让代码更加简洁优美，避免了指针满天飞的情形。除了这种场景之外引用还用于如下两个场景：

> 引用型参数

一般我们使用const reference参数作为只读形参，这种情况下既可以避免参数拷贝还可以获得与传值参数一样的调用方式。

```
void test(const vector<int> &data)
{
    //...
}
int main()
{
  	vector<int> data{1,2,3,4,5,6,7,8};
    test(data);
}
```

> 引用型返回值

C++提供了重载运算符的功能，我们在重载某些操作符的时候，使用引用型返回值可以获得跟该操作符原来语法相同的调用方式，保持了操作符语义的一致性。一个例子就是operator []操作符，这个操作符一般需要返回一个引用对象，才能正确的被修改。

```
vector<int> v(10);
v[5] = 10;    //[]操作符返回引用，然后vector对应元素才能被修改
              //如果[]操作符不返回引用而是指针的话，赋值语句则需要这样写
*v[5] = 10;   //这种书写方式，完全不符合我们对[]调用的认知，容易产生误解
```

#### 3.指针与引用的性能差距

C++中的引用只是C++对指针操作的一个“语法糖”，在底层实现时C++编译器实现这两种操作的方法完全相同。

C++中引入了引用操作，在对引用的使用加了更多限制条件的情况下，保证了引用使用的安全性和便捷性，还可以保持代码的优雅性。在适合的情况使用适合的操作，引用的使用可以一定程度避免“指针满天飞”的情况，对于提升程序稳定性也有一定的积极意义。最后，指针与引用底层实现都是一样的，不用担心两者的性能差距。

### [宏那些事]

[(https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/macro)

#### 1.宏中包含特殊符号

分为几种：`#`，`##`，`\`

##### 1.1 字符串化操作符（#）

**在一个宏中的参数前面使用一个#,预处理器会把这个参数转换为一个字符数组**，换言之就是：**#是“字符串化”的意思，出现在宏定义中的#是把跟在后面的参数转换成一个字符串**。

**注意：其只能用于有传入参数的宏定义中，且必须置于宏定义体中的参数名前。**



### 多态和虚函数

#### 一、多态性

 多态性：多态就是在同一个类或继承体系结构的基类与派生类中，用同名函数来实现各种不同的功能。

**静态绑定又称静态联编**，是指在编译程序时就根据调用函数提供的信息，把它所对应的具体函数确定下来，即在编译时就把调用函数名与具体函数绑定在一起。

**动态绑定又称动态联编**，是指在编译程序时还不能确定函数调用所对应的具体函数，只有在程序运行过程中才能够确定函数调用所对应的具体函数，即在程序运行时才把调用函数名与具体函数绑定在一起。

编译时多态性： ---静态联编(连接)----系统在编译时就决定如何实现某一动作,即对某一消息如何处理.静态联编具有执行速度快的优点.在C++中的编译时多态性是通过函数重载和运算符重载实现的。 运行时多态性： ---动态联编(连接)----系统在运行时动态实现某一动作,即对某一消息在运行过程实现其如何响应.动态联编为系统提供了灵活和高度问题抽象的优点,在C++中的运行时多态性是通过继承和虚函数实现的。

#### 二、虚函数

虚函数的意义

1、基类与派生类的赋值相容

派生类对象可以赋值给基类对象。 派生类对象的地址可以赋值给指向基类对象的指针。 派生类对象可以作为基类对象的引用。 赋值相容的问题： 不论哪种赋值方式，都只能通过基类对象（或基类对象的指针或引用）访问到派生类对象从基类中继承到的成员， 不能借此访问派生类定义的成员。

2、虚函数使得可以通过基类对象的指针或引用访问派生类定义的成员。

3.Virtual关键字其实质是告知编译系统，被指定为virtual的函数采用动态联编的形式编译。

4.虚函数的虚特征：基类指针指向派生类的对象时，通过该指针访问其虚函数将调用派生类的版本。

- 一旦将某个成员函数声明为虚函数后，它在继承体系中就永远为虚函数了
- 如果基类定义了虚函数，当通过基类指针或引用调用派生类对象时，将访问到它们实际所指对象中的虚函数版本。
- 只有通过基类对象的指针和引用访问派生类对象的虚函数时，才能体现虚函数的特性。
- 派生类中的虚函数要保持其虚特征，必须与基类虚函数的函数原型完全相同，否则就是普通的重载函数，与基类的虚函数无关。
- 派生类通过从基类继承的成员函数调用虚函数时，将访问到派生类中的版本。
- 只有类的非静态成员函数才能被定义为虚函数，类的构造函数和静态成员函数不能定义为虚函数。原因是虚函数在继承层次结构中才能够发生作用，而构造函数、静态成员是不能够被继承的。
- 内联函数也不能是虚函数。因为内联函数采用的是静态联编的方式，而虚函数是在程序运行时才与具体函数动态绑定的，采用的是动态联编的方式，即使虚函数在类体内被定义，C++编译器也将它视为非内联函数。 5.基类析构函数几乎总是为虚析构函数。 why? 假定使用delete和一个指向派生类的基类指针来销毁派生类对象，如果基类析构函数不为虚,就如一个普通成员函数，delete函数调用的就是基类析构函数。在通过基类对象的引用或指针调用派生类对象时，将致使对象析构不彻底！

作者：牛客988320449号
链接：https://www.nowcoder.com/discuss/828174?source_id=profile_create_nctrack&channel=-1
来源：牛客网



为了实现C++的多态，C++使用了一种动态绑定的技术。这个技术的核心是虚函数表（下文简称虚表）。每个包含了虚函数的类都包含一个虚表。 

 我们知道，当一个类（A）继承另一个类（B）时，类A会继承类B的函数的调用权。所以如果一个基类包含了虚函数，那么其继承类也可调用这些虚函数，换句话说，一个类继承了包含虚函数的基类，那么这个类也拥有自己的虚表。  我们来看以下的代码。类A包含虚函数vfunc1，vfunc2，由于类A包含虚函数，故类A拥有一个虚表。 

 那么，什么时候会执行函数的动态绑定？这需要符合以下三个条件。 

-  通过指针来调用函数 
-  指针upcast向上转型（继承类向基类的转换称为upcast，关于什么是upcast，可以参考本文的参考资料） 
-  调用的是虚函数 

 如果一个函数调用符合以上三个条件，编译器就会把该函数调用编译成动态绑定，其函数的调用过程走的是上述通过虚表的机制。

#### 三、纯虚函数和抽象类

1.纯虚函数概念？

仅定义函数原型而不定义其实现的虚函数 Why pure function? 实用角度：占位手段place-holder 方法学：接口定义手段，抽象表达手段 How? class X { virtual ret_type func_name (param) = 0; } 2.抽象类概念？

What is an abstract class? 包含一个或多个纯虚函数的类 Using abstract class **不能实例化抽象类** 但是可以定义抽象类的指针和引用 Converting abstract class to concrete class 定义一个抽象类的派生类 定义所有纯虚函数

3.C++对抽象类具有以下限定

- 抽象类中含有纯虚函数，由于纯虚函数没有实现代码，所以不能建立抽象类的对象。
- 抽象类只能作为其他类的基类，可以通过抽象类对象的指针或引用访问到它的派生类对象，实现运行时的多态性。
- 如果派生类只是简单地继承了抽象类的纯虚函数，而没有重新定义基类的纯虚函数，则派生类也是一个抽象类。

### 动态库和静态库的区别

#### 【静态库】

在链接阶段，会将汇编生成的目标文件.o与引用到的库一起链接打包到可执行文件中。因此对应的链接方式称为静态链接。

试想一下，静态库与汇编生成的目标文件一起链接为可执行文件，那么静态库必定跟.o文件格式相似。其实一个静态库可以简单看成是一组目标文件（.o/.obj文件）的集合，即很多目标文件经过压缩打包后形成的一个文件。静态库特点总结：

l 静态库对函数库的链接是放在编译时期完成的。

l 程序在运行时与函数库再无瓜葛，移植方便。

l 浪费空间和资源，因为所有相关的目标文件与牵涉到的函数库被链接合成一个可执行文件。

#### 动态库

动态库在程序编译时并不会被连接到目标代码中，而是在程序运行是才被载入。**不同的应用程序如果调用相同的库，那么在内存里只需要有一份该共享库的实例**，规避了空间浪费问题。动态库在程序运行是才被载入，也解决了静态库对程序的更新、部署和发布页会带来麻烦。用户只需要更新动态库即可，**增量更新**。

动态库特点总结：

l 动态库把对一些库函数的链接载入推迟到程序运行的时期。

l 可以实现进程之间的资源共享。（因此动态库也称为共享库）

l 将一些程序升级变得简单。

l 甚至可以真正做到链接载入完全由程序员在程序代码中控制（**显式调用**）。

Window与Linux执行文件格式不同，在创建动态库的时候有一些差异。

#### g++(gcc)编译选项

l -shared ：指定生成动态链接库。

l -static ：指定生成静态链接库。

l -fPIC ：表示编译为位置独立的代码，用于编译共享库。目标文件需要创建成位置无关码， 就是在可执行程序装载它们的时候，它们可以放在可执行程序的内存里的任何地方。

l -L. ：表示要连接的库所在的目录。

l -l：指定链接时需要的动态库。编译器查找动态连接库时有隐含的命名规则，即在给出的名字前面加上lib，后面加上.a/.so来确定库的名称。

l -Wall ：生成所有警告信息。

l -ggdb ：此选项将尽可能的生成gdb 的可以使用的调试信息。

l -g ：编译器在编译的时候产生调试信息。

l -c ：只激活预处理、编译和汇编,也就是把程序做成目标文件(.o文件) 。

l -Wl,options ：把参数(options)传递给链接器ld 。如果options 中间有逗号,就将options分成多个选项,然后传递给链接程序。

