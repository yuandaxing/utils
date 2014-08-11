d = {}
exec ''' 
def synthetic_spam(z) :
    return z*z + 1
''' in d
print d.keys()
spam = d['synthetic_spam']
print spam(3)

def spam(self, x) :
    return 'hello spam(%s).' % x

def eggs(self) :
    return 'hello egges().'

d = dict(spam = spam, 
         eggs = eggs)
SyntheticClass = type( 'SyntheticClass',
                       (), d )
obj = SyntheticClass()
print obj.spam(7), obj.eggs()
