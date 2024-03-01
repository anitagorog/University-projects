from src.repository.repo_clients import ClientRepo
from src.repository.repo_exception import DublicateItemException


class ServClients:
    def __init__(self):
        self.repo = ClientRepo()
        self.clients = self.repo.l_clients

    def content_c(self, client):
        # checks if two clients have the same id
        def same_id(cl):
            return cl.client_id == client.client_id
        return any(map(same_id, self.clients))

# it checks if it was already added, if not it adds to the others
    def try_add_c(self, client):
        if self.content_c(client):
            raise DublicateItemException("Client already on the list")
        self.clients.append(client)

# returns the clients from the repo, in different lines
    def list_c(self):
        return '\n'.join(map(str, self.clients))

# filters the list of clients, removes what is needed to
    def filter_c(self, n):
        # returns False if the one we want to remove is found
        def not_exist(x):
            return not x.name.startswith(n)
        self.clients = list(filter(not_exist, self.clients))

# updates a client's name with a new one
    def update_c(self, the_id, new):
        for c in self.clients:
            if c.client_id == the_id:
                c.set_name(new)

    def search_by_id(self, the_id):
        for c in self.clients:
            if c.client_id == the_id:
                return c
        return "Not found"

    def search_by_name(self, name):
        for c in self.clients:
            if c.name == name:
                return c
        return "Not found"
