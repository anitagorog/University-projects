from src.tests import test_try_add
from src.ui.ui import Ui


def main():
    menu = Ui()
    while True:
        menu.command()


if __name__ == '__main__':
    test_try_add()
    main()
