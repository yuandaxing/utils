class IronSuite :
    pass

class WarMachine :
    pass

class IronMan :
    class __metaclass__(type) :
        def __new__(cls, name, bases, attrs) :
            if attrs.has_key('env') and attrs['env'] == 'hostile' :
                attrs['suite'] = WarMachine() 
            else :
                attrs['suite'] = IronSuite()
            return type.__new__(cls, name, bases, attrs)

class WarMan(IronMan) :
    env = 'hostile'

ironman = WarMan()
print ironman.suite


#writing metaclass
class Meta(type) :
    pass

class Final(object):
    __metaclass__ = Meta

#
class Meta(type) :
    def __new__(meta, name, supers, attrs) :
        print 'meta.new execution hook'
        return type.__new__(meta, name, supers, attrs)

    def __init__(class_, name, supers, attrs) :
        print 'meta.init execution hook'
