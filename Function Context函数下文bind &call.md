# Function Context函数下文bind &call

------

Functions in JavaScript run in a specific context, and using the `this` variable we have access to it. 

浏览器中的所有标准功能都在Window上下文下运行。 在对象或类下定义的函数（另一个函数）将使用在其内创建对象的上下文。但是，我们也可以在运行时（在执行函数之前或同时）更改函数的上下文。

### Binding a method to an object

To bind a function to an object and make it an object method, we can use the `bind` function. Here is a simple example:

```javascript
var person = {
    name : "John"
};

function printName()
{
    console.log(this.name);
}
```

Obviously, we are not able to call `printName()` without associating the function with the object `person`. To do this we must create a bound method of the function printName to person, using the following code:

```javascript
var boundPrintName = printName.bind(person);
boundPrintName();    // prints out "John"
```

### Calling a function with a different context

我们可以使用call和apply函数来调用函数，就像它绑定到对象一样。 调用函数和Apply函数之间的区别仅在于它们如何接收其参数-调用函数首先接收this参数，然后接收函数的参数，而apply函数首先接收this参数，并接收参数数组 传递给函数，作为函数的第二个参数。

For example, let's call `printName` with `person` as the context using the `call` method:

```javascript
printName.call(person);      // prints out "John"
```

### call/apply vs bind

 call/apply and bind之间的区别在于，绑定返回的新函数与旧函数相同，只是新函数中的this值现在是绑定到的对象。 call / apply将此函数作为绑定对象来调用该函数，但是它不会返回return新函数或更改原始函数，而是使用不同的值来调用它。

For example:

```javascript
var boundPrintName = printName.call(person);    //boundPrintName gets printName's return value (null)
boundPrintName();                               //doesn't work because it's not a function, it's null

printName.bind(person);                         //returns a new function, but nothing is using it so it's useless
printName();                                    //throws error because this.name is not defined
```

Think of `call` as executing the return value of `bind`.

For example:

```javascript
printName.call(person);     //is the same as
printName.bind(person)();   //executes the function returned by bind
```

Or think of `bind` returning a shortcut to `call`.

For example:

```javascript
var boundPrintName = printName.bind(person); //is the same as
var boundPrintName = function()
{
    printName.call(person);
}
```

## Exercise

Create bound copies of printFullName and printDetails to person called boundPrintFullName and boundPrintDetails.

## Answer

```javascript
var person = {
    firstName : "John",
    lastName : "Smith",
    age : 23
};

function printFullName()
{
    console.log(this.firstName + " " + this.lastName);
}

function printDetails()
{
    console.log(this.firstName + " is " + this.age + " years old");
}

// TODO: create bound copies of printFullName and printDetails.
var boundPrintFullName=printFullName.bind(person);
var boundPrintDetails=printDetails.bind(person);

boundPrintFullName();
boundPrintDetails();

```

```javascript

var person={
    name:"yanhao",
    age:"20",
    
}
function printName()
{
    console.log(this.name);
}
function printAge()
{
    console.log(this.age);
}
//111111
var a=printName.bind(person);
a();
var b=printAge.bind(person);
b();
//222
printName.bind(person)();
printAge.bind(person)();
//333
printName.call(person); 
printAge.call(person);


> "yanhao"
> "20"
> "yanhao"
> "20"
> "yanhao"
> "20"

```

>
>
>总结理解：bind会返回一个新的函数 接不接受是你的事情 不接受的话可以在后面加括号来调用（情况2） 接受的话用个var来接受，后面可以通过这个var来调用（情况1）
>
>​					call就像一次性的东西一样（情况3）

