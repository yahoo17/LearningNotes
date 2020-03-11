# Json的学习

 **JSON**(JavaScript Object Notation) 是一种轻量级的数据交换格式。 易于人阅读和编写。



 **JSON**采用完全独立于语言的文本格式，但是也使用了类似于C语言家族的习惯（包括C, C++, C#, Java, JavaScript, Perl, Python等）。 这些特性使JSON成为理想的数据交换语言。 



参考

[Json的官方文档](https://www.json.org/json-zh.html)

页面有中文版的选项



然后Json解析器有许多，我看了[Tencent的RapidJson](http://rapidjson.org/zh-cn/)

当然，在前面Json官方文档的底部，有各种语言的json解析器

![1582383757039](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\1582383757039.png)

可以看到rapidjson在第六个





## 它是一个高效的 C++ JSON 解析／生成器，提供 SAX 及 DOM 风格 API



这里贴一个例子

关于Dom 那应该是前端html的知识

```C++
用法一览

此简单例子解析一个 JSON 字符串至一个 document (DOM)，对 DOM 作出简单修改，最终把 DOM 转换（stringify）至 JSON 字符串。
// rapidjson/example/simpledom/simpledom.cpp`
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
 
using namespace rapidjson;
 
int main() {
    // 1. 把 JSON 解析至 DOM。
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    Document d;
    d.Parse(json);
 
    // 2. 利用 DOM 作出修改。
    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);
 
    // 3. 把 DOM 转换（stringify）成 JSON。
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
 
    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
    return 0;
}

```

