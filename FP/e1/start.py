from src.service import Service
from src.ui import Ui


def main():
    ui = Ui()
    print(ui.print_table())
    while True:
        ui.command()


main()
