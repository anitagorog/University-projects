from a5 import *

import random


def menu():
    print('1. Read a list of complex numbers (in z = a + bi form) from the console')
    print('2. Display the entire list of numbers on the console')
    print('3. Length and elements of a longest subarray...')
    print('4. Exit program')


def menu2():
    print('1. Length and elements of a longest subarray of numbers having the same modulus')
    print("2. The length and elements of a maximum subarray sum, when considering each number's real part")


def get_real():
    '''
    Creates the real part of a complex number
    :return:
    An integer which is the real part of a complex number
    '''
    x = int(input('Get the real part of the number: '))
    return x


def get_img():
    '''
    Creates the imaginary part of a complex number
    :return:
    An integer which is the imaginary part of a complex number
    '''
    x = int(input('Get the imaginary part of the number: '))
    return x


def creates(l, k):
    '''
    Creates a complex number
    :param l: list with integers
    :param k: natural number
    :return:
    The list added with the real and the imaginary part of the created complex number
    '''
    l.append(get_real())
    l.append(get_img())
    return l, k+2


def displaylist(l):
    '''
    Prints list l
    :param l: list with integers
    :return:
    List l
    '''
    for i in range(0, len(l), 2):
        print(str(l[i]), " + i*", str(l[i+1]))


def display2(d):
    '''
    Prints dictionary d
    :param d: dictionary with integers
    :return:
    Dictionary d
    '''
    for i in range(0, len(d), 2):
        print(str(d[str(i)]), " + i*", str(d[str(i+1)]))


def printl(l, ma, q):
    '''
    Prints the needed part of a list l
    :param l: list with integers
    :param ma: natural number
    :param q: natural number
    :return:
    The needed part of a list l
    '''
    print('Maximum length: ', ma)
    print('Elements: ')
    for i in range(q-2*ma+2, q+2, 2):
        print(str(l[i]), " + i*", str(l[i+1]))


##def print1(l, ma, q):
    ##print('Maximum length: ', ma)
    ##print('Elements: ')
    ##for i in range(q - 2 * ma + 2, q, 2):
        ##print(str(l[i]), " + i*", str(l[i + 1]))


if __name__ == '__main__':
    l = None
    while True:
        menu()
        choice = input('Choose your intention: ')
        if not l:
            l = []
            k = 0
            d = {}
            while k < 20:
                m = random.randint(-9, 9)
                l.append(m)
                d[str(k)] = m
                k += 1
        if choice == '1':
            n = int(input('The number of complex numbers besides the already existing 10: '))
            n *= 2
            while k < (n+20):
                creates(l, k)
                x = str(k)
                d[x] = l[k]
                x = str(k + 1)
                d[x] = l[k + 1]
                k += 2
        elif choice == '2':
            print('Display from list:')
            displaylist(l)
            print('Display from dictionary: ')
            display2(d)
        elif choice == '3':
            menu2()
            ex = input('Choose your intention: ')
            if ex == '1':
                ma, q = prob1(l)
                printl(l, ma, q)
            elif ex == '2':
                ma, q = prob2(l)
                printl(l, ma, q)
            else:
                print("Invalid")
        elif choice == '4':
            break
        else:
            print("Invalid")
