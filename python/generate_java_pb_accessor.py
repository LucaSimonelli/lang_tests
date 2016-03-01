import re

def underscore(name):
  name = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
  #print name
  return re.sub('([a-z0-9])([A-Z])', r'\1_\2', name)

def generate_java_pb_accessor(name):
  #print underscore(name)
  fields = underscore(name).lower().split('_')
  fields = map(lambda x: x[:1].upper() + x[1:], fields)
  return ''.join(fields)

mynames = [
         "AAaAAaA",
         "AAaAAaAA",
         "AAaAAaAAAa",
         "AAA",
         "AA",
         "A",
         "a",
         "aA",
         "aaA",
         "aAA",
         "aAaAaA",
         ""
         ]
for s in mynames:
    print s
    print generate_java_pb_accessor(s)
    print
