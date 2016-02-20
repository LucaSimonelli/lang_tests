import math

"""
luca@kitt:~/mytests/python$ python
Python 2.7.6 (default, Mar 22 2014, 22:59:56) 
[GCC 4.8.2] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> import binomial
>>> binomial.bnc(67,1)
67L
>>> binomial.bnc(67,2)
2211L
>>> binomial.bnc(66,2)
2145L
>>> binomial.bnc(66,3)
45760L
>>>
"""

def bnc(n,k):
    """ Non optimized function to calculate the binomial coefficient given n
    and k. 
    """
    a = math.factorial(n);
    b = math.factorial(k);
    c = math.factorial(n-k);
    return a // (b*c)


def range_bnc(n, k_start, k_end):
    """ Given n and a range of k values, it returns the sum of all the binomial
    coefficients calculated with each k value.
    """
    k = k_start
    res = 0
    while (k <= k_end):
        res += bnc(n,k)
        k+=1
    return res
