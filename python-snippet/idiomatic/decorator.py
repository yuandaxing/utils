def logger(func) :
    def wrapper(*args, **kwargs) :
        print 'go into function', args, kwargs
        return func(*args, **kwargs)
    return wrapper

@logger
def my_func(x, y) :
    return x * y

my_func(2,3)
my_func(6, 9)

def stepper(start = 0, step = 1, stop = 1000) :
    _start = start
    while _start < stop:
        yield _start
        _start += step 

#generator expression
ex = (z * 5 for z in range(1, 100))
import itertools
itertools.chain([1,2], ['a', 'b'])
z =  itertools.combinations([1,2,3,4], 3)
z = itertools.permutations([1,2,3,4], 3)
listA = range(1, 5)
listB = [True, False, True, True]
f = itertools.compress(listA, listB)
f = itertools.count(10)
c = itertools.cycle('abcd')

str2 = 'aaaaaaabbbbbbbbaaaaccccccccc'
itertools.groupby(str2)
listC = [
    {'id':1, 'c' : 'd'},
    {'id':1, 'e' : 'f'},
    {'id':3, 'g' : 'h'},
    ]

print {k:list(v) for k,v in itertools.groupby(listC, 
                            key = lambda x : x['id'])}
 
reduce
filter
itertools.product('aaa', [1,2])
imap, ifilter, izip
class Swallow:
    def __init__(self, airspeed, color):
        """
        
        """
        self.airspeed = airspeed
        self.color = color
    

A = Swallow(1.0, 'red')
        
getattr(A, 'color')
getattr(A, 'airspeed')
getattr(A, 'unkown')
hasattr(A, 'color')
hasattr(A, 'airspeed')
hasattr(A, 'unkown')
setattr(A, 'color', 'white')
setattr(A, 'airspeed', 2.0)
setattr(A, 'unkown', 'fuck')
