# This is the program's UI module. The user interface and all interaction with the user (print and input statements)
# are found here
from functions import *


def menu():
    print('   1. Add a new expense or insert')
    print('add <sum> <category>')
    print('insert <day> <sum> <category>')
    print('   2. Modify expenses')
    print('remove <day>')
    print('remove <start day> to <end day>')
    print('remove <category>')
    print('   3. Display expenses with different properties')
    print('list')
    print('list <category>')
    print('list <category> [ < | = | >] <value>')
    print('   4. Filter expenses')
    print('filter <category>')
    print('filter <category> [ < | = | >] <value>')
    print('   5. Undo')
    print('undo')
    print('   6. Exit')
    print('exit')


def read_com():
    command = input('Enter your intention: ')
    if command == 'undo' or command == 'exit' or command == 'list':
        com = command
        args = ' '
    else:
        pos = command.find(' ')
        if pos == -1:
            print('Invalid request')
            return -1, -1
        com = command[:pos]
        args = command[pos + 1:]
        if com != 'add' and com != 'insert' and com != 'remove' and com != 'list' and com != 'filter' and com != 'undo' and com != 'exit':
            print('Invalid request')
            return -1, -1
    return com, args


def console():
    l = generate()
    lu = []
    lst = l.copy()
    lu.append(lst)
    while True:
        menu()
        com, args = read_com()
        try:
            if com == 'add':
                add_sum(l, args)
                lst = l.copy()
                lu.append(lst)
            elif com == 'insert':
                insert_sum(l, args)
                lst = l.copy()
                lu.append(lst)
            elif com == 'remove':
                modify_sum(l, args)
                lst = l.copy()
                lu.append(lst)
            elif com == 'list':
                for a in display_expenses(l, args):
                    print(a)
            elif com == 'filter':
                filter_expenses(l, args)
                lst = l.copy()
                lu.append(lst)
            elif com == 'undo':
                if len(lu) == 1:
                    l = []
                elif len(lu) == 0:
                    print('Already empty list')
                else:
                    l = undo(lu)
            elif com == 'exit':
                break
        except ValueError:
            print('Invalid request')


