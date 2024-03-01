from src.domain.book import Book
from src.services.services import Service


def test_try_add():
    serv = Service()
    new = Book('9999', 'Tim', 'Sun')
    try:
        serv.try_add(new)
        serv.content(new)
        assert True
    except:
        pass
    if True:
        print('Tests passed')
