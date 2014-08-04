for i in [0, 1, 2, 3, 4, 5]:
    print i**2

for i in range(6) :
    print i**2

for i in xrange(7) :
    print i**2

colors = ['red', 'green', 'blue',
          'yellow']

print '\n\r'
for i in range(len(colors)) :
    print colors[i]
print '\n\r'
for color in colors :
    print color

print '\n\r'
for i in range(len(colors)-1, -1, -1) :
    print colors[i]

print '\n\r'
for color in reversed(colors) :
    print color


for i in range(len(colors)) :
    print i, '--->', colors[i]

print '\n\n'

for i, color in enumerate(colors) :
    print i, '---->', color

names = ['raymond', 'rachel', 'matthew']

n = min(len(names), len(colors))
for i in range(n) :
    print names[i], '---->', colors[i]


for name, color in zip(names, colors) :
    print name, '----->', color 


for color in sorted(colors) :
    print color 

for color in sorted(colors, reverse = True) :
    print color

print '\r\n'

def compare_length(c1, c2) :
    if len(c1) < len(c2) :
        return -1
    if len(c1) > len(c2) :
        return 1
    return 0

print sorted(colors, cmp = compare_length)

print sorted(colors, key=len)


#call a function until a sentinel value

blocks = []
while True :
    block = f.read(32)
    if block == '' :
        break
    blocks.append(block)

'''
partial is a high function
'''
blocks = []
for block in iter(partial(f.read, 32), '') :
    blocks.append(block)


def find(seq, target) :
    found = False
    for i , value in enumerate(seq) :
        if value == target :
            found = True
            break

    if not Found :
        return -1
    return 1


def find(seq, target) :
    for i, value in enumerate(seq) :
        if value == target :
            break
    else :
        return -1
    return i

dictionary = {'matthew' : 'blue', 
              'rachel' : 'green',
              'raymond' : 'red' }
#looping over dictionary keys
for k in dictionary :
    print k


for k in dictionary.keys() :
    if k.startswith('r') :
        del d[k]

#looping over a dictionary keys and values

for k in dictionary :
    print k, '---->', d[k]

for k, v in dictionary.items() :
    print k, '---->', v

for k, v in dictionary.iteritems() :
    print k, '--------->', v

#construct a dictionary from pairs
#zip and izip, one is for list, one is for iterator
d = dict(izip(names, colors))

#counting with dictionaries
d = {}
for color in colors :
    if color not in d :
        d[color] = 0
    d[color] += 1

for color in colors :
    d[color] = d.get(color, 0) + 1
#setdefault is a good method 
d = defaultdict(int)
for color in colors :
    d[color] += 1



#grouping with dictionaries
names = ['raymond', 'rachel', 'matthew',
         'roger', 'betty', 'melissa',
         'judith', 'charlie']
for name in names :
    key = len(name)
    if key not in d :
        d[key] = []
    d[key].append(name)

for name in names:
    key = len(names)
    d.setdefault(key, []).append(name)

d = defaultdict(list)
for name in names :
    key = len(name)
    d[key].append(name)


# is a dictionary popitem() atomic
while d :
    key, value = d.popitem()
    print key, '---->', value


#Linking dictionary
default = {'color' : 'red',
           'user' : 'guest'}
parser = argparse.ArgumentParser()
parser.add_argument('-u', '--user')
parser.add_argument('-c', '--color')
namespace = parser.parse_args([])
command_line_args = {k:v for k, v in 
                     vars(namespace).items() if v}
d = defaults.copy()
d.update(os.environ)
d.update(command_line_args)
d = Chainmap(command_line_args, os.environ, defaults)


#improving clarity
#clarity function calls with keyword arguments
twitter_search('@obama', False, 20, True)

twitter_search('@obama', retweets = False,
               numtweets = 20, popular = True)


doctest.testmod()
(0, 4)
doctest.testmod()
TestResults(failed=0, attempted=4)
TestResults = namedtuple('TestResults', 
                         ['failed', 'attempted'])


#unpacking sequence
p = 'first', 'second', 'third'
first, second, third = 'first', 'second', 'third'


#updating multiple state variables

x, y = y, x
def fibonacci(n) :
    x, y = 0, 1
    for i in range(n) :
        print x
        x, y = y, x+y

#simultaneous state updates
temp_x = x + dx * t
temp_y = y + dy * t
temp_dx = influence(m, x, y, dx, dy, partial = 'x')
temp_dy = influence(m, x, y, dx, dy, partial = 'y')
x = temp_x
y = temp_y
dx = temp_dx
dy = temp_dy

x, y, dx, dy = (x + dx * t, 
                y + dy * t,
                influence(m, x, y, dx, dy, partial = 'x'),
                influence(m, x, y, dx, dy, partial = 'y'))


#concatenating strings
names = ['raymond', 'rachel', 'matthew',
         'roger', 'betty', 'melissa',
         'judith', 'charlie']

s = names[0]
for name in names[1:]:
    s += ', ' + name 
print s

print ', '.join(names)

#update sequence
del names[0]
names.pop(0)
names.insert(0, 'mark')
names = deque(names)
del names[0]
names.popleft()
names.insertleft('mark')


#decorators and context managers
#help seperate business logical and manager code
def web_lookup(url, saved = {}) :
    if url in saved :
        return saved[url]
    page = urllib.urlopen(url).read()
    saved[url] = page
    return page


@cache
def web_lookup(url) :
    return urllib.urlopen(url).read()

#caching decorators

def cache(func):
    saved = {}
    @wraps(func)
    def newfunc(*args) :
        if args in saved :
            return saved[*args]
        result = func(*args)
        saved[args] = result
        return result
    return newfunc

#factor-out temporary contexts
old_context = getcontext().copy()
getcontext().prec = 50
print Decimal(355) / Decimal(113)
setcontext(old_context)

with localcontext(Context(prec = 50)) :
    print Decimal(355) / Decimal(113)

#open close file
with open('data.txt') as f :
    data = f.read()

#how to use locks
lock = threading.Lock()
lock.acquire()
try :
    print 'critical section 1'
    print 'critical section 2'
finally :
    lock.release()

with lock :
    print 'critical section 1'
    print 'critical section 2'

#remove file
try :
    os.remove('somefile.temp')
except OSError :
    pass

with ignored(OSError)
    os.remove('somefile.temp')

@Contextmanager
def ignored(*exceptions) :
    try :
        yield
    except exceptions :
        pass

with open('help.txt', 'w') as f :
    oldstdout = sys.stdout
    sys.stdout = f
    try :
        help(pow) 
    finally :
        sys.stdout = oldstdout

with open('help.txt', 'w') as f :
    with redirect_stdout(f) :
        help(pow)

result = []
for i in range(10) :
    s = i ** 2
    result.append(s)
print sum(result)

print sum([i ** 2 for i in range(10)])
#or xrange
