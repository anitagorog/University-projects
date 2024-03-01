import unittest

from src.repo import Repo
from src.service import Service


class Test(unittest.TestCase):
    def test(self):
        ser = Service()
        board = ser.rep.board
        board[3][3] = 'x'
        ser.tick(1)
        self.assertTrue(board[2][3] == '')

