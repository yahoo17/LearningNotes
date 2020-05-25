# new to py
import math
print(abs(1))
n1=255
n2=1000
print(hex(n1))
print("hex(n2)\n")
def dec_to_hex(x):
    if x:
        return (hex(x))

print(dec_to_hex(n2))

def my_abs(x):
    if x>=0:
        return x
    else:
        return -x

print(my_abs(100))
print(my_abs(-100))

def move(x,y,step,angle=0):
    nx=x+step*math.cos(angle)
    ny=y-step*math.sin(angle)
    return nx,ny

def quadratic(a,b,c):
    temp=math.sqrt(b*b-4*a*c)
    x1=(-b+temp)/2/a
    x2=(-b-temp)/2/a
    return x1,x2

print(quadratic(1,2,1))
print(quadratic(1,0,-1))

def power(x,n=2):
    if n>1:
        return power(x,n-1)*x
    else: 
        return x

print(power(2))


def enroll(name,gender):
    #xie ru mou ge di fang
    print("name:",name)
    print("gender:",gender)

enroll("yanhao","nan")

def add_end(L=[]):
    L.append("END")
    return L
L=[1,2,3]
add_end(L)
print(L)
L2=[3,4,5]
add_end(L2)
print(L2)

print(add_end())
print(add_end())
print(add_end())

def add_end2(L=None):
    if L is None:
        L=[]
    L.append("END")
    return L
print(add_end2())
print(add_end2())
print(add_end2())

def cal(numbers):
    sum=0
    for n in numbers:
        sum=sum+n*n
    return sum

print(cal([1,2,3,4]))

def change_cal(*numbers):
    sum=0
    for n in numbers:
        sum+=n
    return sum
print(change_cal(1,4,4,1))

# def person(name,age,**kw):
#     list=[]
#     # if 'city' in kw:
#     #     list.append(kw.city)
#     print(name,age,list,kw)



# def person2(name,age,*,city,phone):
#     print(name,age,city,job)


# person2('Michael',30)
# person2('Bob',35,city='Beijing',phoneNumber='10000')
# extra_info={'city':'Beijing','PhoneNumber':'136213123'}
# person2('Jack',24,**extra_info)

# person2('Michael',30)
# person2('Bob',35,city='Beijing',phoneNumber='10000')
# extra_info={'city':'Beijing','PhoneNumber':'136213123'}
# person2('Jack',24,**extra_info)

def f1(a,b,c=0,*arg,**kw):
    print("必选参数a,b=",a,b)
    print("默认参数",c)
    print("可变参数 好像是个list",arg)
    print("kw",kw)
# 定义默认参数要牢记一点：默认参数必须指向不变对象！

#可变参数 一般就是list

#关键字参数 组装成一个dict
 
#命名关键字参数 要限制关键字参数的名字，就可以用命名关键字参数，
# 例如，只接收city和job作为关键字参数。这种方式定义的函数如下：
# def person(name, age, *, city, job):
#print(name, age, city, job)

#在Python中定义函数，可以用必选参数、
# 默认参数、可变参数、关键字参数和命名关键字参数，
# 这5种参数都可以组合使用。但是请注意，
# 参数定义的顺序必须是：必选参数、默认参数、可变参数、命名关键字参数和关键字参数。
f1(10,20,100,[1,2,3,4])

tuple1=(1,2,3,4,5)
dict1={'name':"yanhao","id":2013}
print(tuple1,"\n",dict1)



