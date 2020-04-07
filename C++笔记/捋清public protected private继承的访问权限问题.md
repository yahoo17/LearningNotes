## 捋清public protected private继承的访问权限问题

写一个我认为的本质吧

继承的本质就是为了代码复用嘛,你可以理解为把基类的代码全部copy过来

只不过copy的时候可能要做修改嘛

那么怎么确定修改的方式呢?

答案是依据继承的类型

* 如果是public继承 就把父类原封不动搬过来就好了(需要说明的是父类的private永远都不搬的) 父类的public还是public 父类的protected还是protected 
* 如果是protected继承 就和上面不一样了 它会把public改成protected protected照搬为protected
* 如果是private继承 它会把 基类的public 和protected都改成private

好的.现在我们已经把基类的代码搬到子类了我们来看看效果



```C++
#include <iostream>
class B 
{
private:
    void pvB() { printf("pvB\n"); }
protected:
    void ptB() { printf("ptB\n"); }
public:
    void pbB() { printf("pbB\n"); }

};
class D: public B
{
    //_________________________
// 搬的时候注意要不要修改 我这里是public继承 所以没修改
protected:
    void ptB() { printf("ptB\n"); }
public:
    void pbB() { printf("pbB\n"); }
    //_______________________________
    
    
public:	
    void func() { ptB(); pbB(); }
protected:

private:

};

```

那么你看,

* 在这个类D里,类作用域里,能访问的东西自然是 这个类里面的所有东西 对吧,由于我们已经把类B搬进来了 (你自然可以把他们看成这个类的成员 这也是为了我后面叙述更多层的继承做准备)

* 那么 ,在类D之外 ,比如说main函数里,我们建一个D对象,能访问这个对象的什么呢? 自然是这个对象的public啦,这个对象的public自然还包括了继承得来的基类的public

至此,两层继承 类内类外的访问权限我们都可以轻易算出了

那么更多层次的继承呢 ,用上面的方法 再搬一次就好啦,对吧 哈哈哈