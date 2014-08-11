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
