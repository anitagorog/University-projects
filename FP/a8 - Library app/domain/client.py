
class Client:
    def __init__(self, client_id, name):
        self.client_id = client_id
        self.name = name

    def __str__(self):
        return f"{self.client_id} - {self.name}"

    @property
    def get_name(self):
        return self.name

    @property
    def get_id(self):
        return self.client_id

    def set_name(self, new):
        self.name = new

    def set_id(self, new):
        self.client_id = new
