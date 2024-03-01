
class Rental:
    def __init__(self, rental_id, book_id, client_id, rented_date, returned_date):
        self.rental_id = rental_id
        self.book_id = book_id
        self.client_id = client_id
        self.rented_date = rented_date
        self.returned_date = returned_date

    def __str__(self):
        return f"{self.rental_id} - {self.book_id} by {self.client_id}: from {self.rented_date} to {self.returned_date}"

    def set_returned_date(self, new):
        self.returned_date = new
