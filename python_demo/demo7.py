class Server(object):
    
    def __init__(self,argc1=0,argc2=0,argc3=0):
        self.date=100
        self.name=10
    __slots__=('date','name')
    
    def get_name(self):
        return self.name
    def get_date(self):
        return self.date

m_instance=Server()
print('my name is %s,and my birth date is %s'%(m_instance.get_name(),m_instance.get_date()))


class myServer(Server):
    def __init__(self):
        self.age=17
    def get_age(self):
        print(self.age)

m_in=myServer()
m_in.get_age()