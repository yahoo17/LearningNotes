### 《C++ Primer》

### 关联容器

**有8种 其实就是map 和set**

map 普通map

mutimap 就是可重复的map

 

unordered_map 就是无序的map

unordered_mutimap 就是无序的且可重复的map

然后set同理，所以一共有8个

可以使用列表初始化

 

```C++
// justForTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

\#include <C:\Users\DELL\source\repos\LibrarySystem\dataStructure.cpp>

\#include <vector>

\#include <string>

\#include <iostream>

\#include <map>

\#include <set>

\#include <unordered_map>

\#include <unordered_set>

 

using namespace std;

 

int main()

{

  set<int> testset = { 1,2,3 };

   map<string, int> mp;

   //初始化 set和map都是模板类型的

   //map的元素是pair对

   mp = { {"annotation",1} ,{"double",2} };

 

   //map的下标操作，map的下标操作比较特殊，如果是这样子的，annotation关键字对应的值（键值对）本来是1，就会赋2

   mp["annotation"] = 2;

 

   mp["trible"] = 3; //这样会先查找，找不到啊，那会插入trible，然后赋值0，然后再赋值3

 

   /*那map的查找操作，应该用find 或者count 那么find很好，如果没找到 就会返回尾迭代器*/

   mp.find("annotation");

   //所以就有了find==end 这种好操作 要是等于end，就意味着没找到

   if(mp.find("annotation1  ")==mp.end())

​    cout << "没找到" << endl;

 

   //打印map的每一个键值对

   for (const auto& x : mp)

   {

​     cout << "关键字是" << x.first << " 值是" << x.second << endl;

   }

   testset.insert(3);

   testset.insert(5);

   for (auto it=testset.begin();it!=testset.end();it++)

​     cout << *it;

   //迭代器 cbegin() 和begin() 这个cbegin是const

   /* begin()     Return iterator to beginning (public member function )

​    cbegin()    Return const_iterator to beginning (public member function )

   */

 

   /*

​    set的迭代器是const的 只能用迭代器来访问这些只读元素 不能用迭代器来修改

   */

   //set插入元素用insert可以是两个迭代器，也可以直接是；

 

   /* key_type 是键值对的键的类型 value_type是键值对的值的类型

​    且对于set来说键，值都是一样的类型

​    所以set的这两个都相同

​    但是对于map来说，就不一样了

​    map的key那个好理解，就是键的类型

​    但是map的value_type却是指的是pair这种键值对的类型

​    那么值的类型，我们用了一个特别的mapped_tyepe

   */

   map<string, int>::mapped_type v1 = 2;

 

   map<string, int>::value_type v2 = { "string",1 };

 

   // map<string, int>::value_type v2 = 1; 这句就会报错

 

   map<string, int>::key_type v3 = " stign";

}
```



 