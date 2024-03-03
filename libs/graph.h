#ifndef GRAPH_H
#define GRAPH_H

typedef struct Vertice
{
  char label;
  struct Vertice *next;
  struct Edge *adjacency_list;
} Vertice;

typedef struct Edge
{
  int weight;
  struct Vertice *target;
  struct Edge *edge;
} Edge;

int empty_graph(Vertice *vertice);
int empty_adjacency_list(Edge *edge);
Vertice *allocate_vertice();
Edge *allocate_edge();
void add_vertice(Vertice **graph, Vertice vertice);
void add_edge(Edge **adjacency_list, Edge edge);
void print_graph(Vertice *graph);
int graph_length(Vertice *graph);
Vertice *get_vertices(FILE *file_ptr);
Edge *get_edges(Vertice **graph, FILE *file_ptr);
Vertice *load_graph(const char *file_name);
void clear_graph(Vertice **graph);

#endif
