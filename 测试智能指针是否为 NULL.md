测试智能指针是否为 NULL 

在Qt的项目中，osg里有智能指针

``` 
osg::ref_ptr<int> a;
```

然后可能和C++标准库不同 ,在判断智能指针是否为空的时候

> 
>
> **以下来自与《More Effective C++》 ，读了觉得很有收获**
>
> **文尾有我看VS2019的MSVC2017中的头文件 和 osg的**
>
> 

但是有一件我们做不到的事情是“发现灵巧指针为 NULL”： 

````c++
SmartPtr<TreeNode> ptn; 

if (ptn == 0) ...                    // error! 
if (ptn) ...                         // error! 
if (!ptn) ...                        // error! 
````



这是一个严重的限制。 

## 在灵巧指针类里加入一个 isNull 成员函数是一件很容易的事

## 但是没有解决当测试NULL 时灵巧指针的行为与 dumb pointer（即普通指针） 不相似的问题。

另一种方法是提供隐式类型转换操作符，允许编译上述的测试。一般应用于这种目的的类型转换是 void* ： 



````
template<class T> 
class SmartPtr { 
public: 
  ... 
  operator void*();                  // 如果灵巧指针为 null， 
  ...                                // 返回 0， 否则返回 
};                                   // 非 0。 
SmartPtr<TreeNode> ptn; 
... 
if (ptn == 0) ...                    // 现在正确 
if (ptn) ...                         // 也正确 
if (!ptn) ...                        // 正确 
````



这与 iostream 类中提供的类型转换相同，所以可以这样编写代码： 

````
ifstream inputFile("datafile.dat"); 
if (inputFile) ...                   // 测试 inputFile 是否已经被 
                                     // 成功地打开。 
````



像所有的类型转换函数一样，它有一个缺点：在一些情况下虽然大多数程序员希望它调
用失败，但是函数确实能够成功地被调用（参见条款 M5）。特别是它允许灵巧指针与完全不
同的类型之间进行比较： 

````
SmartPtr<Apple> pa; 
SmartPtr<Orange> po; 
... 
if (pa == po) ...                    // 这能够被成功编译! 
````



即使在 SmartPtr<Apple> 和 SmartPtr<Orange>之间没有 operator= 函数，也能够编译，
因为灵巧指针被隐式地转换为 void*指针，而对于内建指针类型有内建的比较函数。这种进
行隐式类型转换的行为特性很危险。（再回看一下条款 M5,必须反反复复地阅读，做到耳熟
能详。） 
在 void*类型转换方面，也有一些变化。有些设计者采用到 const void*的类型转换，
还有一些采取转换到 bool 的方法。这些变化都没有消除混合类型比较的问题。 
有一种两全之策可以提供合理的测试 null 值的语法形式，同时把不同类型的灵巧指针
之间进行比较的可能性降到最低。



## 这就是在灵巧指针类中重载 operator!，当且仅当灵巧指针是一个空指针时，operator!返回 true：



​	

````
template<class T> 
class SmartPtr { 
public:   ... 
  bool operator!() const;            // 当且仅当灵巧指针是 
  ...                                // 空值，返回 true。 
}; 
用户程序如下所示： 
SmartPtr<TreeNode> ptn; 
... 
if (!ptn) {                          // 正确 
  ...                                // ptn 是空值 
} 
else { 
  ...                                // ptn 不是空值 
} 
但是这样就不正确了： 
if (ptn == 0) ...                    // 仍然错误 
if (ptn) ...                         // 也是错误的 
仅在这种情况下会存在不同类型之间进行比较： 
SmartPtr<Apple> pa; 
SmartPtr<Orange> po; 
... 
if (!pa == !po) ...                 // 能够编译


 
````



幸好程序员不会经常这样编写代码。

有趣的是，iostream 库的实现除了提供 void*隐式
的类型转换，也有 operator!函数，不过这两个函数通常测试的流状态有些不同。*

（在 C++类库标准中（参见 Effective C++ 条款 49 和本书条款 M35）

，void*隐式的类型转换已经被bool 类型的转换所替代，operator bool 总是返回与 operator!相反的值。）

## 而在osg中也有重载operator！





![1582033732568](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\1582033732568.png)

## 但是在VS里面没有

![](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\1582034393360.png)