def foo2(cls, x) :
    print 'foo2 is class = %s' %  (cls, )
    print x

class ClassMethod(object) :
    def __init__(self, function) :
        print 'class method __init__() called '
        self.f = function

    def __get__(self, instance, owner = None) :
        print '\t__get__() called '
        print '\tINFO:self = %s, instance = %s, owner = %s' % (self, instance, owner)
        def temp(x) :
            print 'i am temp function '
            return self.f(owner, x)
        return temp 


class Class2(object) :
    method = ClassMethod(foo2)

class Class3(Class2) :
    pass 

if __name__ == '__main__':  
    ins = Class2()  
    print("ins.method = %s, Class2.method = %s, Class21.method = %s" % (ins.method, Class2.method, Class3.method))  
    ins.method('abc')  
    Class2.method('xyz')  
    Class3.method('asdf')  










