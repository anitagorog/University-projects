from copy import deepcopy


class DirectedGraph:
    def __init__(self, vertices, edges):
        self.__vertices = []
        self.__edges = []
        self.outbound = {}
        self.inbound = {}
        self.costs = {}

        for vertex in vertices:
            self.add_vertex(vertex)

        for edge in edges:
            self.add_edge(edge[0], edge[1], edge[2])

    def get_vertices(self):
        return self.__vertices

    def get_outbound(self):
        return self.outbound

    def get_inbound(self):
        return self.inbound

    def get_costs(self):
        return self.costs

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
        self.inbound[vertex] = []
        self.outbound[vertex] = []

    def is_edge(self, x, y):
        if self.is_vertex(x) is False:
            raise Exception
        if self.is_vertex(y) is False:
            raise Exception
        if x in self.inbound[y] and y in self.outbound[x]:
            return True
        return False

    def add_edge(self, x, y, c):
        if self.is_edge(x, y) is True:
            raise Exception
        self.__edges.append((x, y))
        self.inbound[y].append(x)
        self.outbound[x].append(y)
        self.costs[(x, y)] = []
        self.costs[(x, y)].append(c)

    def delete_vertex(self, x):
        if self.is_vertex(x) is False:
            raise Exception

        self.__vertices.remove(x)

        for (i, j) in list(self.costs.keys()):
            if i == x or j == x:
                del self.costs[(i, j)]

        for i in range(len(self.inbound[x])):
            self.outbound[self.inbound[x][i]].remove(x)
        for i in range(len(self.outbound[x])):
            self.inbound[self.outbound[x][i]].remove(x)

        if x in self.outbound:
            self.outbound.pop(x)
        if x in self.inbound:
            self.inbound.pop(x)

    def delete_edge(self, x, y):
        if self.is_vertex(x) is False:
            raise Exception
        if self.is_vertex(y) is False:
            raise Exception
        if self.is_edge(x, y) is False:
            raise Exception
        self.__edges.remove((x, y))
        self.inbound[y].remove(x)
        self.outbound[x].remove(y)
        self.costs.pop((x, y))

    def get_in_out_degree(self, x):
        if self.is_vertex(x) is False:
            raise Exception
        return len(self.inbound[x]), len(self.outbound[x])

    def parse_out_edges(self, x):
        if self.is_vertex(x) is False:
            raise Exception
        return self.outbound[x]

    def parse_in_edges(self, x):
        if self.is_vertex(x) is False:
            raise Exception
        return self.inbound[x]

    def modify_the_cost(self, x, y, new_c):
        if self.is_vertex(x) is False:
            raise Exception
        if self.is_vertex(y) is False:
            raise Exception
        if self.is_edge(x, y) is False:
            raise Exception
        self.costs[(x, y)] = new_c

    def copy(self):
        return deepcopy(self)

    def get_number_of_edges(self):
        return len(self.__edges)

    def backward_breadth_first_search(self, start_vertex, target_vertex):
        """
        Given a start and target vertex returns the shortest path between them in the directed graph
        :param start_vertex: integer
        :param target_vertex: integer
        :return:
        List of vertices between the two vertices including them or an empty list if there is no path
        """
        if start_vertex not in self.__vertices or target_vertex not in self.__vertices:
            raise Exception
        # if the vertices are not valid raise an exception
        queue = [target_vertex]
        visited = [target_vertex]
        next_v = {}
        while len(queue) != 0:
            current = queue.pop(0)
            # take first vertex from queue and go through its inbounds
            for access_v in self.inbound[current]:
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

    def highest_cost_path(self, start, end, topo_sorted):
        """
        Constructs the highest cost path between two given vertices in a directed graph
        :param start: integer
        :param end: integer
        :param topo_sorted: the list of topological order of the graph
        :return: the cost of the path, and a dictionary for helping to reconstruct the path
        """
        # initialising the two dictionaries, one for storing the costs, one for saving the path
        distance = {}
        previous = {}
        inf = float('-inf')
        # let we use 'inf' as -infinity

        for vertex in topo_sorted:
            # initialising the dictionaries for every vertex
            distance[vertex] = inf
            previous[vertex] = -1
        # change the cost from the dictionary from inf to 0 -> therefore the algorithm will start the path from here
        distance[start] = 0

        for vertex in topo_sorted:
            # parse through the topological order
            if vertex == end:
                # if it got to the target vertex -> break
                break
            for vertex2 in self.outbound[vertex]:
                # parsing through the outbound of the current vertex
                if distance[vertex2] < distance[vertex] + self.costs[(vertex, vertex2)][0]:
                    # if the cost saved for that outbound in the dictionary is less than the cost of the current vertex
                    # and the cost of their edge -> save
                    # does not stand if we add anything to -infinity (-> starts from start vertex)
                    distance[vertex2] = distance[vertex] + self.costs[(vertex, vertex2)][0]
                    previous[vertex2] = vertex

        return distance[end], previous
