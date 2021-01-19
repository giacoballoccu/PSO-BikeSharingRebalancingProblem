from array import array

import networkx as nx
import matplotlib.pyplot as plt

def main():
    with open('.nodes.txt') as f:
        lines = f.readlines()

        nodes = {}
        pos1 = {}
        for idx, line in enumerate(lines):
            node_infos = line.split()
            demand = node_infos[0]
            coords = (float(node_infos[1])/100, float(node_infos[2])/100)
            pos1[str(idx)] = [float(node_infos[1])/100, float(node_infos[2])/100]
            nodes[idx] = [demand, coords]

    f.close()

    with open('.edges.txt') as f:
        line = f.readline().split()
        edges = []
        for i in range(0,len(line)-1):
            edges.append((line[i], line[i+1]))

    f.close()


    G = nx.DiGraph()
    for idx, edge in enumerate(edges):
        G.add_edges_from([edge], weight=idx)



    #values = [val_map.get(node, 0.25) for node in G.nodes()]

    # Specify the edges you want here
    # red_edges = [('A', 'C'), ('E', 'C')]
    # edge_colours = ['black' if not edge in red_edges else 'red'
                    #for edge in G.edges()]
    # black_edges = [edge for edge in G.edges() if edge not in red_edges]

    # Need to create a layout when doing
    # separate calls to draw nodes and edges
    pos = nx.spring_layout(G)
    for k,v in pos1.items():
        pos[k] = v
    nx.draw_networkx_nodes(G, pos, cmap=plt.get_cmap('jet'),
                            node_size = 500)
    nx.draw_networkx_labels(G, pos)
    nx.draw_networkx_edges(G, pos, edgelist=G.edges, edge_color='r', arrows=True)
    plt.show()

if __name__ == "__main__":
    main()