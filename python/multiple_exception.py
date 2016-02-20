class MyExc1(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

class MyExc2(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

try:
    raise MyExc1("test")
except (MyExc2, MyExc1):
    print "MyExc2 cought"
