from src.repo import Repo


class Service:
    def __init__(self):
        self.rep = Repo()

    def place(self, pat, row, col):
        row = int(row)
        col = int(col)
        if pat not in self.rep.patterns:
            raise Exception
        move = self.rep.patterns[pat]
        len = 0
        for x in move:
            if x != 'n':
                len += 1
            elif x == 'n':
                break
        k = 0
        for i in range(row, row+len):
            for j in range(col, col+len):
                if move[k] == 'x':
                    if self.rep.board[i][j] == 'x':
                        raise Exception
                    self.rep.board[i][j] = 'x'
                k += 1
            k += 1

    def tick(self, n):
        '''
        Makes the new generation
        :param n: integer
        :return:
        '''
        # n = how many generations
        for c in range(n):
            for i in range(1, len(self.rep.board)-1):
                # we iterate through the board and check how many neighbours they have that makes them 'die' or 'alive'
                k = 0
                f = 0
                # we count regarding the live cells in k
                # we count regarding the live cells in f
                for j in range(1, len(self.rep.board[i])-1):
                    if self.rep.board[i][j] == self.rep.board[i-1][j-1]:
                        k += 1
                    if self.rep.board[i][j] == self.rep.board[i-1][j]:
                        k += 1
                    if self.rep.board[i][j] == self.rep.board[i-1][j+1]:
                        k += 1
                    if self.rep.board[i][j] == self.rep.board[i+1][j-1]:
                        k += 1
                    if self.rep.board[i][j] == self.rep.board[i+1][j]:
                        k += 1
                    if self.rep.board[i][j] == self.rep.board[i+1][j+1]:
                        k += 1
                    if self.rep.board[i][j] == self.rep.board[i][j-1]:
                        k += 1
                    if self.rep.board[i][j] == self.rep.board[i][j+1]:
                        k += 1

                    if self.rep.board[i][j] == '' and self.rep.board[i-1][j-1] == 'x':
                        f += 1
                    if self.rep.board[i][j] == '' and self.rep.board[i-1][j] == 'x':
                        f += 1
                    if self.rep.board[i][j] == '' and self.rep.board[i-1][j+1] == 'x':
                        f += 1
                    if self.rep.board[i][j] == '' and self.rep.board[i+1][j-1] == 'x':
                        f += 1
                    if self.rep.board[i][j] == '' and self.rep.board[i+1][j] == 'x':
                        f += 1
                    if self.rep.board[i][j] == '' and self.rep.board[i+1][j+1] == 'x':
                        f += 1
                    if self.rep.board[i][j] == '' and self.rep.board[i][j-1] == 'x':
                        f += 1
                    if self.rep.board[i][j] == '' and self.rep.board[i][j+1] == 'x':
                        f += 1
# when needed change
                    if self.rep.board[i][j] == 'x':
                        if k < 2 or k > 3:
                            self.rep.board[i][j] = ''
                    else:
                        if f == 2:
                            self.rep.board[i][j] = 'x'

