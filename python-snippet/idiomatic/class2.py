class A(object) :
    a = 0
    def set(self) :
        self.a = 10
        return self.a

class B(A) :
    a = 2
    def f1(self) :
        super(B, self).set()
    

b = B()
print dir(b)
print super(B, b).set()
print b.a
