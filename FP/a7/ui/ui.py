from src.domain.book import Book
from src.services.services import Service


def commands():
    print("Options: add, list, filter, undo, exit")


class Ui:
    def __init__(self):
        self.serv = Service()
        self.com = {"exit": exit, "add": self.add_b, "list": self.list_p, "filter": self.fil_b, "undo": self.undo_b}

    def command(self):
        print(commands())
        c = input("Enter your intention: ")
        if c in self.com:
            self.com[c]()
        else:
            print("Invalid request")

    def add_b(self):
        title = input("Enter the title: ")
        author = input("Enter the author: ")
        isbn = input("Enter the isbn: ")

        bo = Book(isbn, author, title)

        try:
            self.serv.try_add(bo)
        except Exception:
            print("Error")

    def list_p(self):
        print(self.serv.list_b())

    def fil_b(self):
        w = input('Enter the word you would like to delete: ')
        self.serv.filter_b(w)

    def undo_b(self):
        try:
            self.serv.try_un()
        except Exception:
            print("No steps back left")
