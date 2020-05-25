 # C++多线程

### thread

在使用`std::thread`的时候，对创建的线程有两种操作：等待/分离，也就是`join/detach`操作。`join()`操作是在`std::thread t(func)`后“某个”合适的地方调用，其作用是回收对应创建的线程的资源，避免造成资源的泄露。`detach()`操作是在`std::thread t(func)`后马上调用，用于把被创建的线程与做创建动作的线程分离，分离的线程变为后台线程,其后，创建的线程的“死活”就与其做创建动作的线程无关，它的资源会被init进程回收。

在这里主要对`join`做深入的理解。

由于`join`是等待被创建线程的结束，并回收它的资源。因此，join的调用位置就比较关键。比如，以下的调用位置都是错误的。

 因此std::thread提供了几个线程管理的工具，其中join就是很重要的一个：等待线程执行完成。即使当线程函数已经执行完成后，调用join仍然是有效的。 

### Mutex

mutex又称互斥量，用于提供对共享变量的互斥访问。C++11中mutex相关的类都在<mutex>头文件中。共四种互斥类:

| 序号 | 名称                       | 用途                                            |
| :--: | -------------------------- | ----------------------------------------------- |
|  1   | std::mutex                 | 最基本也是最常用的互斥类                        |
|  2   | std::recursive_mutex       | 同一线程内可递归(重入)的互斥类                  |
|  3   | std::timed_mutex           | 除具备mutex功能外，还提供了带时限请求锁定的能力 |
|  4   | std::recursive_timed_mutex | 同一线程内可递归(重入)的timed_mutex             |

#### [1115. 交替打印FooBar](https://leetcode-cn.com/problems/print-foobar-alternately/)

我们提供一个类：

```
class FooBar {
  public void foo() {
    for (int i = 0; i < n; i++) {
      print("foo");
    }
  }

  public void bar() {
    for (int i = 0; i < n; i++) {
      print("bar");
    }
  }
}
```

两个不同的线程将会共用一个 `FooBar` 实例。其中一个线程将会调用 `foo()` 方法，另一个线程将会调用 `bar()` 方法。

请设计修改程序，以确保 "foobar" 被输出 n 次。

>
>
>```
>class FooBar {
>private:
>    int n;
>    mutex m1,m2;
>public:
>    FooBar(int n) {
>        this->n = n;
>        m2.lock();
>    }
>
>    void foo(function<void()> printFoo) {
>        
>        for (int i = 0; i < n; i++) {
>            m1.lock();
>        	// printFoo() outputs "foo". Do not change or remove this line.
>        	printFoo();
>            m2.unlock();
>        }
>    }
>
>    void bar(function<void()> printBar) {
>        
>        for (int i = 0; i < n; i++) {
>            m2.lock();
>        	// printBar() outputs "bar". Do not change or remove this line.
>        	printBar();
>            m1.unlock();
>        }
>    }
>};
>```
>
>

# std::condition_variable

 

