
class Student(object):
    def __init__(self,name,score):
        self.__name=name
        self.__score=score
    def print_score(self):
        print('%s: %s' % (self.__name, self.__score))
    def set_score(self,score):
        self.__score=score
  


a=Student("yanhao",99)
a.print_score()
a._Student__name=123
print(a._Student__name)

a.set_score(100)
a.print_score()

class Animal(object):
    def run(self):
        print("Animal can run")

class Dog(Animal):
    def run(self):
        print("Dog can run")

class Cat(Animal):
     def run(self):
        print("Cat can run")

a=Dog()
a.run()
b=Cat()
b.run()
print(isinstance(a,Animal))
print(isinstance(a,Dog))
print(isinstance(a,Cat))
print(type(a))
if type(123)==str:
    print('the same type')
else:
    print('no the same')

#print(dir('ABC'))
print(len('ABC'))

from types import MethodType
s.se