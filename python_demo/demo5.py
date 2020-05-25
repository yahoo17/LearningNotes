#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'a test module'


__author__ ='Michael Yan'
import sys

def test():
    args=sys.argv
    if len(args)==1:
        print('Hello world')
    elif len(args)==2:
        print('Hello ,%s'%args[1])
    else:
        print("tooo many arguments")

if __name__=='__main__':
    test()



class Student(object):
    def __init__(self,name,score):
        self.__name=name
        self.score=score
    def print_score(self):
        print('%s: %s' % (self.__name, self.score))
    def set_score(self,score):
        self.score=score
  
#有些时候，你会看到以一个下划线开头的实例变量名，
# 比如_name，这样的实例变量外部是可以访问的，
# 但是，按照约定俗成的规定，当你看到这样的变量时，
# 意思就是，“虽然我可以被访问，但是，请把我视为私有变量，不要随意访问”。

a=Student("yanhao",99)

a.print_score()
a.__name=100
a.print_score()