[ C++](https://zh.cppreference.com/w/cpp)

 

[线程支持库](https://zh.cppreference.com/w/cpp/thread)

 

**`std::condition_variable`**

 

| 定义于头文件 ``           |      |            |
| ------------------------- | ---- | ---------- |
| class condition_variable; |      | (C++11 起) |
|                           |      |            |

`condition_variable` 类是同步原语，能用于阻塞一个线程，或同时阻塞多个线程，直至另一线程修改共享变量（*条件*）并通知 `condition_variable` 。 

```C++
#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
 
std::condition_variable cv;
std::mutex cv_m; // This mutex is used for three purposes:
                 // 1) to synchronize accesses to i
                 // 2) to synchronize accesses to std::cerr
                 // 3) for the condition variable cv
int i = 0;
 
void waits()
{
    std::unique_lock<std::mutex> lk(cv_m);
    std::cerr << "Waiting... \n";
    cv.wait(lk, []{return i == 1;});
    std::cerr << "...finished waiting. i == 1\n";
}
 
void signals()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk(cv_m);
        std::cerr << "Notifying...\n";
    }
    cv.notify_all();
 
    std::this_thread::sleep_for(std::chrono::seconds(1));
 
    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
        std::cerr << "Notifying again...\n";
    }
    cv.notify_all();
}
 
int main()
{
    std::thread t1(waits), t2(waits), t3(waits), t4(signals);
    t1.join(); 
    t2.join(); 
    t3.join();
    t4.join();
}
```

#### [1116. 打印零与奇偶数](https://leetcode-cn.com/problems/print-zero-even-odd/)

假设有这么一个类：

```
class ZeroEvenOdd {
  public ZeroEvenOdd(int n) { ... }      // 构造函数
  public void zero(printNumber) { ... }  // 仅打印出 0
  public void even(printNumber) { ... }  // 仅打印出 偶数
  public void odd(printNumber) { ... }   // 仅打印出 奇数
}
```

相同的一个 `ZeroEvenOdd` 类实例将会传递给三个不同的线程：

1. 线程 A 将调用 `zero()`，它只输出 0 。
2. 线程 B 将调用 `even()`，它只输出偶数。
3. 线程 C 将调用 `odd()`，它只输出奇数。

每个线程都有一个 `printNumber` 方法来输出一个整数。请修改给出的代码以输出整数序列 `010203040506`... ，其中序列的长度必须为 2*n*。

 >
 >
 >```
 >class ZeroEvenOdd {
 >private:
 >    int n;
 >    mutex m1;
 >    condition_variable cv;
 >    bool zeroOrother=false;  //t
 >    bool oddOreven=false;
 >public:
 >    ZeroEvenOdd(int n) {
 >        this->n = n;
 >    }
 >
 >    // printNumber(x) outputs "x", where x is an integer.
 >    void zero(function<void(int)> printNumber) {
 >        {
 >            for(int i=0;i<n;i++)
 >            {
 >                unique_lock<mutex> lock(m1);
 >                cv.wait(lock,[=]{return !zeroOrother;});
 >                zeroOrother=true;
 >                printNumber(0);
 >                cv.notify_all();
 >
 >            }
 >            
 >        }
 >    }
 >
 >    void even(function<void(int)> printNumber) {
 >        for(int i=2;i<=n;i+=2)
 >        {
 >            unique_lock<mutex> lock(m1);
 >            cv.wait(lock,[=]{return zeroOrother&&oddOreven;});
 >            printNumber(i);
 >            zeroOrother=false;
 >            oddOreven=false;
 >            cv.notify_all();
 >        }
 >        
 >    }
 >
 >    void odd(function<void(int)> printNumber) {
 >        for(int i=1;i<=n;i+=2)
 >        {
 >            unique_lock<mutex> lock(m1);
 >            cv.wait(lock,[=]{return  zeroOrother&&!oddOreven;});
 >            printNumber(i);
 >            zeroOrother=false;
 >            oddOreven=true;
 >            cv.notify_all();
 >        }
 >    }
 >};
 >```
 >
 >



```
class H2O {
private:

    mutex m1;
    mutex m2;
    condition_variable cv;
    int hcount=0;
    bool henough=false;
    bool oenough=false;
 

public:
    H2O() {
        
    }

    void hydrogen(function<void()> releaseHydrogen) {
       
        {
            unique_lock<mutex> lock(m1);
            cv.wait(lock,[=]{retuQrn !henough;});
            releaseHydrogen();
            hcount++;
            if(hcount>=2)
                henough=true;
            cv.notify_all();
        }
        if(henough&&oenough)
        {
           lock_guard<mutex> lock(m1);
            hcount-=2;
            henough=false;
            oenough=false;
        }
       
    }

    void oxygen(function<void()> releaseOxygen) {
        
        
        {
            unique_lock<mutex> lock(m1);
            cv.wait(lock,[=]{return !oenough;});
            releaseOxygen();
            oenough=true;
            cv.notify_all();
        }
       
    }
};
```

```
class FizzBuzz {
private:
    int n;
    condition_variable cv;
    mutex m1;
public:
    FizzBuzz(int n) {
        this->n = n;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        for(int i=1;i<=n;i++)
        {            
            unique_lock<mutex> lock(m1);
            cv.wait(lock,[=]{return i%3==0&&i%5;});
            printFizz();
            cv.notify_all();         
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        
        for(int i=1;i<=n;i++)
        {
            unique_lock<mutex> lock(m1);
            cv.wait(lock,[=]{return i%3&&i%5==0;});
            printBuzz();
            cv.notify_all();          
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        for(int i=1;i<=n;i++)
        {
            unique_lock<mutex> lock(m1);
            cv.wait(lock,[=]{return i%3==0&&i%5==0;});
            printFizzBuzz();
            cv.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        for(int i=1;i<=n;i++)
        {
            unique_lock<mutex> lock(m1);
            cv.wait(lock,[=]{return i%3&&i%5;});
            printNumber(i);
            cv.notify_all();           
        }
    }
};
```

