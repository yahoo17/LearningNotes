class Student(object):

    @property
    def score(self):
        return self._score

    @score.setter
    def score(self, value):
        if not isinstance(value, int):
            raise ValueError('score must be an integer!')
        if value < 0 or value > 100:
            raise ValueError('score must between 0 ~ 100!')
        self._score = value

a=Student()
a.score=10
print(a.score)

class Screen(object):
    @property
    def width(self):
        return self._width
    @width.setter
    def width(self,value):
        if value>0:
            self._value=value
        
    @property 
    def height(self):
        return self._height
    @height.setter
    def height(self,value):
        if value>150:
            self._height=value
    
    @property
    def resolution(self):
        return self._resolution
    def resolution(self,value):
        self._resolution=value
# 测试:
s = Screen()
s.width = 1024
s.height = 768
print('resolution =', s.resolution)
if s.resolution == 786432:
    print('测试通过!')
else:
    print('测试失败!')
