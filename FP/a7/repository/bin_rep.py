import pickle


class Binary:
    def __init__(self, name="book.bin"):
        self.name = name
        self.l_books = self.load_file()

    def save_file(self, l_books):
        # w - write mode (overwrite), b - binary mode
        f = open(self.name, "wb")
        pickle.dump(l_books, f)
        f.close()

    def load_file(self):
        try:
            f = open(self.name, "rb")
            o = pickle.load(f)
            f.close()
            return o
        except EOFError:
            return []
        except IOError:
            print("Error")
