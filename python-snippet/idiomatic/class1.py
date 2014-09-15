class Class1(object):
    f1, f2 = 20, 30
    def __init__(self) :
        self.f1 = 90
        print self.f1, self.f2

    def __call__(self) :
        print self.f1, self.f2 
       
    def func1(self) :
        print self.f1+self.f2 

class Class2(Class1) :
    def __init__(self) :
        super(Class2, self).__init__()
        print 'hello, world'

c = Class2()
c()
c.func1()
