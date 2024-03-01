# Solve the problem from the third set here
def perfect(n):
    """

    Returns if an n natural number is perfect
    :param n: natural number
    :return:
    True if n is equal to the sum of its divisors, except itself or False otherwise
    """
    s=1
    for i in range(2,n):
        if n%i==0 :
            s+=i
    if s==n:
        return True
    return False

def largest_perfect_number(n):
    """

    Returns the largest perfect number smaller than an n natural number
    :param n: natural number
    :return:
    The largest perfect number smaller than n or "not exist" if such a number does not exist
    """
    n=n-1
    while perfect(n)==False and n!=1:
        n=n-1
    if n==1:
        return "not exist"
    else: return n

if __name__ == '__main__':
    print(largest_perfect_number(7))
