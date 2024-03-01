from src.domain import Board


class Repo:
    def __init__(self, filename='file.txt', filename2='board.txt'):
        self.bo = Board()
        self.board = self.bo.board
        self.filename = filename
        self.filename2 = filename2
        self.patterns = self.load()

    def load(self):
        self.patterns = {}
        lines = []
        f = open(self.filename, 'rt')
        lines = f.readlines()
        f.close()
        for line in lines:
            cur = line.split(';')
            lst = []
            c2 = cur[1].split(',')
            for c in c2:
                lst.append(c.strip())
            # pat = {cur[0]: lst}
            self.patterns[cur[0]] = lst
        return self.patterns

    def save(self):
        f = open(self.filename, 'wt')
        for p in self.patterns:
            st = str(p)
            f.write(st)
        f.close()

    def save2(self):
        f2 = open(self.filename2, 'wt')
        for b in self.board:
            for i in b:
                if i == '':
                    st = '0,'
                else:
                    st = str(i) + ','
                f2.write(st)
            f2.write('\n')
        f2.close()

    def load2(self):
        lines = []
        f = open(self.filename2, 'rt')
        lines = f.readlines()
        f.close()
        i = -1
        k = 0
        for line in lines:
            i += 1
            cur = line.split(',')

            # k = 0
            for j in range(0, len(self.board[i])):
                if cur[j].strip() == '0':
                    self.board[i][j] = ' '
                else:
                    self.board[i][j] = cur[j]
                # k += 1

