import datetime

from src.domain.rental import Rental
from src.repository.repo_books import BookRepo
from src.repository.repo_clients import ClientRepo
from src.repository.repo_exception import DublicateItemException


class RentalRepo:
    def __init__(self):
        self.reb = BookRepo()
        self.rec = ClientRepo()
        self.l_rentals = self.set_r()

    def content(self, rental):
        def same_id(re):
            return re.rental_id == rental.rental_id
        return any(map(same_id, self.l_rentals))

    def add(self, rental):
        if self.content(rental):
            raise DublicateItemException("Rent already on the list")
        self.l_rentals.append(rental)

    def remove(self, rent_id):
        def not_exist(x):
            return not x.rental_id.startswith(rent_id)
        self.l_rentals = list(filter(not_exist, self.l_rentals))

    def set_r(self):
        self.l_rentals = []
        t = datetime.datetime.now()
        for i in range(10):
            x = Rental(str(i), self.reb.l_books[i].id, self.rec.l_clients[i].client_id, str(t.year) + ' ' + str(t.month)
                       + ' ' + str(t.day), 'pending')
            self.l_rentals.append(x)
        return self.l_rentals
