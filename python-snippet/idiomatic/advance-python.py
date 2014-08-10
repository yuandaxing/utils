A = set(['a', 'b', 'c'])
B = set(['c', 'd', 'k'])
print A & B


my_dict = {'a' : 1, 'b' : 3, 'c' : 5}
result = {k : v * 2 for k, v in my_dict}

my_dict.iterkeys()
my_dict.itervalues()
my_dict.itervalues()

[lambda x : x * 2 (y) for y in my_dict.itervalues()]

my_first_list = ['a', 'b', 'c', 'd']
my_second_list = [1, 2, 3, 4]
zip(my_first_list, my_second_list)

enumerate(my_first_list)
enumerate(my_first_list, 3) # (3, a), (4, b) ...
my_third_list = [7, 8, 9, 10, 11]

zip(my_first_list, my_second_list, my_third_list)

str1 = 'abcdef'
str2 = '123456'
zip(str1, str2)
[''.join(s) for s in zip(str1, str2)]
d1 = dict(zip(str1, str2))
dict((k * 3, v) for k, v in d1.iteritems())
filter(lambda x : x % 2 == 0, my_third_list)
any(lambda x : x % 13 == 0, my_third_list)

choice = [True, True, False, False]
any(choice)
all(choice)
mylist = range(1, 5)
imylist = xrange(1,5)

map(lambda x: x * 3, mylist)
import itertools
itertools.imap
itertools.izip
def multi_closure(x) :
    def wrapper(y) :
        return x * y
    return wrapper

def donot_panic_func(func) :
    def wrapper(some_attri) :
        try :
            func(some_attri)
        except :
            print too bad functions
    return wrapper 

catch_it = donot_panic_func(bad_function_from_lib)
catch_it(10)

@donot_panic_func
bad_function_from_lib(some_attri)

def decorators_func(func) :
    def wrapper(*args, **kwrags) :
        'do something before'
        value = func(*args, **kwargs) 
        'do something after'
        return value
    return wrapper

def logger(func) :
    def wrapper(*args, **kwargs) :
        print 'go into function', args, kwargs
        return func(*args, **kwargs)
    return wrapper

@logger
def my_func(x, y) :
    return x * y

type(class_name, parent_tuple_class, attribute)
