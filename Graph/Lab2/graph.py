from copy import deepcopy


class DirectedGraph:
    def __init__(self, vertices, edges):
        self.__vertices = []
        self.__edges = []
        self.__outbound = {}
        self.__inbound = {}
        self.__costs = {}

        for vertex in vertices:
            self.add_vertex(vertex)

        for edge in edges:
            self.add_edge(edge[0], edge[1], edge[2])

    def get_vertices(self):
        return self.__vertices

    def get_outbound(self):
        return self.__outbound

    def get_inbound(self):
        return self.__inbound

    def get_costs(self):
        return self.__costs

    def get_number_of_vertices(self):
        return len(self.__vertices)

    def parse_through_vertices(self):
        return [vertex for vertex in self.__vertices]

    def is_vertex(self, vertex):
        if vertex in self.parse_through_vertices():
            return True
        return False

    def add_vertex(self, vertex):
        if self.is_vertex(vertex) is True:
            raise Exception
        self.__vertices.append(vertex)
        self.__inbound[vertex] = []
        self.__outbound[vertex] = []

    def is_edge(self, x, y):
        if self.is_vertex(x) is False:
            raise Exception
        if self.is_vertex(y) is False:
            raise Exception
        if x in self.__inbound[y] and y in self.__outbound[x]:
            return True
        return False

    def add_edge(self, x, y, c):
        if self.is_edge(x, y) is True:
            raise Exception
        self.__edges.append((x, y))
        self.__inbound[y].append(x)
        self.__outbound[x].append(y)
        self.__costs[(x, y)] = []
        self.__costs[(x, y)].append(c)

    def delete_vertex(self, x):
        if self.is_vertex(x) is False:
            raise Exception

        self.__vertices.remove(x)

        for (i, j) in list(self.__costs.keys()):
            if i == x or j == x:
                del self.__costs[(i, j)]

        for i in range(len(self.__inbound[x])):
            self.__outbound[self.__inbound[x][i]].remove(x)
        for i in range(len(self.__outbound[x])):
            self.__inbound[self.__outbound[x][i]].remove(x)

        if x in self.__outbound:
            self.__outbound.pop(x)
        if x in self.__inbound:
            self.__inbound.pop(x)

    def delete_edge(self, x, y):
        if self.is_vertex(x) is False:
            raise Exception
        if self.is_vertex(y) is False:
            raise Exception
        if self.is_edge(x, y) is False:
            raise Exception
        self.__edges.remove((x, y))
        self.__inbound[y].remove(x)
        self.__outbound[x].remove(y)
        self.__costs.pop((x, y))

    def get_in_out_degree(self, x):
        if self.is_vertex(x) is False:
            raise Exception
        return len(self.__inbound[x]), len(self.__outbound[x])

    def parse_out_edges(self, x):
        if self.is_vertex(x) is False:
            raise Exception
        return self.__outbound[x]

    def parse_in_edges(self, x):
        if self.is_vertex(x) is False:
            raise Exception
        return self.__inbound[x]

    def modify_the_cost(self, x, y, new_c):
        if self.is_vertex(x) is False:
            raise Exception
        if self.is_vertex(y) is False:
            raise Exception
        if self.is_edge(x, y) is False:
            raise Exception
        self.__costs[(x, y)] = new_c

    def copy(self):
        return deepcopy(self)

    def get_number_of_edges(self):
        return len(self.__edges)

    def backward_breadth_first_search(self, start_vertex, target_vertex):
        '''
        Given a start and target vertex returns the shortest path between them in the directed graph
        :param start_vertex: integer
        :param target_vertex: integer
        :return:
        List of vertices between the two vertices including them or an empty list if there is no path
        '''
        if start_vertex not in self.__vertices or target_vertex not in self.__vertices:
            raise Exception
        # if the vertices are not valid raise an exception
        queue = [target_vertex]
        visited = [target_vertex]
        next_v = {}
        while len(queue) != 0:
            current = queue.pop(0)
            # take first vertex from queue and go through its inbounds
            for access_v in self.__inbound[current]:
                # if it is not saved, it does
                if access_v not in visited:
                    queue.append(access_v)
                    visited.append(access_v)
                    next_v[access_v] = current
                    # here we save the actual way of the path
                    if access_v == start_vertex:
                        break
                    # if we got to the required start vertex, break
        path = []
        if start_vertex not in visited:
            return path
        # returns empty list if there is not a path
        path.append(start_vertex)
        while next_v[start_vertex] != target_vertex:
            path.append(next_v[start_vertex])
            start_vertex = next_v[start_vertex]
        # we make the list path using the dictionary next_v
        path.append(target_vertex)
        return path
