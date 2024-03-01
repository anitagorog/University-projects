import random
from src.domain.book import Book


class MemoryRepository:
    def __init__(self):
        self.l_books = self.set_b()

    def set_b(self):
        self.l_books = []
        for i in range(1, 11):
            b = Book("isbn" + str(i), rand_au(), titles[i - 1])
            self.l_books.append(b)
        return self.l_books

    def save_file(self, l_books):
        self.l_books = l_books


au_first = ["Anthony", "Alexander", "Emma", "Ezra"]
au_last = ["Levine", "Raven", "Hope", "Pierce"]

titles = ["Crave", "Apple", "Pineapple", "Mother", "Father", "Sister", "Brother", "Family", "Glass", "Mirror"]


def rand_au():
    x = random.randint(0, 3)
    y = random.randint(0, 3)
    return au_first[x] + ' ' + au_last[y]

