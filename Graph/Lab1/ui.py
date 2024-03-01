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
              "13. Exit\n")

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
                      #      and self.file_name != "graph10k.txt" and self.file_name != "graph100k.txt" \
                       #     and self.file_name != "graph1m.txt":
                       # raise Exception
                    self.__graph = load_file(self.file_name)
                elif choice == "11":
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
                    exit()
                else:
                    print("Invalid request\n")
            except Exception:
                print("Invalid request. Try again.\n")


def main():
    ui = UI()
    ui.start()


main()
