class foo :
    pass

class foobase:
    def hello(self) :
        print 'hello, world'

foo.__bases__ += (foobase, )

f = foo()
f.hello()

class barbase :
    def a(self) :
        print 'hello'

class bar :
    def a(self) :
        print 'bar'

b = bar()
b.a()

f = getattr(barbase, 'a') 
setattr(bar, 'a', f.im_func)
c = bar()
c.a()

import types 

def MixIn(pyClass, mixInClass, makeAncestor=0): 
   if makeAncestor: 
     if mixInClass not in pyClass.__bases__: 
        pyClass.__bases__ = (mixInClass,) + pyClass.__bases__ 
   else: 
     # Recursively traverse the mix-in ancestor 
     # classes in order to support inheritance 
     baseClasses = list(mixInClass.__bases__) 
     baseClasses.reverse() 
     for baseClass in baseClasses: 
        MixIn(pyClass, baseClass) 

     # Install the mix-in methods into the class 
     for name in dir(mixInClass): 
        if not name.startswith('__'): 
        # skip private members 
           member = getattr(mixInClass, name) 
           if type(member) is types.MethodType: 
               member = member.im_func 
           setattr(pyClass, name, member) 
