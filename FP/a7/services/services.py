from src.repository.bin_rep import Binary
from src.repository.rep import MemoryRepository
from src.repository.txt_rep import FileRepo


class Service:
    def __init__(self):
        self.repo = MemoryRepository()
        # to switch between the repos we have to write here above which we would like to use
        self.books = self.repo.l_books
        self.undo = []

# checks if the book was already added, it returns True if not, False otherwise
    def content(self, book):
        # checks if two books have the same isbn
        def same_isbn(bo):
            return bo.isbn == book.isbn

        return any(map(same_isbn, self.books))

# it checks if it was already added, if not it adds to the others
    def try_add(self, book):
        if self.content(book):
            raise Exception("Book already added")
        self.undo.append(self.books.copy())
        self.books.append(book)

    def list_b(self):
        self.repo.save_file(self.books)
        return '\n'.join(map(str, self.books))

    def filter_b(self, w):
        def not_exist(x):
            return not x.title.startswith(w)
        self.undo.append(self.books)
        self.books = list(filter(not_exist, self.books))

    def try_un(self):
        if not self.undo:
            raise Exception
        self.books = self.undo.pop()
