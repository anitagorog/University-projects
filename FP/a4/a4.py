import random
import sys


def consistent(lst, n, j):
    c = 0
    if j != lst[- 1]:
        c = 1
    if c == 1 and len(lst) < n:
        return 1
    else:
        return 0


def solution(l, n):
    d = l[-1]
    if len(l) == n and d != 0:
        return 1
    else:
        return 0


def output(l):
    l.append(0)
    print(l)


def backtracking_recursive(l, n):
    for d in range(-1, 2):

        if consistent(l, n, d) == 1:
            l.append(d)
            if solution(l, n) == 1:
                output(l)
                l.pop(-1)
                l.pop(-1)
            else:
                backtracking_recursive(l[:], n)
                l.pop(-1)


def backtracking_iterative(n):
    lst = [0]
    i = 1
    j = -1
    while i <= n:
        ad = ''
        k = j
        while k <= 1:
            if k != lst[i-1]:
                lst.append(k)
                ad = 'X'
                i = i + 1
                j = -1
                break
            else:
                k = k + 1
        if ad == '':
            i = i - 1
            j = lst[-1] + 1
            del lst[-1]

        if i == n + 1:
            if lst[n] == 0:
                print(lst)
            i = i - 1
            j = lst[-1] + 1
            del lst[-1]
        if i == 0:
            return


def naive_version(l, k):
    maximum = -99999999
    for i in range(0, k-3):
        for j in range(i+1, k-2):
            for a in range(j+1, k-1):
                for b in range(a+1, k):
                    if l[b]-l[a]+l[j]-l[i] > maximum:
                        maximum = l[b]-l[a]+l[j]-l[i]
                        m = b
                        n = a
                        p = j
                        q = i
                        print(l[m], l[n], l[p], l[q])
    print("The sum = ", l[m]-l[n]+l[p]-l[q])


def dynamic_programme(l):
    # the list should have at least 4 elements
    if len(l) < 4:
        exit(-1)

    # initialize to `-sys.maxsize`
    x = [-sys.maxsize] * (len(l) + 1)
    y = [-sys.maxsize] * len(l)
    z = [-sys.maxsize] * (len(l) - 1)
    t = [-sys.maxsize] * (len(l) - 2)

    # x stores the maximum value of `l[m]`
    for i in reversed(range(len(l))):
        x[i] = max(x[i + 1], l[i])
    print(x)

    # y stores the maximum value of `l[m] - l[n]`
    for i in reversed(range(len(l) - 1)):
        y[i] = max(y[i + 1], x[i + 1] - l[i])
    print(y)

    # z stores the maximum value of `l[m] - l[n] + l[p]`
    for i in reversed(range(len(l) - 2)):
        z[i] = max(z[i + 1], y[i + 1] + l[i])
    print(z)

    # t stores the maximum value of `l[m] - l[n] + l[p] - l[q]`
    for i in reversed(range(len(l) - 3)):
        t[i] = max(t[i + 1], z[i + 1] - l[i])
    print(t)

    # maximum value at t[0]
    print("The sum =", t[0])


if __name__ == '__main__':
    n = int(input("n = "))
    n *= 2
    l = [0]
    print("Backtracking recursive: ")
    print(backtracking_recursive(l, n))
    print("Backtracking iterative: ")
    print(backtracking_iterative(n))

    lst = [30, 5, 15, 18, 30, 40]
    k = 6
    print(lst)
    print("The naive version")
    naive_version(lst, k)
    print("The dynamic programme")
    dynamic_programme(lst)
    k = int(input("The length of your array(>=4): "))
    lst = []
    for i in range(k):
        x = random.randint(0, 100)
        lst.append(x)
    print("The array: ", lst)
    if k < 4:
        print("Not valid")
    else:
        print("The naive version")
        naive_version(lst, k)
    print("The dynamic programme")
    dynamic_programme(lst)
