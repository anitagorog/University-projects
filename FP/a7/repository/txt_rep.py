from src.domain.book import Book


class FileRepo:
    def __init__(self, file_name="file_rep.txt"):
        self._file_name = file_name
        # load from the file
        self.l_books = self.load_file()

    def load_file(self):
        # t - text file mode, r - reading
        self.l_books = []
        ls = []
        try:
            fin = open(self._file_name, "rt")
            ls = fin.readlines()
            fin.close()
        except IOError:
            pass
        for li in ls:
            current = li.split(",")
            new = Book(current[0].strip(), current[1].strip(), current[2].strip())
            self.l_books.append(new)
        return self.l_books

    def save_file(self, l_books):
        # t - text file mode, w - writing (rewrite the file every time)
        fo = open(self._file_name, "wt")
        for book in l_books:
            bo_s = str(book.isbn) + "," + str(book.author) + "," + str(book.title) + "\n"
            fo.write(bo_s)
        fo.close()
