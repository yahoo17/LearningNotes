# Vector动态扩容

无聊看了一下Vector的源码

看看动态扩容怎么实现的

### 一.vector的介绍

首先这玩意是动态的,非常灵活 储存的时候是连续的线性空间, 

**插播一个在<STL源码剖析> 中看到的问题, 提出质疑**

  原文如下:

```C++

  
所以它的迭代器也是完全可以用普通的指针

比如
vector<int>::iterator i1;
vector<shape>::iteraor i2;

i1其实就是int *
i2其实就是 shape *
    //
```

但是经过我的实验, 好像不是这样

![1586939718988](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\1586939718988.png)

先上Vector的数据结构

```C++
class Vector
{
	public:
		iterator start;
		iterator begin(){return start};
        //目前使用了的空间头
        
		iterator finish;
		iterator end(){return finish};		
        //目前使用了的空间的尾
        
        size_type size(){ return size_type(end-start);}
        
        reference front() {return *begin();}
        reference back(){return *(end()-1);}
		iterator end_of_storage;	//目前可用空间的尾
		
    	bool empty(){return begin()==end();}
}
```

#### 看完觉得真的很简洁 我这里粗略的写了一些而已 够我们后面去理解

当我们用push_back插入的时候,会检查 还有没有备用的空间 ,如果没有的话

要经历allocator先按**规则**分配空间 然后把之前的拷贝过去, 再插入,最后释放原来的空间 这是一个庞大的工程

**分配空间的规则**

{

如果原本大小为0

​	分配空间为1;

else

​	分配空间为=原来的*2;

}

