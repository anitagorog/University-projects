import random
def insert_sort(l, step):
    '''

    Sorts a list using the insert sort method
    :param l: list of natural numbers
    :param step: natural number
    :return:
    A sorted list
    '''
    b = 0
    for k in range(1, len(l)):
        i = k-1
        while i >= 0 and l[i+1] < l[i]:
            c = l[i]
            l[i] = l[i+1]
            l[i+1] = c
            i = i-1
            b += 1
            if b % step == 0:
                print(l)
    return l

def stooge_sort(l, i, j, step, b):
    '''

    Sorts a list using the stooge sort method
    :param l: list of natural numbers
    :param i: natural number
    :param j: natural number
    :param step: natural number
    :param b: natural number
    :return:
    A sorted list
    '''
    b += 1
    if b % step == 0:
        print(l)
    if i >= j:
        return l
    if l[i] > l[j]:
        k = l[i]
        l[i] = l[j]
        l[j] = k
    if j-i+1 > 2:
        k = (j-i+1)//3
        stooge_sort(l, i, (j-k), step, b)
        stooge_sort(l, (i+k), j, step, b)
        stooge_sort(l, i, (j - k), step, b)

def menu():
    print('1. Generate a list of n random natural numbers')
    print('2. Sort the list using the insert sorting algorithm')
    print('3. Sort the list using the stooge sorting algorithm')
    print('4. Exit program')

def generate_list():
    n = input('n=')
    n = int(n)
    l = []
    for i in range(n):
        x = random.randint(0,100)
        l.append(x)
    return l

if __name__ == '__main__':
    while True:
        menu()
        choice = input('Choose your intention: ')
        if choice == '1':
            lst = generate_list()
            print(lst)
        elif choice == '2':
            try:
              if lst:
                step = input('step: ')
                step = int(step)
                l = lst.copy()
                print(insert_sort(l, step))
            except:
               print("not exist")
        elif choice == '3':
            try:
              if lst:
                b = 0
                step = input('step: ')
                step = int(step)
                l2 = lst.copy()
                print(stooge_sort(l2, 0, len(l2)-1, step, b))
            except:
                print("not exist")
        elif choice == '4':
            break
        else:
            print("Invalid")
