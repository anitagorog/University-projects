import math
import random
from graph import DirectedGraph


def save_file(file_name, outbound, vertices, cost, nr_edges, inbound):
    fo = open(file_name, "wt")
    vertex_string = str(len(vertices)) + " " + str(nr_edges) + "\n"
    fo.write(vertex_string)
    for vertex in vertices:
        if not outbound[vertex] and not inbound[vertex]:
            vertex_string = str(vertex) + " " + str(-1) + "\n"
            fo.write(vertex_string)
        else:
            for outbounds in outbound[vertex]:
                vertex_string = str(vertex) + " " + str(outbounds) + " " + str(cost[(vertex, outbounds)][0]) + "\n"
                fo.write(vertex_string)
    fo.close()


def save_random(graph, file_name):
    if graph == -1:
        fo = open(file_name, "wt")
        fo.write("Request not possible")
        fo.close()
    else:
        save_file(file_name, graph.get_outbound(), graph.get_vertices(), graph.get_costs(), graph.get_number_of_edges(),
                  graph.get_inbound())


def load_file(file_name):
    # t - text file mode, r - reading
    vertices = []
    edges = []
    graph = DirectedGraph(vertices, edges)

    lines = []
    try:
        fin = open(file_name, "rt")
        lines = fin.readlines()
        fin.close()
    except IOError:
        pass

    line = lines[0].strip()
    nr_vertex = int(line.split(" ")[0])
    first_line = 0

    for i in range(nr_vertex):
        graph.add_vertex(i)

    for line in lines:
        if first_line == 0:
            first_line += 1
        else:
            line = line.strip()
            if line.split(" ")[1] != "-1":
                v1 = int(line.split(" ")[0])
                v2 = int(line.split(" ")[1])
                cos = int(line.split(" ")[2])

                try:
                    graph.add_edge(v1, v2, cos)
                except Exception:
                    pass

    return graph


def create_random_graph(nr_vertices, nr_edges):
    random_graph = DirectedGraph([], [])
    for i in range(nr_vertices):
        random_graph.add_vertex(i)
    while random_graph.get_number_of_edges() < nr_edges:
        i = random.randint(0, nr_vertices-1)
        j = random.randint(0, nr_vertices-1)
        try:
            random_graph.add_edge(i, j, i+j)
        except Exception:
            pass
    return random_graph


def negative_cycle(graph, start):
    """
    Checks if there is a negative cycle from vertex 'start'
    :param graph: DirectedGraph object
    :param start: integer
    :return: True if there is, False otherwise
    """
    n = graph.get_number_of_vertices()  # len(graph)
    d = [[math.inf for x in range(n)] for y in range(n)]

    for i in range(n):
        d[i][i] = 0
    for (i, j), c in graph.costs.items():
        d[i][j] = c[0]
    for k in range(n):
        for i in range(n):
            for j in range(n):
                d[i][j] = min(d[i][j], d[i][k] + d[k][j])
                if d[start][start] < 0:
                    print("There is a negative cost cycle in the graph accessible from the starting vertex.")
                    return True
    print("No negative cycle")
    return False


