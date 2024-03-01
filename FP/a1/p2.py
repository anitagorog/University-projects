# Solve the problem from the second set here
def prime(n):
    """

    Returns if a number is prime or not
    :param n: non-null natural number
    :return:
    True if the given number is prime and False if it is not
    """
    for i in range(2,n//2):
        if n%i==0:
            return False
    return True

def twin_prime(n):
    """

    Returns the pair of twin prime numbers immediately larger than non-null natural number n
    :param n: non-null natural number
    :return:
    The pair of twin prime numbers immediately larger n
    """
    p2=0
    p1=n
    while p2==0:
       p1=p1+1
       if prime(p1)==True :
         if prime(p1+2)==True:
            p2=p1+2
    return p1,p2

if __name__ == '__main__':
    print(twin_prime(13))

