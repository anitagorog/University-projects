import math


def modulus(l, k):

    '''

    Calculates the modulus of a complex number from list l
    :param l: list with integers
    :param k: natural number
    :return:
    The modulus of a complex number from list l

    '''

    x1 = math.sqrt(l[k]*l[k]+l[k+1]*l[k+1])
 ## x2 = math.sqrt(d[str(k)] * d[str(k)] + d[str(k + 1)] * d[str(k + 1)])
 ## x1 == x2
    return x1


def prob1(l):
    '''
    Finds the length and the position of a last the element of the longest subarray of numbers having the same modulus
    :param l: list with integers
    :return:
    Length and the position of a last the element of the longest subarray of numbers having the same modulus
    '''
    ma = 1
    p = 1
    q = -1
    a = modulus(l, 0)
    for i in range(2, len(l), 2):
        ##print(a)
        ##print(' ')
        if a == modulus(l, i):
            p += 1
            print(a, 'p')
        else:
            p = 1
        if p > ma:
            ma = p
            q = i
        a = modulus(l, i)
    return ma, q
## We can do the same with the dictionary
## we just have to convert i to a string when referring to an element


def prob2(l):
    '''
    Finds the length and the position of the last element of a maximum subarray sum, when considering each number's real part
    :param l: list with integers
    :return:
    The length and the position of the last element of a maximum subarray sum, when considering each number's real part
    '''
    s = 0
    ma = -999999
    length = 0
    ml = 0
    q = -1
    for i in range(0, len(l)-1, 2):
        if s + l[i] >= 0:
            s += l[i]
            length += 1
        else:
            s = 0
            length = 0
        if ma < s:
            ma = s
            ml = length
            q = i
    return ml, q
## We can do the same with the dictionary
## we just have to convert first i to a string when referring to an element

##print(prob1([2, 4, 3, 2, 2, 3]))