from texttable import Texttable

from src.service import Service


class Ui:
    def __init__(self):
        self.ser = Service()
        self.board = self.ser.rep.board
        self.n = 1

    def print_table(self):
        table = Texttable()
        for i in self.board:
            table.add_row(i)
        return table.draw()

    def save(self):
        self.ser.rep.save()

    def command(self):
        i = input('Intention: ')
        if i.startswith('place'):
            t = i.split(' ')
            try:
                if len(t) != 3:
                    raise Exception
                pat = t[1]
                nr = t[2].split(',')
                row = nr[0]
                col = nr[1]

                self.ser.place(pat, row, col)
                print(self.print_table())
            except:
                print('Invalid')
        elif i == 'save board.txt':
            self.ser.rep.save2()
            print(self.print_table())
        elif i == 'load board.txt':
            self.ser.rep.load2()
            print(self.print_table())
        elif i.startswith('tick'):
            if i == 'tick':
                self.ser.tick(self.n)
                print(self.print_table())
        else:
            print('Invalid2')

