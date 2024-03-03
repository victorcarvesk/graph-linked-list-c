#include <stdio.h>
#include <stdlib.h>

#include "../libs/graph.h"

int empty_graph(Vertice *graph)
{
  return (graph == NULL);
}

int empty_adjacency_list(Edge *edge)
{
  return (edge == NULL);
}

Vertice *allocate_vertice()
{
  return (Vertice *)malloc(sizeof(Vertice));
}

Edge *allocate_edge()
{
  return (Edge *)malloc(sizeof(Edge));
}

void add_vertice(Vertice **graph, Vertice vertice)
{
  Vertice *new_vertice, *current_vertice;
  new_vertice = allocate_vertice();

  if (new_vertice == NULL)
  {
    perror("Cannot allocate memory for new vertice");
  }

  new_vertice->label = vertice.label;
  new_vertice->next = NULL;

  if (empty_graph(*graph))
  {
    *graph = new_vertice;
  }
  else
  {
    current_vertice = *graph;
    while (current_vertice->next != NULL)
    {
      current_vertice = current_vertice->next;
    }
    current_vertice->next = new_vertice;
  }
  return;
}

void add_edge(Edge **adjacency_list, Edge edge)
{
  Edge *new_edge, *current_edge;
  new_edge = allocate_edge();

  if (new_edge == NULL)
  {
    perror("Cannot allocate memory for new edge");
  }

  new_edge->target = edge.target;
  new_edge->edge = NULL;

  if (empty_adjacency_list(*adjacency_list))
  {
    *adjacency_list = new_edge;
  }
  else
  {
    current_edge = *adjacency_list;
    while (current_edge->edge != NULL)
    {
      current_edge = current_edge->edge;
    }
    current_edge->edge = new_edge;
  }
  return;
}

void print_graph(Vertice *graph)
{
  Vertice *current = graph;
  while (current != NULL)
  {
    printf("[%c] ", current->label);
    Edge *adje = current->adjacency_list;
    while (adje != NULL)
    {
      printf("→ %c ", adje->target->label);
      adje = adje->edge;
    }
    printf("\n");
    current = current->next;
  }
  printf("\n");
}

int graph_length(Vertice *graph)
{
  Vertice *current = graph;
  int vertice_counter = 0;
  while (current != NULL)
  {
    vertice_counter++;
    current = current->next;
  }
  return vertice_counter;
}

Vertice *get_vertices(FILE *file_ptr)
{

  char buffer;
  int count = 0;
  Vertice *graph;

  while (!feof(file_ptr))
  {

    buffer = fgetc(file_ptr);
    Vertice *vertice = allocate_vertice();

    if (buffer >= 'A' && buffer <= 'Z')
    {
      vertice->label = buffer;
      add_vertice(&graph, *vertice);
    }
    else if (buffer == '\n')
    {
      return graph;
    }
  }
}

Edge *get_edges(Vertice **graph, FILE *file_ptr)
{
  char buffer;
  int count = 0;
  Edge *adjacency_list = NULL;
  Vertice *vertices = *graph;

  while (!feof(file_ptr))
  {

    buffer = fgetc(file_ptr);
    Edge *edge = allocate_edge();

    if (buffer == '0' || buffer == '1')
    {

      if (buffer == '1')
      {
        edge->target = vertices;
        edge->weight = 1;
        add_edge(&adjacency_list, *edge);
      }
      vertices = vertices->next;
    }
    else if (buffer == '\n')
    {
      return adjacency_list;
    }
  }
}

Vertice *load_graph(const char *file_name)
{
  FILE *adjacency_matrix = fopen(file_name, "r");

  if (adjacency_matrix == NULL)
  {
    perror("cannot open file");
    return NULL;
  }

  printf("\nLoading graph from file '%s'...\n", file_name);

  Vertice *graph = get_vertices(adjacency_matrix);

  printf("Identified vertices: %d.\n", graph_length(graph));

  Vertice *current = graph;
  while (current != NULL)
  {
    current->adjacency_list = get_edges(&graph, adjacency_matrix);
    current = current->next;
  }

  fclose(adjacency_matrix);

  printf("Graph successfully loaded.\n\n");

  return graph;
}

void clear_graph(Vertice **graph)
{
  Vertice *current_vertice = *graph;
  Vertice *next_vertice;
  while (current_vertice != NULL)
  {
    Edge *current_edge = current_vertice->adjacency_list;
    Edge *next_edge;
    while (current_edge != NULL)
    {
      next_edge = current_edge->edge;
      free(current_edge);
      current_edge = next_edge;
    }
    next_vertice = current_vertice->next;
    free(current_vertice);
    current_vertice = next_vertice;
  }
  *graph = NULL;
  printf("Graph cleared.\n\n");
}
