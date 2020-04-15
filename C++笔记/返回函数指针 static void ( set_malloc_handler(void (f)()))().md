## 返回函数指针 static void (* set_malloc_handler(void (*f)()))()   

```C++
static void (*set_malloc_handler(void (*f)()))() {
    
}
```

<STL源码剖析> P52 有一个函数长这样  ,读了好久都没看懂啥意思



实际上完整的代码应该是这样的

```C++
class A
{
public:
    static void (*__malloc_alloc_oom_handler)();
    //定义了一个函数指针__malloc_alloc_oom_handler 对应的函数的返回类型是void , 参数类型是()
    //
public:
    static void (*set_malloc_hander(void (*f)())) ()
    {
        void (*old)() = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = f;
        return (old);
    }
};
```

嗯 __malloc_alloc_oom_handler是一个函数指针

###  对于 static void (* set_malloc_handler(void (*f)()))()   

首先应该看出 void(*f)() 是一个函数指针f作为参数 

那么由于函数指针作为返回类型的特殊语法,我们接下来就看不懂了

先说结论  这样就看得懂了吧

```
void *()     set_malloc_handler  (     void(*f)()     )
```

或者说这样总归看得懂了

```C++
static PF set_malloc_handler(PF f) {
    PF old = __malloc_alloc_oom_handler;
    __malloc_alloc_oom_handler = f;
    return (old);
}
```



set_malloc_handler是函数名

返回类型是函数指针

参数是函数指针

 **综合起来说，就是我们定义了一个函数set_malloc_handler，它接受一个void ( * )()类型的参数f，返回类型为void ( * )( )**

在C++11中

利用C++11的尾置返回类型表达式函数首部可以写成这样：

```C++

	//方法3
static auto set_malloc_handler(void (*f)()) -> void (*)()
```

在VS中测试是正常的



当然还有其他办法

```C++
typedef void (*PF)(); //方法1  我们定义一个函数指针类型PF代表void (*)()类型
using PF = void (*)(); //方法2 在C++11中
```



```C++
static PF set_malloc_handler(PF f) {
    PF old = __malloc_alloc_oom_handler;
    __malloc_alloc_oom_handler = f;
    return (old);
}
```

