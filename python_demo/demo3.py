from collections import Iterable 
r=[3,15,30,19,30,30]
# for i in r:
#     if i%5==0:
#         print(i)

d = {'a': 1, 'b': 2, 'c': 3}

for key in d:
    print(key)

print(isinstance([1,2,3],Iterable))

print(isinstance("1231",Iterable))

print(isinstance(123,Iterable))

for x,y in [(1,1),(2,4),(3,9)] :
    print(x,y,x+y)

def findMax(L):
    max=L[0]
    for x in L:
        if x>max:
            max=x
    return max

L=(100,20,3,900,3123,33)
it=iter(L)
while True:
    try:
        x=next(it)
        print("hh",x)
    except StopIteration:
        break

    