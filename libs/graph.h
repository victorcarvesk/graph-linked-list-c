#ifndef GRAPH_H
#define GRAPH_H

// #include "../libs/linked_list.h"

typedef struct Vertice {
  char label;
  struct Vertice *next;
  struct Edge *adj_list;
} Vertice;

typedef struct Edge {
  int weight;
  struct Vertice *target;
  struct Edge *edge;
} Edge;

Vertice *new_graph();
Edge *new_edge();
int empty_graph(Vertice * vertice);
int empty_edge(Edge * edge);
Vertice *allocate_vertice();
Edge *allocate_edge();
void add_vertice(Vertice **graph, Vertice vertice);
void add_edge(Edge **adj_list, Edge edge);
void print_graph(Vertice *graph);
// int list_length(Vertice * head);
// void remove_vertice(Vertice ** head, Vertice vertice);
// Vertice * search_vertice(Vertice * head, Vertice vertice);
// void del_list(Vertice ** head);


Vertice* get_vertices(FILE *file_ptr);
// void get_Vertices(FILE *adjacency_matrix, int quant_vertices);

Vertice* load_graph(const char *file_name);

Edge* get_edges(Vertice** graph, FILE* file_ptr);

#endif
