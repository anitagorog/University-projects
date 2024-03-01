from src.repository.repo_books import BookRepo
from src.repository.repo_exception import DublicateItemException


class ServBooks:
    def __init__(self, rep):
        # self.repo = BookRepo()
        self.repo = rep
        self.books = self.repo.l_books

    def content(self, book):
        # checks if two books have the same isbn
        def same_id(bo):
            return bo.id == book.id

        return any(map(same_id, self.books))

# it checks if it was already added, if not it adds to the others
    def try_add(self, book):
        # if self.content(book):
        #    raise DublicateItemException("Book already added")
        # self.books.append(book)
        # self.repo.save_b(self.books)
        self.repo.try_addr(book)

# returns the books from the repo, in different lines
    def list_b(self):
        return '\n'.join(map(str, self.books))

# filters the list of books, removes what is needed to
    def filter_b(self, w):
        # returns False if the one we want to remove is found
        def not_exist(x):
            return not x.title.startswith(w)
        self.books = list(filter(not_exist, self.books))

# updates a book with a new title
    def update_b(self, the_id, new):
        for b in self.books:
            if b.id == the_id:
                b.set_title(new)

    def search_by_id(self, the_id):
        for b in self.books:
            if b.id == the_id:
                return b
        return "Not found"

    def search_by_title(self, title):
        for b in self.books:
            if b.title == title:
                return b
        return "Not found"

    def search_by_author(self, author):
        l = []
        for b in self.books:
            if b.author == author:
                k = str(b)
                l.append(k)
        if l:
            return l
        else:
            return "Not found"
