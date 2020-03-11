# C++ 面向对象高级特性和STL（一）设计模式

目前遇到的，最简单好用的设计模式

单例模式

```C++
class A
{
    public:
    	static A * getInstance()
        {
            if(m_a==nullptr)
             	m_a=new A();   
			return m_a;
        }
    private:
    	static A* m_a;
}


```

>
>
>这个很好理解嘛，A永远只有一个静态实例，避免创建多个A类型的对象嘛。
>
>在实际项目中，遇到的问题也有，比如说
>
>要在类A中 ，拿到某个文件的绝对路径 ，如果我们用的是
>
>```
>qApp->applicationDirPath
>```
>
>这就会有一个问题 ：我那个静态对象会早于qApp初始化，也就是说，没法调用这个办法拿到路径
>
>解决方法：
>
>就是初始化写到static init()函数里，然后在main函数里调用init
>
> 



