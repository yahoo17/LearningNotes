// C++11.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
using namespace std;
int main()
{
    int a = 1;
    int b = 2;
    int c = 3;
    auto temp =[](int &a, int &b, int &c) { cout << a << b << c << endl;  a++; b++; c++; };
    temp(a, b, c);
    std::cout << a << b << c << endl;
    /*auto temp = []() ->int { cout << "hello world " << endl; return 0; };
    cout << temp();*/

    /*auto stringfunc = []()->string { cout << " this is stringFunc\n"; return "return VALUE"; };
    cout << stringfunc();*/

    /*auto lambda = [] {printf(" auto usage;"); };
    lambda();*/


}

