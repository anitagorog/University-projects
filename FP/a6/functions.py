# The program's functions are implemented here. There is no user interaction in this file,
# therefore no input/print statements.
# Functions here
# communicate via function parameters, the return statement and raising of exceptions. 

import datetime
import random
types = ['housekeeping', 'food', 'transport', 'clothing', 'internet', 'others']


def generate():
    '''
    Generates 10 random expenses
    :return: a list containing 10 random possible dictionaries
    '''
    l = []
    for i in range(10):
        day = random.randint(1, 30)
        su = random.randint(1, 100)
        cate = random.choice(["housekeeping", "food", "transport", "clothing", "internet", "others"])
        l.append(create(day, su, cate))
    return l


def create(day, su, cate):
    '''
    Creates a dictionary of the input data elements
    :param day: natural number between 1 and 30
    :param su: natural number
    :param cate: string
    :return: a dictionary
    '''
    if day == 0:
        current_time = datetime.datetime.now()
        day = current_time.day
    else:
        day = int(day)
    if day > 30 or day < 1:
        raise ValueError
    su = int(su)
    if su < 1:
        raise ValueError
    return {"day": day, "amount": su, "type": cate}


def test_create():
    assert create(1, 2, 'f') == {"day": 1, "amount": '2', "type": 'f'}


def get_day(expense):
    '''
    Gets the element of a dictionary with the key day
    :param expense: dictionary
    :return: natural number
    '''
    return expense["day"]


def get_type(expense):
    '''
    Gets the element of a dictionary with the key type
    :param expense: dictionary
    :return: string
    '''
    return expense["type"]


def get_sum(expense):
    '''
    Gets the element of a dictionary with the key amount
    :param expense: dictionary
    :return: natural number
    '''
    return expense["amount"]


def set_day(expense, new_day):
    '''
    Sets the element of a dictionary with the key day
    :param expense: dictionary
    :param new_day: natural number
    :return: dictionary
    '''
    expense["day"] = new_day
    return expense


def set_sum(expense, new_sum):
    '''
    Sets the element of a dictionary with the key amount
    :param expense: dictionary
    :param new_sum: natural number
    :return: dictionary
    '''
    expense["amount"] = new_sum
    return expense


def set_type(expense, new_cat):
    '''
    Sets the element of a dictionary with the key type
    :param expense: dictionary
    :param new_cat: string
    :return: dictionary
    '''
    expense["type"] = new_cat
    return expense


def add_sum(l, args):
    '''
    Adds a new dictionary to the list
    :param l: list (of dictionaries)
    :param args: string
    :return: the list with the new wished dictionary
    '''
    pos = args.find(' ')
    su = args[:pos]
    cate = args[pos+1:]
    if cate in types:
        x = create(0, su, cate)
        l.append(x)
    else:
        raise ValueError


def test_add_sum():
    l = []
    args = '10 internet'
    add_sum(l, args)
    assert len(l) == 1
    assert l[0] == {"day": 3, "amount": 10, "type": 'internet'}


def insert_sum(l, args):
    '''
    Inserts a new dictionary to the list
    :param l: list (of dictionaries)
    :param args: string
    :return: the list with the new wished dictionary
    '''
    pos = args.find(' ')
    day = args[:pos]
    args2 = args[pos+1:]
    pos2 = args2.find(' ')
    su = args2[:pos2]
    cate = args2[pos2+1:]
    if cate in types:
        x = create(day, su, cate)
        l.append(x)
    else:
        raise ValueError


def test_insert_sum():
    l = []
    args = '25 10 internet'
    insert_sum(l, args)
    assert l[0] == {"day": 25, "amount": 10, "type": 'internet'}


