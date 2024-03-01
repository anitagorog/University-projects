import unittest

from src.domain.book import Book
from src.domain.client import Client
from src.services.serv_books import ServBooks
from src.services.serv_clients import ServClients


class Tests(unittest.TestCase):

    def test_books(self):
        self.serv = ServBooks()
        new = Book('isbn20', 'Tim', 'Sun')
        self.assertFalse(self.serv.try_add(new))
        self.assertTrue(self.serv.content(new))
        self.assertTrue(self.serv.filter_b('Crave') is None)
        self.assertTrue(self.serv.update_b('isbn6', 'Me') is None)

    def test_clients(self):
        self.serv = ServClients()
        new = Client('id20', 'Tim')
        self.assertFalse(self.serv.try_add_c(new))
        self.assertTrue(self.serv.content_c(new))
        self.assertTrue(self.serv.filter_c('Emma') is None)
        self.assertTrue(self.serv.update_c('id6', 'Me') is None)


if __name__ == '__main__':
    unittest.main()
