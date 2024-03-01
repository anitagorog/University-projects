
class Book:
    def __init__(self, book_id, author, title):
        self.id = book_id
        self.author = author
        self.title = title

    def __str__(self):
        return f"{self.id} - {self.title} by {self.author}"

    @property
    def get_id(self):
        return self.id

    @property
    def get_title(self):
        return self.title

    @property
    def get_au(self):
        return self.author

    def set_id(self, new):
        self.id = new

    def set_title(self, new):
        self.title = new

    def set_au(self, new):
        self.author = new
