reference往往以指针的形式实现出来，因此，pass by reference你可以看成是传指针

而pass by value 就会拷贝一份临时的数据或者说对象

对于内置类型 int double 效率上肯定是pass by value效率更高

所以在STL中，很多时候都是pass by value

那什么时候用pass by reference呢

答案是，除了之前的情况，大部分时候都要用pass by reference 

pass by value 还面临着对象切割的问题



```
void function(A a)
{
	a.display();
}


class A
{
	void display()

}
class B:public A
{
	virtual void display()

}

```

对象切割slicing 就是传一个子类B的对象b作为参数

但是在函数中调用

```
b.display();
```

的时候，会调用类A的display而不是类B的

因为function的参数是A 而b以pass by value 传进来就会被切割