def modify_sum(l, args):
    '''
    Removes certain elements from the list
    :param l: list (of dictionaries)
    :param args: string
    :return: the modified list
    '''
    try:
        x = args.isnumeric()
        if x is True:
            for expense in l:
                if get_day(expense) == int(args):
                    l.remove(expense)
        elif args.find("to") != -1:
            pos = args.find(' ')
            n1 = args[:pos]
            n1 = int(n1)
            args2 = args[pos+1:]
            pos2 = args2.find(' ')
            n2 = args2[pos2+1:]
            n2 = int(n2)
            k = 0
            while k < len(l):
                c = 1
                expense = l[k]
                for i in range(n1, n2+1):
                    if c == 1 and get_day(expense) == i:
                        l.remove(expense)
                        c = 0
                        k -= 1
                k += 1
        else:
            k = 0
            while k < len(l):
                expense = l[k]
                if get_type(expense) == args:
                    l.remove(expense)
                    k -= 1
                k += 1
    except ValueError:
        print('Invalid')


def test_modify_sum():
    l = [{"day": 25, "amount": 10, "type": 'internet'}]
    args = '25'
    modify_sum(l, args)
    assert l == []


def display_expenses(l, args):
    '''
    Shows the wished elements of the list
    :param l: list (of dictionaries)
    :param args: string
    :return: the wished elements of the list
    '''
    l_d = []
    if args == ' ':
        return l
    elif args.find(' ') == -1:
        for expense in l:
            if get_type(expense) == args:
                l_d.append(expense)
    elif args.find(' = ') != -1:
        pos = args.find(' = ')
        ty = args[:pos]
        su = args[pos+3:]
        su = int(su)
        for expense in l:
            if get_type(expense) == ty and get_sum(expense) == su:
                l_d.append(expense)
    elif args.find(' < ') != -1:
        pos = args.find(' < ')
        ty = args[:pos]
        su = args[pos+3:]
        su = int(su)
        for expense in l:
            if get_type(expense) == ty and get_sum(expense) < su:
                l_d.append(expense)
    elif args.find(' > ') != -1:
        pos = args.find(' > ')
        ty = args[:pos]
        su = args[pos+3:]
        su = int(su)
        for expense in l:
            if get_type(expense) == ty and get_sum(expense) > su:
                l_d.append(expense)
    else:
        raise ValueError
    return l_d


def filter_expenses(l, args):
    '''
    Keeps only certain elements of the list
    :param l: list (of dictionaries)
    :param args: string
    :return: the list with the kept elements
    '''
    if args.find(' ') == -1:
        if args in types:
            k = 0
            while k < len(l):
                expense = l[k]
                if get_type(expense) != args:
                    l.remove(expense)
                    k -= 1
                k += 1
        else:
            raise ValueError
    elif args.find(' = ') != -1:
        pos = args.find(' = ')
        ty = args[:pos]
        su = args[pos+3:]
        su = int(su)
        if ty in types:
            k = 0
            while k < len(l):
                expense = l[k]
                if get_type(expense) != ty or get_sum(expense) != su:
                    l.remove(expense)
                    k -= 1
                k += 1
        else:
            raise ValueError
    elif args.find(' < ') != -1:
        pos = args.find(' < ')
        ty = args[:pos]
        su = args[pos+3:]
        su = int(su)
        if ty in types:
            k = 0
            while k < len(l):
                expense = l[k]
                if get_type(expense) != ty or get_sum(expense) >= su:
                    l.remove(expense)
                    k -= 1
                k += 1
        else:
            raise ValueError
    elif args.find(' > ') != -1:
        pos = args.find(' > ')
        ty = args[:pos]
        su = args[pos+3:]
        su = int(su)
        if ty in types:
            k = 0
            while k < len(l):
                expense = l[k]
                if get_type(expense) != ty or get_sum(expense) <= su:
                    l.remove(expense)
                    k -= 1
                k += 1
        else:
            raise ValueError
    else:
        raise ValueError


def undo(lu):
    '''
    Undoes the last operation during the program
    :param lu: list of the modified lists
    :return: the anterior element of the list lu
    '''
    lu.remove(lu[-1])
    return lu[-1]

