from array import array

import networkx as nx
import matplotlib.pyplot as plt
def read_nodes():
    with open('.nodes.txt') as f:
        lines = f.readlines()
        nodes = {}
        for idx, line in enumerate(lines):
            node_infos = line.split()
            demand = node_infos[0]
            coords = (float(node_infos[1])/100, float(node_infos[2])/100)
            nodes[str(idx)] = [demand, coords]

    f.close()

    print(nodes)
    return nodes
def read_edges():
    optimal_route_str = ""
    with open('.edges.txt') as f:
        line = f.readlines()[-1].split()
        edges = []
        for i in range(0,len(line)-1, 2):
            edges.append((line[i], line[i+1]))
            optimal_route_str = optimal_route_str + "[" + line[i] + " -> " + line[i+1] + "]" + ", "
    f.close()

    print(edges)
    return edges, optimal_route_str
def main():
    #Read nodes from file
    nodes = read_nodes()
    nNodes = len(nodes)

    #Read edges and costruct string with optimal route
    edges, optimal_route_str = read_edges()

    #Create multigraph for plotting
    G = nx.MultiDiGraph()
    G.add_edges_from(edges)

    #Set nodes color, red for depots and blue for normal stations
    color_map = ['darkred' if k == '0' or k == str(nNodes-1) else 'blue' for k in nodes.keys()]
    #Set edge color, green for main path, black for fullfill from depot
    edge_colours = ['grey' if edge[1] == '0' or edge[0] == '0' else 'black' for edge in G.edges()]
    edge_colours[0] = 'black'

    #Set position of nodes according to real positions and set label with demand
    pos = nx.spring_layout(G)
    for k,v in nodes.items():
        pos[k] = v[1]
        #Node label with demand amount
        if(k != str(0) and k != str(nNodes-1)):
            plt.text(pos[k][0],pos[k][1]-0.05,s='Demand =' + nodes[str(k)][0], bbox=dict(facecolor='blue', alpha=0.5),horizontalalignment='center')

    #Drawing the graph
    plt.title("Optimal path: " + optimal_route_str)
    nx.draw_networkx_nodes(G, pos, node_color=color_map,
                            node_size = 500)
    nx.draw_networkx_labels(G, pos, font_color='white')
    nx.draw_networkx_edges(G, pos, edgelist=G.edges, edge_color=edge_colours, arrows=True, width=1.5, connectionstyle='arc3, rad = 0.2')
    #nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
    plt.show()

if __name__ == "__main__":
    main()