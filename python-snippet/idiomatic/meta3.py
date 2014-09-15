class A(object) :
    a = 'i am a string.'

#equal 
A = type('A', (object,), {'a': 'i am a string.'})

class Meta(type) :
    def __call__(self) :
        print 'Enter meta.__call__:', self
        obj = type.__call__(self)
        print 'Exit meta.__call__:', obj
        return obj

    def __new__(metacls, name, bases, dictionary) :
        print 'Enter meta.__new__:', metacls, name, bases, dictionary
        dictionary['__call__'] = Meta.__call__
        newClass = type.__new__(metacls, name, bases, dictionary)
        print 'Exit meta.__new__:', newClass
        print newClass

    def __init__(cls, name, bases, dictionary) :
        print 'Enter meta.__init__:', cls, name, bases, dictionary
        super(Meta, cls).__init__(name, bases, dictionary)
        print 'Exit Meta.__init__'

print 'Create class A'
A = Meta('A', (object, ), {})

print
print 'Create instance of class A'
z = A()
