import random


class Book:
    def __init__(self, isbn, author, title):
        self.isbn = isbn
        self.author = author
        self.title = title

    def __str__(self):
        return f"{self.title} by {self.author} - isbn:{self.isbn}"

    def get_isbn(self):
        return self.isbn

    def get_author(self):
        return self.author

    def get_title(self):
        return self.title

    def set_i(self, n):
        self.isbn = n

    def set_a(self, n):
        self.author = n

    def set_t(self, n):
        self.title = n


au_first = ["Anthony", "Alexander", "Emma", "Ezra"]
au_last = ["Levine", "Raven", "Hope", "Pierce"]

titles = ["Crave", "Apple", "Pineapple", "Mother", "Father", "Sister", "Brother", "Family", "Glass", "Mirror"]


def rand_au():
    x = random.randint(0, 3)
    y = random.randint(0, 3)
    return au_first[x] + ' ' + au_last[y]


def rand_b():
    b_l = []
    for i in range(1, 11):
        b = Book("isbn" + str(i), rand_au(), titles[i-1])
        b_l.append(b)
    return b_l

