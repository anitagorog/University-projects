from src.domain.book import Book
from src.domain.client import Client
from src.domain.rental import Rental
from src.repository.repo_books import BookRepo
from src.repository.repo_exception import DublicateItemException, DoesntExistException
from src.services.serv_books import ServBooks
from src.services.serv_clients import ServClients
from src.services.serv_rentals import ServRentals


def commands():
    print("Options: ")
    print("add, list, filter, update (-> books/clients)")
    print("rent, return, show")
    print("search (-> books/clients)")
    print("statistics")
    print("exit")


def book_fields():
    print("book id, title, author")


def client_fields():
    print("client id, name")


def stat():
    print("most rented books, most active clients, most rented author")


class Ui:
    def __init__(self):
        self.brep = BookRepo()
        self.servbook = ServBooks(self.brep)
        self.servclient = ServClients()
        self.servrent = ServRentals(self.brep)
        self.com = {"exit": exit, "add": self.add_s, "list": self.list_s, "filter": self.fil_s, "update": self.upd_s,
                    "rent": self.rent_b, "show": self.show, "return": self.return_b, "search": self.search_s,
                    "statistics": self.stat}

    def command(self):
        print(commands())
        c = input("Enter your intention: ")
        if c in self.com:
            self.com[c]()
        else:
            print("Invalid request")

    def add_s(self):
        s = input('Which do you intend to add -> book/client: ')
        if s == 'book':
            self.add_b()
        elif s == 'client':
            self.add_c()
        else:
            print("Invalid request")

    def add_b(self):
        title = input("Enter the title: ")
        author = input("Enter the author: ")
        isbn = input("Enter the isbn: ")
        bo = Book(isbn, author, title)
        try:
            self.servbook.try_add(bo)
        except DublicateItemException as a:
            print(a)

    def add_c(self):
        name = input("Enter the name: ")
        n_id = input("Enter the id: ")
        cl = Client(n_id, name)
        try:
            self.servclient.try_add_c(cl)
        except DublicateItemException as a:
            print(a)

    def list_s(self):
        s = input('Which would you like to see -> book/client: ')
        if s == 'book':
            self.list_b()
        elif s == 'client':
            self.list_c()
        else:
            print("Invalid request")

    def list_b(self):
        print(self.servbook.list_b())

    def list_c(self):
        print(self.servclient.list_c())

    def fil_s(self):
        s = input('From which would you like to delete -> book/client: ')
        if s == 'book':
            self.fil_b()
        elif s == 'client':
            self.fil_c()
        else:
            print("Invalid request")

    def fil_b(self):
        w = input('Enter the title you would like to delete: ')
        self.servbook.filter_b(w)

    def fil_c(self):
        w = input('Enter the name you would like to delete: ')
        self.servclient.filter_c(w)

    def upd_s(self):
        s = input('Which would you like to update -> book/client: ')
        if s == 'book':
            self.upd_b()
        elif s == 'client':
            self.upd_c()
        else:
            print("Invalid request")

    def upd_b(self):
        the = input('Enter the id of the book you would like to change: ')
        new = input('Enter the new title: ')
        self.servbook.update_b(the, new)

    def upd_c(self):
        the = input('Enter the id of the client: ')
        new = input('Enter the new name: ')
        self.servclient.update_c(the, new)

    def rent_b(self):
        r_id = input("Enter rent id: ")
        book = input("Enter book id: ")
        client = input("Enter client id: ")
        date = input("Enter the rented date(yyyy mm dd): ")
        rent = Rental(r_id, book, client, date, "pending")
        try:
            self.servrent.check_rent(rent)
        except (DoesntExistException, DublicateItemException) as a:
            print(a)

    def show(self):
        print(self.servrent.list_r())

    def return_b(self):
        r_id = input("Enter the rent id: ")
        date = input("Enter the returned date(yyyy mm dd): ")
        try:
            self.servrent.return_b(r_id, date)
        except DoesntExistException as a:
            print(a)

    def search_s(self):
        s = input('In which do you intend to search -> book/client: ')
        if s == 'book':
            self.search_b()
        elif s == 'client':
            self.search_c()
        else:
            print("Invalid request")

    def search_b(self):
        book_fields()
        f = input("Choose the field: ")
        if f == "book id":
            w = input("Enter the id: ")
            print(self.servbook.search_by_id(w))
        elif f == "title":
            w = input("Enter the title: ")
            print(self.servbook.search_by_title(w))
        elif f == "author":
            w = input("Enter the author: ")
            print(self.servbook.search_by_author(w))
        else:
            print("Invalid request")

    def search_c(self):
        client_fields()
        f = input("Choose the field: ")
        if f == "client id":
            w = input("Enter the id: ")
            print(self.servclient.search_by_id(w))
        elif f == "name":
            w = input("Enter the name: ")
            print(self.servclient.search_by_name(w))
        else:
            print("Invalid request")

    def stat(self):
        stat()
        s = input("Choose: ")
        if s == "most rented books":
            for b in self.servrent.most_books():
                print(b, ' ', self.servrent.most_books()[b])
        elif s == "most active clients":
            for b in self.servrent.most_clients():
                print(b, ' ', self.servrent.most_clients()[b])
        elif s == "most rented author":
            for b in self.servrent.most_author():
                print(b, ' ', self.servrent.most_author()[b])
        else:
            print("Invalid request")
