#函数

f=abs

#变量可以指向函数


def add(x,y,f):
    return f(x)+f(y)

print(add(-10,10,f))

print(sorted([-36,5,-323,4324,555]))
print(sorted([-36,5,-323,4324,555],key=abs))

def lazy_sum(*args):
    def sum():
        ax = 0
        for n in args:
            ax = ax + n
        return ax
    return sum
f = lazy_sum(1, 3, 5, 7, 9)
print(f())

#print( cal_sum([-36,5,-323,4324,555]) )