def lowest_cost_walk(graph, start, end):
    """
    Computes the lowest cost of a walk from source to target and builds the path of at most known length
    k, where k is from [1, n] (n is the number of the vertices). If no walk exists,
    the cost is math.inf as initialized.
    :param graph: DirectedGraph object
    :param start: number as a string
    :param end: number as a string
    :return: the walk represented as a list and the minimum_cost as an integer
    """
    n = graph.get_number_of_vertices()
    d = [[math.inf for x in range(n + 1)] for y in range(n)]
    d[int(start)][0] = 0
    # initialize matrix d with inf as elements and at the line number 'start' the first element with 0
    previous = [[math.inf for x in range(n)] for y in range(n)]
    # initialize matrix previous with elements inf, to reconstruct the walk later on

    for length in range(1, n):
        # parse through as the possible length of the walk
        for vertex in graph.parse_through_vertices():
            # parse through all vertex
            if d[int(vertex)][length - 1] != math.inf:
                # if it was initialised after giving the value inf check
                for neighbour in graph.get_outbound()[vertex]:
                    # go through its outbounds
                    if d[int(neighbour)][length] > (d[int(vertex)][length - 1] + graph.get_costs()[(vertex, neighbour)][0]):
                        # if the outbound of vertex at given length is greater than the vertex at previous length plus
                        # their cost -> save
                        d[int(neighbour)][length] = d[int(vertex)][length - 1] + graph.get_costs()[(vertex, neighbour)][0]
                        previous[int(neighbour)][length] = int(vertex)

    minimum_cost = math.inf
    minimum_length = 0
    for length in range(1, n):
        if d[int(end)][length] < minimum_cost:
            minimum_cost = d[int(end)][length]
            minimum_length = int(length)
    # computing minimum cost and length using matrix d

    walk = [int(end)]
    current = int(end)
    for length in range(minimum_length, 0, -1):
        walk.insert(0, previous[int(current)][length])
        current = previous[int(current)][length]
    # constructing the path using matrix previous

    return walk, minimum_cost


def topo_sort_dft(graph, vertex, sortd, fully_proc, in_proc):
    """
    Analyses a vertex of a graph and checks if there exists a cycle, if not adds to the topological order of it
    :param graph: DirectedGraph object
    :param vertex: integer
    :param sortd: list of the topological sort
    :param fully_proc: list of fully processed vertices
    :param in_proc: list of vertices still in process
    :return: False, if it found a cycle, True otherwise
    """
    # add the current vertex to be in process
    in_proc.append(vertex)
    for y in graph.get_inbound()[vertex]:
        # parse through the inbound of it
        if y in in_proc:
            # if one inbound of it is in process that means there is a cycle, so return false
            return False
        elif y not in fully_proc:
            # else if the inbound is not fully processed yet, call the function for that too
            ok = topo_sort_dft(graph, y, sortd, fully_proc, in_proc)
            # if that call returned false -> return false here too
            if not ok:
                return False
    # remove the vertex from the ones in process and add to the fully processes and the topological sorted ones
    in_proc.remove(vertex)
    sortd.append(vertex)
    fully_proc.append(vertex)
    # if it gets here, that means no cycles -> return true
    return True


def get_topo_sorted(graph):
    """
    Constructs the topological sort of directed graph 'graph'
    :param graph: DirectedGraph object
    :return: a list of vertices in topological sorting order, or empty list if G has cycles
    """
    # initialise the list where will be:
    sortd = []
    # the topological sort
    fully_proc = []
    # the processed vertices
    in_proc = []
    # and where we put the vertices in process
    for x in graph.get_vertices():
        # parse through vertices
        if x not in fully_proc:
            # if x is not fully processed yet call the topo_sort_dft function
            ok = topo_sort_dft(graph, x, sortd, fully_proc, in_proc)
            if not ok:
                # if the function returned false, it means we have cycles -> return an empty list
                sortd = []
                return sortd
    # if no cycles, return the topological order
    return sortd


