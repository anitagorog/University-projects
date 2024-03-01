def minimum(n):
    """

    Returns for the number n the minimal natural number m formed with the same digits
    :param n: natural number
    :return:
    The minimal natural number m formed with the digits of number n
    """
    l = []
    m = n
    while m > 0:
        l.append(m % 10)
        m = m // 10
    for i in range(0, len(l) - 1):
        for j in range(i + 1, len(l)):
            if l[i] > l[j]:
                c = l[i]
                l[i] = l[j]
                l[j] = c
    for i in range(0, len(l)):
        m = m * 10 + l[i]
    return m


if __name__ == '__main__':
    print(minimum(656))
# Solve the problem from the first set here
def minimum(n):
    """

    Returns for the number n the minimal natural number m formed with the same digits
    :param n: natural number
    :return:
    The minimal natural number m formed with the digits of number n
    """
    l=[]
    m=n
    while m>0:
        l.append(m%10)
        m=m//10
    for i in range(0,len(l)-1):
        for j in range(i+1,len(l)):
            if l[i]>l[j]:
                c=l[i]
                l[i]=l[j]
                l[j]=c
    for i in range(0,len(l)):
        m=m*10+l[i]
    return m
if __name__ == '__main__':
    print(minimum(656))
