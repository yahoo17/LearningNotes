初始化列表里初始化const数据成员
class A
{
public:
	A():increment(10){}
private:
	const int increment;
}
#include "Time.h"
class Employee
{
public:
	Employee(Time t1, Time t2):birthTime(t1),hireTime(t2)
	{
		
	}
private:
	const Time birthTime;
	const Time hireTime;

};
初始化列表的顺序是按声明的顺序来的