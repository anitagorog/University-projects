import datetime

from src.repository.repo_books import BookRepo
from src.repository.repo_clients import ClientRepo
from src.repository.repo_exception import DublicateItemException, DoesntExistException
from src.repository.repo_rents import RentalRepo
from src.services.serv_books import ServBooks


class ServRentals:
    def __init__(self, bser):
        self.repo = RentalRepo()
        self.b_ser = bser
        self.books = self.b_ser.l_books
        self.c_repo = ClientRepo()
        self.rents = self.repo.l_rentals

    def save_r(self):
        self.repo.l_rentals = self.rents

    def check_rent(self, rental):
        if not self.book_exist(rental.book_id):
            raise DoesntExistException("Book does not exist")
        if not self.client_exist(rental.client_id):
            raise DoesntExistException("Client not on the list")
        if self.book_available(rental.book_id):
            raise DoesntExistException("Book not available")
        try:
            self.check_time(rental.rented_date)
        except Exception:
            raise DoesntExistException("Date not valid")
        try:
            self.repo.add(rental)

        except DublicateItemException as a:
            raise DublicateItemException(a)
#        if self.book_exist(rental.book_id) and self.client_exist(rental.client_id) \
#                and not self.book_available(rental.book_id) and self.check_time(rental.rented_date):
#            self.repo.add(rental)
#        else:
#            raise Exception

    def book_exist(self, b_i):
        def same_id(book):
            return book.id == b_i
        print('\n'.join(map(str, self.books)))
        return any(map(same_id, self.books))

    def book_available(self, b_i):
        def av_id(rent):
            return rent.book_id == b_i and rent.returned_date == "pending"
        return any(map(av_id, self.rents))

    def client_exist(self, c_i):
        def same_id(client):
            return client.client_id == c_i
        return any(map(same_id, self.c_repo.l_clients))

    def list_r(self):
        return '\n'.join(map(str, self.rents))

    def return_b(self, the_id, date):
        try:
            for r in self.rents:
                if r.rental_id == the_id:
                    try:
                        self.check_ret_time(r.rented_date, date)
                    except Exception:
                        raise DoesntExistException
                    r.set_returned_date(date)
        except DoesntExistException:
            raise DoesntExistException("Date not valid")

    def check_ret_time(self, rent, ret):
        y = rent.split(' ')
        x = ret.split(' ')
        if len(x) != 3:
            raise Exception
        for i in range(3):
            if not x[i].isnumeric():
                raise Exception
        if int(x[0]) > int(y[0]) or int(x[1]) > int(y[1]) or int(x[2]) > int(y[2]):
            return True
        else:
            raise Exception

    def check_time(self, time):
        x = time.split(' ')
        if len(x) != 3:
            raise Exception
        for i in range(3):
            if not x[i].isnumeric():
                raise Exception
        if x[0] < '0' or int(x[0]) > 2023:
            raise Exception
        if x[1] < '0' or int(x[1]) > 12:
            raise Exception
        if x[2] < '0' or int(x[2]) > 31:
            raise Exception
        return True

    def check_sub_time(self, rent, ret):
        y = rent.split(' ')
        if ret == 'pending':
            current = datetime.datetime.now()
            return current.day - int(y[2])
        x = ret.split(' ')
        return int(x[2]) - int(y[2])

    def most_books(self):
        d = {}
        for b in self.b_repo.l_books:
            k = str(b)
            d[k] = 0
        l = list(d.keys())
        for r in self.rents:
            k = str(r.book_id)
            for i in l:
                if i.startswith(k):
                    d[i] += 1
        sol = dict(sorted(d.items(), key=lambda x: x[1], reverse=True))
        return sol

    def most_clients(self):
        d = {}
        for b in self.c_repo.l_clients:
            k = str(b)
            d[k] = 0
        l = list(d.keys())
        for r in self.rents:
            k = str(r.client_id)
            for i in l:
                if i.startswith(k):
                    d[i] += self.check_sub_time(r.rented_date, r.returned_date)
        sol = dict(sorted(d.items(), key=lambda x: x[1], reverse=True))
        return sol

    def most_author(self):
        d = self.most_books()
        l = list(d.keys())
        d2 = {}
        for b in l:
            sp = b.split(' ')
            n = str(sp[4] + ' ' + sp[5])
            d2[n] = 0
        for k in d:
            for a in d2:
                if k.find(a) != -1:
                    d2[a] += d[k]
        sol = dict(sorted(d2.items(), key=lambda x: x[1], reverse=True))
        return sol


if __name__ == '__main__':
    def sort_dict_by_value(d, reverse=False):
        return dict(sorted(d.items(), key=lambda x: x[1], reverse=reverse))

    print("Original dictionary elements:")
    colors = {'Red': 6, 'Green': 2, 'Black': 5, 'White': 2, 'Pink': 4}
    print(colors)
    print(colors.items())
    print(sorted(colors.items(), key=lambda x: x[1]))
    print(colors.get('Red'))
    print(colors['Red'])

    print("\nSort (ascending) the said dictionary elements by value:")
    print(sort_dict_by_value(colors))

    print("\nSort (descending) the said dictionary elements by value:")
    print(sort_dict_by_value(colors, True))

    x = "isbn10 - Mirror by Emma Pierce"
    z = 'h'
    y = x.split(' ')
    name = str(y[4]+' '+y[5])
    print(name)
    print(x.find("Emma Pierce"))
    for c in colors:
        print(c)

    def mf(e):
        return e['Red']
    co = [{'Red': 6, 'Green': 2}, {'Red': 2, 'Green': 2}]
    co.sort(key=mf)
    print(co)
    # print('/n'.join([x, y]))

    k = '3 2'
    print(k.isnumeric())
    lc = k.split()
    print(lc[1] > '3')

