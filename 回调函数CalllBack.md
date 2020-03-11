# Callbacks回调函数

------

>
>
>这是我比较感兴趣的部分，因为我的主要语言就是C++ 而在C++里面，回调函数常常伴随着函数指针，C形式的函数指针比较复杂，所以想看看JavaScript是怎么实现的；

Callbacks in JavaScript are functions that are passed as arguments to other functions. This is a very important feature of  asynchronous programming, and it enables the function that receives the  callback to call our code when it finishes a long task, while allowing  us to continue the execution of the code.

主要意思就是异步编程，比如一个函数需要在5 s之后执行另外一个函数，这时候总不能一直占着CPU资源吧。就好比，服务员5分钟后来端厨师炒好的菜。不管厨师有没有炒好，来端菜这个回调函数都会执行



For example:

```javascript
var callback = function() {
    console.log("Done!");
}

setTimeout(callback, 5000);
```

This code waits 5 seconds and prints out "Done!" when the 5 seconds  are up. Note that this code will not work in the interpreter because it  is not designed for handling callbacks.

It is also possible to define callbacks as anonymous functions, like so:

```javascript
setTimeout( function() {console.log("Done!");}, 5000);
```

Like regular functions, callbacks can receive arguments and be executed more than once. 

## Exercise

Define a function called `callback` which receives an argument and prints it out.

## Answer

```javascript
function useCallback(callback)
{
    callback(1);
    callback(2);
    callback(3);
}

function callback(sentence) {
    console.log(sentence);
}


useCallback(callback);
```

输出

>1
>2
>3