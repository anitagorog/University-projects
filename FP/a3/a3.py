import random
import timeit

def insert_sort(l):
    '''

    Sorts a list using the insert sort method
    :param l: list of natural numbers
    :return:
    A sorted list
    '''
    for k in range(1, len(l)):
        i = k-1
        while i >= 0 and l[i+1] < l[i]:
            c = l[i]
            l[i] = l[i+1]
            l[i+1] = c
            i = i-1
    return l

def stooge_sort(l, i, j):
    '''

    Sorts a list using the stooge sort method
    :param l: list of natural numbers
    :param i: natural number
    :param j: natural number
    :return:
    A sorted list
    '''
    if i >= j:
        return l
    if l[i] > l[j]:
        k = l[i]
        l[i] = l[j]
        l[j] = k
    if j-i+1 > 2:
        k = (j-i+1)//3
        stooge_sort(l, i, (j-k))
        stooge_sort(l, (i+k), j)
        stooge_sort(l, i, (j - k))

def menu():
    print('1. Generate a list of n random natural numbers')
    print('2. Sort the list using the insert sorting algorithm')
    print('3. Sort the list using the stooge sorting algorithm')
    print('4. Best case')
    print('5. Worst case')
    print('6. Average case')
    print('7. Exit')

def generate_list(n):
    '''

    Generates a list with n elements
    :param n: natural number
    :return:
    A list with n elements
    '''
    l = []
    for i in range(n):
        x = random.randint(0, 100)
        l.append(x)
    return l

def generate_a_reversly_sorted_list(n):
    '''

    Returns a list with numbers in a descending order
    :param n: natural number
    :return:
    A list with numbers in a descending order
    '''
    l = []
    for i in range(n):
        if i == 0:
            x = random.randint(0, 100)
        else: x = random.randint(0, l[i-1])
        l.append(x)
    return l

def generate_a_sorted_list(n):
    '''

        Returns a list with numbers in an ascending order
        :param n: natural number
        :return:
        A sorted list
    '''
    l = []
    for i in range(n):
        if i == 0:
            x = random.randint(0, 100)
        else:
            x = random.randint(l[i - 1], 100)
        l.append(x)
    return l

if __name__ == '__main__':
    while True:
        menu()
        choice = input('Choose your intention: ')
        if choice == '1':
            n = input('length=')
            n = int(n)
            lst = generate_list(n)
            print(lst)
        elif choice == '2':
            try:
              if lst:
               l = lst.copy()
               insert_sort(l)
            except:
               print("not exist")
        elif choice == '3':
            try:
              if lst:
                l2 = lst.copy()
                print(stooge_sort(l2, 0, len(l2) - 1))
            except:
                print("not exist")
        elif choice == '4':
            n = input("length: ")
            n = int(n)
            b = 1
            lb = generate_a_sorted_list(n)
            lb2 = generate_list(n)
            print("Best case for insert sort")
            print(lb)
            print("Best case for stooge sort")
            print(lb2)
            while (b < 6):
                print("For length ", n, "the time is: ")
                print("For insert sort ")
                starttime = timeit.default_timer()
                print("The start time is :", starttime)
                insert_sort(lb)
                print("The time difference is :", timeit.default_timer() - starttime)
                print("For stooge sort ")
                starttime = timeit.default_timer()
                print("The start time is :", starttime)
                stooge_sort(lb2, 0, len(lb2) - 1)
                print("The time difference is :", timeit.default_timer() - starttime)
                b += 1
                n *= 2
                lb = generate_a_sorted_list(n)
                lb2 = generate_list(n)
        elif choice == '5':
            n = input("length: ")
            n = int(n)
            b = 1
            lw = generate_a_reversly_sorted_list(n)
            lw2 = generate_a_sorted_list(n)
            print("Worst case for insert sort")
            print(lw)
            print("Worst case for stooge sort")
            print(lw2)
            while (b < 6):
                print("For length ", n, "the time is: ")
                print("For insert sort ")
                starttime = timeit.default_timer()
                print("The start time is :", starttime)
                insert_sort(lw)
                print("The time difference is :", timeit.default_timer() - starttime)
                print("For stooge sort ")
                starttime = timeit.default_timer()
                print("The start time is :", starttime)
                stooge_sort(lw2, 0, len(lw2) - 1)
                print("The time difference is :", timeit.default_timer() - starttime)
                b += 1
                n *= 2
                lw = generate_a_reversly_sorted_list(n)
                lw2 = generate_a_sorted_list(n)
        elif choice == '6':
            n = input("length: ")
            n = int(n)
            b = 1
            lst = generate_list(n)
            while(b < 6):

                print("For length ", n, "the time is: ")
                l = lst.copy()
                print("For insert sort ")
                starttime = timeit.default_timer()
                print("The start time is :", starttime)
                insert_sort(l)
                print("The time difference is :", timeit.default_timer() - starttime)
                l2 = lst.copy()
                print("For stooge sort ")
                starttime = timeit.default_timer()
                print("The start time is :", starttime)
                stooge_sort(l2, 0, len(l2) - 1)
                print("The time difference is :", timeit.default_timer() - starttime)
                b += 1
                n *= 2
                lst = generate_list(n)
        elif choice == '7':
            break
        else:
            print("Invalid")
