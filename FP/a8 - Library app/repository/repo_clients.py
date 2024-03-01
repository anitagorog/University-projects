import random
from src.domain.client import Client


class ClientRepo:
    def __init__(self):
        self.l_clients = self.set_c()

    def set_c(self):
        self.l_clients = []
        for i in range(1, 11):
            c = Client("id" + str(i), rand_n())
            self.l_clients.append(c)
        return self.l_clients


first = ["Anthony", "Alexander", "Emma", "Ezra"]
last = ["Cromwell", "Ashley", "Daughter", "West"]


def rand_n():
    x = random.randint(0, 3)
    y = random.randint(0, 3)
    return first[x] + ' ' + last[y]
