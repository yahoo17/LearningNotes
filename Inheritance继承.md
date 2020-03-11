# Inheritance继承

------

JavaScript使用基于原型的继承。 每个对象都有一个原型，并且当调用该对象的方法时，JavaScript会尝试从原型对象中查找要执行的正确函数。

### The prototype attribute

Without using the prototype object, we can define the object Person like this:

```javascript
function Person(name, age)
{
    this.name = name;
    this.age = age;

    function describe()
    {
        return this.name + ", " + this.age + " years old.";
    }
}
```

创建Person对象的实例时，我们将创建函数的所有成员和方法的新副本。 这意味着对象的每个实例将具有其自己的名称和年龄属性以及其自己的describe函数。但是，如果我们使用 Person.prototype 对象并为其分配功能，它也将起作用。



```javascript
function Person(name, age)
{
    this.name = name;
    this.age = age;
}

Person.prototype.describe = function()
{
    return this.name + ", " + this.age + " years old.";
}
```

创建Person对象的实例时，它们将不包含describe函数的副本。 相反，当调用对象方法时，JavaScript将尝试首先从对象本身解析出describe函数，然后再使用其原型属性。

### Inheritance

Let's say we want to create a `Person` object, and a `Student` object derived from `Person`:

```javascript
var Person = function() {};

Person.prototype.initialize = function(name, age)
{
    this.name = name;
    this.age = age;
}

Person.prototype.describe = function()
{
    return this.name + ", " + this.age + " years old.";
}

var Student = function() {};
Student.prototype = new Person();

Student.prototype.learn = function(subject)
{
    console.log(this.name + " just learned " + subject);
}

var me = new Student();

me.initialize("John", 25);
me.learn("Inheritance");
```

正如我们在本例中看到的那样，“ initialize”方法属于“ Person”，而“ learn”方法属于“ Student”，两者现在都属于“ me”对象。

请记住，使用JavaScript进行继承的方法有很多，这只是其中之一。

## Exercise

Create an object called `Teacher` derived from the `Person` class, and implement a method called `teach` which receives a string called `subject`, and prints out:

```javascript
[teacher's name] is now teaching [subject]
```

## Answer

```javascript
var Person = function() {};

Person.prototype.initialize = function(name, age)
{
    this.name = name;
    this.age = age;
}
var Teacher=function(){};
Teacher.prototype=new Person();
Teacher.prototype.teach=function(subject)
{
    console.log( this.name+" is now teaching "+subject);
}

// TODO: create the class Teacher and a method teach

var him = new Teacher();

him.initialize("Adam", 45);
him.teach("Inheritance");
```

>
>解释一下代码吧 前面先创建person类，然后person类加一个原型initiallize
>
>然后创建teacher类，然后把person也当成teacher的一个属性或者说一个成员或者说一个原型加入进teacher类