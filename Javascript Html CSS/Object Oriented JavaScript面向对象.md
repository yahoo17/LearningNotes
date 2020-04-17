# Object Oriented JavaScript面向对象

------

JavaScript uses functions as classes to create objects using the `new` keyword. Here is an example:

```javascript
function Person(firstName, lastName) {
    // construct the object using the arguments
    this.firstName = firstName;
    this.lastName = lastName;

    // a method which returns the full name
    this.fullName = function() {
        return this.firstName + " " + this.lastName;
    }
}

var myPerson = new Person("John", "Smith");
console.log(myPerson.fullName());            // outputs "John Smith"
```

Creating an object using the `new` keyword is the same as writing the following code:

```javascript
var myPerson = {
    firstName : "John",
    lastName : "Smith",
    fullName : function()
    {
        return this.firstName + " " + this.lastName;
    }
}
```

The difference between the two methods of creating objects is that 

 the first method uses a class to define the object and then the `new` keyword to instantiate it

and the second method immediately creates an instance of the object.

## Exercise

Create a class called Person which accepts the name of a person as a string, and his/her age as a number. 

The Person class should have a method called `describe` which returns a string with the following syntax: "`name`, `age` years old". So for example, if John is 19 years old then the function `describe` of his object will return "John, 19 years old".

## Answer

```javascript

// TODO: create the Person class using a function
function Person(name,age)
{
    this.name=name;
    this.age=age;
    this.describe=function()
    {
		return this.name+", "+this.age+" years old";
		//注意题目中的空格
    }
}
var jack = new Person("Jack", 25);
var jill = new Person("Jill", 24);
console.log(jack.describe());
console.log(jill.describe());

```