class UI:
    def __init__(self):
        vertices = []
        edges = []
        self.__graph = DirectedGraph(vertices, edges)
        self.file_name = ""

    @staticmethod
    def menu():
        print("Choose:\n1. Get the number of vertices \n"
              "2. Parse (iterate) the set of vertices\n"
              "3. Given two vertices, find out whether there is an edge from the first one to the second one, \n"
              "4. Get the in degree and the out degree of a specified vertex\n"
              "5. Parse (iterate) the set of outbound"
              " edges of a specified vertex (that is, provide an iterator). For each outbound edge retrieve the target"
              " vertex\n"
              "6. Parse the set of inbound edges of a specified vertex (as above)\n"
              "7. Retrieve or modify the information (the integer) attached to a specified edge\n"
              "8. The graph shall be modifiable: add and remove an edge or a"
              " vertex. \n"
              # Think about what should happen with the properties of existing edges and with the identification of
              # remaining vertices.
              "9. The graph shall be copyable\n"
              # that is
              # it should be possible to make an exact copy of a graph, so that the original can be then modified
              # independently of its copy. Think about the desirable behaviour of an Edge_property attached to the 
              # original
              # graph, when a copy is made.
              "10. Read the graph from a text file (as an external function)\n"  
              "11. Write the graph from a text file (as an external function)\n"  
              "12. Create a random graph with specified number of vertices and of edges (as an external function).\n"
              "13. Given a directed graph and two vertices, finds a lowest length path between them, by using a "
              "backward breadth-first search from the ending vertex.\n"
              "14. Given a graph with costs and two vertices finds a lowest cost walk between the given vertices, "
              "or prints a message if there are negative cost cycles accessible from the starting vertex.\n"
              # "The program will use a matrix defined as d[x,k]=the cost of the lowest cost walk from s to x and of "
              # "length at most k, where s is the starting vertex.\n"
              "15. Verify if the corresponding graph is a DAG and performs a topological sorting of the activities "
              "using the algorithm based on depth-first traversal\n"
              "     - if it is a DAG, finds a highest cost path between two given vertices, in O(m+n).\n"
              "16. Exit\n")

    def start(self):
        while True:
            self.menu()
            choice = input("Enter your intention: ")
            try:
                if choice == "1":
                    print(self.__graph.get_number_of_vertices())
                elif choice == "2":
                    print(self.__graph.parse_through_vertices())
                elif choice == "3":
                    vertex1 = int(input("First vertex: "))
                    vertex2 = int(input("Second vertex: "))
                    if self.__graph.is_edge(vertex1, vertex2):
                        print("It exists.")
                    else:
                        print("It does not exist.")
                elif choice == "4":
                    vertex = int(input("The vertex: "))
                    ind, out = self.__graph.get_in_out_degree(vertex)
                    print(f"In degree {ind} \nOut degree {out} \n")
                elif choice == "5":
                    vertex = int(input("The vertex: "))
                    print(self.__graph.parse_out_edges(vertex))
                elif choice == "6":
                    vertex = int(input("The vertex: "))
                    print(self.__graph.parse_in_edges(vertex))
                elif choice == "7":
                    x = int(input("First vertex: "))
                    y = int(input("Second vertex: "))
                    intention = input("Choose retrieve or modify: ")
                    if intention == "retrieve":
                        print("The cost is: ", self.__graph.get_costs()[(x, y)][0])
                    elif intention == "modify":
                        c = int(input("New cost: "))
                        self.__graph.modify_the_cost(x, y, c)
                    else:
                        print("Invalid option\n")
                elif choice == "8":
                    option = input("Add or delete? (1 or 2) >>> ")
                    if option == "1":
                        which = input("A vertex/edge? >>> ")
                        if which == "vertex":
                            x = int(input("Enter the vertex: "))
                            self.__graph.add_vertex(x)
                        elif which == "edge":
                            x = int(input("Enter the first vertex: "))
                            y = int(input("Enter the second vertex: "))
                            c = int(input("Enter the cost: "))
                            self.__graph.add_edge(x, y, c)
                        else:
                            print("Invalid")
                    elif option == "2":
                        which = input("A vertex/edge? >>> ")
                        if which == "vertex":
                            x = int(input("Enter the vertex: "))
                            self.__graph.delete_vertex(x)
                        elif which == "edge":
                            x = int(input("Enter the first vertex: "))
                            y = int(input("Enter the second vertex: "))
                            self.__graph.delete_edge(x, y)
                    else:
                        print("Invalid")
                elif choice == "9":
                    copy_graph = self.__graph.copy()
                    print("The graph was copied\n")
                    # print(copy_graph.get_vertices())
                    # self.__graph.add_vertex(4)
                    # print(self.__graph.get_vertices())
                    # print(copy_graph.get_vertices())
                elif choice == "10":
                    self.file_name = input("Enter the filename(graph.txt, graph1k.txt, graph10k.txt, graph100k.txt or "
                                               "graph1m.txt): ")
                    # if self.file_name != "graph.txt" and self.file_name != "graph1k.txt" \
                    #        and self.file_name != "graph10k.txt" and self.file_name != "graph100k.txt" \
                     #       and self.file_name != "graph1m.txt" and self.file_name != "graph_modif.txt" \
                      #      and self.file_name != "graph1k_modif.txt" \
                       #     and self.file_name != "graph10k_modif.txt" and self.file_name != "graph100k_modif.txt" \
                        #    and self.file_name != "graph1m_modif.txt":
                    #    raise Exception
                    self.__graph = load_file(self.file_name)
                elif choice == "11":
                    # save_file("small_graph4.txt", self.__graph.get_outbound(), self.__graph.get_vertices(),
                    #       self.__graph.get_costs(), self.__graph.get_number_of_edges(), self.__graph.get_inbound())
                    make_name = self.file_name.split(".")
                    file_name = make_name[0] + "_modif.txt"
                    save_file(file_name, self.__graph.get_outbound(), self.__graph.get_vertices(),
                              self.__graph.get_costs(), self.__graph.get_number_of_edges(), self.__graph.get_inbound())
                elif choice == "12":
                    nr_of_vertices = int(input("Enter the number of vertices: "))
                    nr_of_edges = int(input("Enter the number of edges: "))
                    if nr_of_edges > nr_of_vertices*nr_of_vertices:
                        print("Request not possible\n")
                        random_graph = -1
                    else:
                        random_graph = create_random_graph(nr_of_vertices, nr_of_edges)
                        print("Graph created")
                    save_random(random_graph, "graph.txt")
                elif choice == "13":
                    start_vertex = int(input("Enter the start vertex: "))
                    target_vertex = int(input("Enter the target vertex: "))
                    path = self.__graph.backward_breadth_first_search(start_vertex, target_vertex)
                    if not path:
                        print("No path between the two vertices.")
                    else:
                        print("Path: " + ("-".join(str(v) for v in path)))
                        print("The length: " + str(len(path)-1))
                elif choice == "14":
                    start = input("The start vertex: ")
                    end = input("The target vertex: ")

                    if int(start) not in self.__graph.parse_through_vertices() \
                            or int(end) not in self.__graph.parse_through_vertices():
                        raise Exception

                    if negative_cycle(self.__graph, int(start)) is True:
                        continue

                    walk, minimum_cost = lowest_cost_walk(self.__graph, start, end)
                    if minimum_cost == math.inf:
                        print(f"Vertex {end} is not accessible from vertex {start}.")
                    else:
                        print(f"The cost of the lowest cost walk from {start} to {end} is {minimum_cost}")
                        print("The walk is:")
                        for i in range(len(walk) - 1):
                            print(walk[i], end="-")
                        print(walk[-1])
                elif choice == "15":
                    sortd = get_topo_sorted(self.__graph)
                    if not sortd:
                        print("Graph has cycles.\n")
                    else:
                        print(sortd)
                        print("Graph is a DAG\n")

                        start = int(input("Start vertex: "))
                        end = int(input("End vertex: "))

                        distance, previous = self.__graph.highest_cost_path(start, end, sortd)
                        if distance == float('-inf'):
                            print("No path")
                        else:
                            path = []
                            vertex = end
                            path.append(vertex)
                            while previous[vertex] != -1:
                                path.append(previous[vertex])
                                vertex = previous[vertex]
                            path.reverse()
                            print("Path :" + ("-".join(str(e) for e in path)))
                            print("Cost: " + str(distance))
                elif choice == "16":
                    exit()
                else:
                    print("Invalid request\n")
            except Exception as a:
                print(a)
                print("Invalid request. Try again.\n")


def main():
    ui = UI()
    ui.start()


main()
